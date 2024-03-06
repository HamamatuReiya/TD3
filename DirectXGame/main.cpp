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
#include "DesertStage.h"
#include "VolcanoStage.h"

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

	DesertStage* desertStage = nullptr;
	VolcanoStage* volcanoStage = nullptr;

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

	//砂漠ステージの初期化
	desertStage = new DesertStage();
	desertStage->Initialize();

	//火山ステージの初期化
	volcanoStage = new VolcanoStage();
	volcanoStage->Initialize();

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

				// タイトルシーンの初期化、フラグリセット等
				titleScene->sceneReset();
			}

			break;

		case SceneType::kSelect:
			selectScene->Update();
			if (selectScene->IsSceneEndIsland()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = selectScene->NextSceneIsland();

				// セレクトシーンシーンの初期化、フラグリセット等
				selectScene->sceneReset();
			}

			if (selectScene->IsSceneEndDesert()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = selectScene->NextSceneDesert();

				// セレクトシーンシーンの初期化、フラグリセット等
				selectScene->sceneReset();
			}

			if (selectScene->IsSceneEndVolcano()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = selectScene->NextSceneVolcano();

				// セレクトシーンシーンの初期化、フラグリセット等
				selectScene->sceneReset();
			}

			break;

		case SceneType::kGamePlay:
			// ゲームシーンの毎フレーム処理
			gameScene->Update();

			if (gameScene->IsSceneEnd()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = gameScene->NextScene();

				// ゲームシーンの初期化、フラグリセット等
				gameScene->sceneReset();
			}

			break;

		case SceneType::kDesertStage:
			// 砂漠ステージの毎フレーム処理
			desertStage->Update();

			if (desertStage->IsSceneEnd()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = desertStage->NextScene();

				// 砂漠ステージの初期化、フラグリセット等
				desertStage->sceneReset();
			}

			break;

		case SceneType::kVolcanoStage:
			// 火山ステージの毎フレーム処理
			volcanoStage->Update();

			if (volcanoStage->IsSceneEnd()) {
				// 次のシーンの値を代入してシーン切り替え
				sceneNo = volcanoStage->NextScene();

				// 火山ステージの初期化、フラグリセット等
				volcanoStage->sceneReset();
			}

			break;
		}
		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		//フルスクリーン
		if (input->TriggerKey(DIK_F)) {
			win->SetFullscreen(true);
		}
		if (input->TriggerKey(DIK_D)) {
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
			//セレクトシーンの描画
			selectScene->Draw();
			break;
		case SceneType::kGamePlay:
			// ゲームシーンの描画
			gameScene->Draw();
		case SceneType::kDesertStage:
			//砂漠ステージの描画
			desertStage->Draw();
		case SceneType::kVolcanoStage:
			//火山ステージの描画
			volcanoStage->Draw();

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