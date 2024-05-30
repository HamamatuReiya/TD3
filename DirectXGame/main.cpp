#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

#include "TitleScene.h"
#include "SelectScene.h"
#include "ResultScene.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;
	SelectScene* selectScene = nullptr;

	ResultScene* resultScene = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow();

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);


#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

	//タイトルシーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();

	//セレクトシーンの初期化
	selectScene = new SelectScene();
	selectScene->Initialize();

	resultScene = new ResultScene();
	resultScene->Initialize();

	//最初のシーン
	SceneType sceneNo = SceneType::kTitle;

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();

		switch (sceneNo) {
		case SceneType::kTitle:
			titleScene->Update();

			if (titleScene->IsSceneEnd()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = titleScene->NextScene();
				gameScene->BommLvReset();

				// タイトルシーンの初期化、フラグリセット等
				titleScene->SceneReset();
			}

			break;

		case SceneType::kSelect:
			selectScene->Update();
			if (selectScene->IsSceneEnd()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = selectScene->NextScene();
				// 素材の配置の読み込み
				gameScene->LoadMaterial();
				// セレクトシーンシーンの初期化、フラグリセット等
				selectScene->SceneReset();
				// BGM
				titleScene->BGMStop();
				gameScene->BGMReset();
			}

			break;

		case SceneType::kGamePlay:
			// ゲームシーンの毎フレーム処理
			gameScene->Update();

			if (gameScene->IsSceneEnd()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = gameScene->NextScene();

				// ゲームシーンの初期化、フラグリセット等
				gameScene->SceneReset();

				//BGM
				gameScene->BGMStop();
				resultScene->BGMReset();
			}
			if (gameScene->IsTutorialSceneEnd()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = gameScene->TutorialNextScene();

				// ゲームシーンの初期化、フラグリセット等
				gameScene->SceneReset();
				gameScene->BGMStop();
			}

			break;

		case SceneType::kResult:
			// ゲームシーンの毎フレーム処理
			resultScene->Update();

			if (resultScene->IsSceneEnd()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = resultScene->NextScene();

				gameScene->MaterialReset();

				// ゲームシーンの初期化、フラグリセット等
				resultScene->SceneReset();
				// BGM
				resultScene->BGMStop();
				titleScene->BGMReset();
			}

			break;
		}

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// フルスクリーン
		if (input->TriggerKey(DIK_F)) {
			win->SetFullscreen(true);
		}
		if (input->TriggerKey(DIK_ESCAPE)) {
			win->SetFullscreen(false);
		}

		// 描画開始
		dxCommon->PreDraw();

		switch (sceneNo) {
		case SceneType::kTitle:
			// タイトルシーンの描画
			titleScene->Draw();
			break;

		case SceneType::kSelect:
			// セレクトシーンの描画
			selectScene->Draw();
			break;

		case SceneType::kGamePlay:
			// ゲームシーンの描画
			gameScene->Draw();
			break;
		case SceneType::kResult:
			resultScene->Draw();
			break;
		}

		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	SafeDelete(gameScene);
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}
