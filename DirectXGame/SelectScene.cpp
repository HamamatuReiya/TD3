#include "SelectScene.h"

SelectScene::SelectScene() {}

SelectScene::~SelectScene() {}

void SelectScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_.Initialize();

	//天球
	//3Dモデルの生成
	modelSpacedome_.reset(Model::CreateFromOBJ("spacedome", true));
	//天球の生成
	spacedome_ = std::make_unique<Spacedome>();
	//天球の初期化
	spacedome_->Initialize(modelSpacedome_.get());

	TextureInitialize();

	cursorSpeed_ = {30, 0};

	// フェードの生成
	fade_ = std::make_unique<Fade>();
	// フェードの初期化
	fade_->Initialize();
	// フェードインの開始
	fade_->FadeInStart();
}

void SelectScene::Update() {

	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;
	XINPUT_STATE preJoyState;

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (stageCount_ >= 0 || stageCount_ <= kMaxStage_) {
			if (joyState.Gamepad.sThumbLX < -1 && padStateFlag_ == false) {
				padStateFlag_ = true;
				stageCount_ -= 1;
			} else if (joyState.Gamepad.sThumbLX > 1 && padStateFlag_ == false) {
				padStateFlag_ = true;
				stageCount_ += 1;
			}

			if (joyState.Gamepad.sThumbLX == 0) {
				padStateFlag_ = false;
			}

			Input::GetInstance()->Input::GetJoystickStatePrevious(0, preJoyState);
			
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT &&
			    !(preJoyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) {
				stageCount_ += 1;

			} else if (
			    joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT &&
			    !(preJoyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) {
				stageCount_ -= 1;
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
		}

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

	if (stageCount_ >= 0 || stageCount_ <= kMaxStage_) {
		if (input_->TriggerKey(DIK_LEFT)) {
			stageCount_ -= 1;
		} else if (input_->TriggerKey(DIK_RIGHT)) {
			stageCount_ += 1;
		}
	}

	//ステージ選択
	StageSelect();

	textureCursor_->SetPosition(cursorPos_);

	//天球の更新
	spacedome_->Update();

	// フェードの更新
	fade_->Update();
}

void SelectScene::Draw() {
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

	// 天球の描画
	spacedome_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	textureCursor_->Draw();

	textureNumber_[0]->Draw();
	textureNumber_[1]->Draw();
	textureNumber_[2]->Draw();
	textureNumber_[3]->Draw();

	// フェードの描画
	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void SelectScene::TextureInitialize() {
	// 数字の画像
	uint32_t numHandle[4];
	numHandle[0] = TextureManager::Load("./Resources/number/0.png");
	numHandle[1] = TextureManager::Load("./Resources/number/1.png");
	numHandle[2] = TextureManager::Load("./Resources/number/2.png");
	numHandle[3] = TextureManager::Load("./Resources/number/3.png");

	// 取得した数
	textureNumber_[0] = Sprite::Create(numHandle[0], {50.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	textureNumber_[1] = Sprite::Create(numHandle[1], {313.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	textureNumber_[2] = Sprite::Create(numHandle[2], {600.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	textureNumber_[3] = Sprite::Create(numHandle[3], {853.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	//カーソルの画像
	uint32_t cursorHandle;
	cursorHandle = TextureManager::Load("cursor.png");

	textureCursor_ = Sprite::Create(cursorHandle, {50.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}

void SelectScene::StageSelect() {
	
	if (stageCount_ < 0) {
		stageCount_ += 1;
	}
	if (stageCount_ > kMaxStage_) {
		stageCount_ -= 1;
	}

	if (stageCount_ == 0) {
		cursorPos_.x = 50.0f - 30;
		stageNo = Stage::kTutorial;
	}

	if (stageCount_ == 1) {
		cursorPos_.x = 313.0f - 30;
		stageNo = Stage::kIsland;
	}
	if (stageCount_ == 2) {
		cursorPos_.x = 600.0f - 30;
		stageNo = Stage::kDesert;
	}
	if (stageCount_ == 3) {
		cursorPos_.x = 853.0f - 30;
		stageNo = Stage::kVolcano;
	}
}

void SelectScene::SceneReset() {
	// フェードインの開始
	fade_->FadeInStart();
}
