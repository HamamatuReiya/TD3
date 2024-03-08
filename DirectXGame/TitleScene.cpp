#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// フェードの生成
	fade_ = std::make_unique<Fade>();
	// フェードの初期化
	fade_->Initialize();
	//フェードインの開始
	fade_->FadeInStart();
}

void TitleScene::Update() {
	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A && fadeTimerFlag_ == false) {
			fadeTimerFlag_ = true;
			fade_->FadeOutStart();
		}

		if (fadeTimerFlag_ == true) {
			fadeTimer_--;
		}

		if (fadeTimer_ <= 0) {
			isSceneEnd_ = true;
		}

	}

	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd_ = true;
	}

		// フェードの更新
		fade_->Update();
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	// フェードの描画
	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void TitleScene::SceneReset() {
	// フェードインの開始
	fade_->FadeInStart();
}
