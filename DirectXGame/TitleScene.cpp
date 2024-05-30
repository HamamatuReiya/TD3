#include "TitleScene.h"
#include <ImGuiManager.h>

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_.Initialize();

	titleHandle_ = TextureManager::Load("title.png");
	textureTitle_ = Sprite::Create(titleHandle_, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	fullScreenHandle_ = TextureManager::Load("UI.png");
	textureFullScreen_ = Sprite::Create(fullScreenHandle_, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	subTitleHandle_ = TextureManager::Load("subTitle.png");
	textureSubTitle_ = Sprite::Create(subTitleHandle_, {0.0f, 0.0f}, subTitleColor_, {0.0f, 0.0f});

	subTitleHandle1_ = TextureManager::Load("subTitle1.png");
	textureSubTitle1_ = Sprite::Create(subTitleHandle1_, {0.0f, 0.0f}, subTitleColor1_, {0.0f, 0.0f});

	subTitleHandle2_ = TextureManager::Load("subTitle2.png");
	textureSubTitle2_ = Sprite::Create(subTitleHandle2_, {0.0f, 0.0f}, subTitleColor2_, {0.0f, 0.0f});

	// ルール説明
	luleHandle_ = TextureManager::Load("Lule.png");
	textureLule_ =
	    Sprite::Create(luleHandle_, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	isSceneEnd_ = false;

	/*score_ = std::make_unique<Score>();
	score_->Initialize();

	ranking_ = std::make_unique<Ranking>();
	ranking_->Initialize();*/

	// 天球
	// 3Dモデルの生成
	modelSpacedome_.reset(Model::CreateFromOBJ("spacedome", true));
	// 天球の生成
	spacedome_ = std::make_unique<Spacedome>();
	// 天球の初期化
	spacedome_->Initialize(modelSpacedome_.get());

	// フェードの生成
	fade_ = std::make_unique<Fade>();
	// フェードの初期化
	fade_->Initialize();
	//フェードインの開始
	fade_->FadeInStart();

	// サウンド読み込み
	titlebgmHandle_ = audio_->LoadWave("BGM/Sound_Wave.mp3");
	playTitleBgm_ = audio_->PlayWave(titlebgmHandle_, true, 0.1f);
	
	isLule_ = false;
	// ボタンクールダウン
	ButtonCoolDown_=60;
}

void TitleScene::Update() {
	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;
	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		ButtonCoolDown_--;
		if (isLule_ == false) {
			if (subTitleColor2_.w >= 1.0f) {
				if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A && fadeTimerFlag_ == false) {
					if (ButtonCoolDown_ <= 0) {
						fadeTimerFlag_ = true;
						fade_->FadeOutStart();
						ButtonCoolDown_ = 60;
					}
				}

				if (fadeTimerFlag_ == true) {
					fadeTimer_--;
				}

				if (fadeTimer_ <= 0) {

					isSceneEnd_ = true;
				}
			}
		}
	}

	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd_ = true;
	}


	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X && fadeTimerFlag_ == false) {
		isLule_ = true;
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B && isLule_ == true && fadeTimerFlag_==false) {
		isLule_ = false;
	}


	//仮
	/*static int sc = 20000;
	ImGui::Begin("Score");
	ImGui::SliderInt("Pos", &sc, 0, 20000);
	ImGui::End();

	score_->Update(sc);

	ranking_->Update(sc);*/

	subTitleColor_.w += 0.01f;
	if (subTitleColor_.w>=1.0f) {
		subTitleColor1_.w += 0.01f;
	}
	if (subTitleColor1_.w >= 0.5f) {
		subTitleColor2_.w += 0.01f;
	}

	// 天球の更新
	spacedome_->Update();

	// フェードの更新
	fade_->Update();

	//sc = 0;
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
	if (subTitleColor2_.w >= 1.0f) {
		textureTitle_->Draw();
	}
	

	textureSubTitle_->SetColor(subTitleColor_);
	textureSubTitle1_->SetColor(subTitleColor1_);
	textureSubTitle2_->SetColor(subTitleColor2_);

	textureSubTitle_->Draw();
	textureSubTitle1_->Draw();
	textureSubTitle2_->Draw();

	textureFullScreen_->Draw();
	
	if (isLule_==true) {
		textureLule_->Draw();
	}

	// フェードの描画
	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void TitleScene::SceneReset() {
	// フェードインの開始
	fade_->FadeInStart();
	isSceneEnd_ = false;
	
	fadeTimerFlag_ = false;
	fadeTimer_ = kFadeTimer_;
	ButtonCoolDown_ = 60;
}

void TitleScene::BGMReset() { 
	playTitleBgm_ = audio_->PlayWave(titlebgmHandle_, true, 0.1f); 
}

void TitleScene::BGMStop() { 
	audio_->StopWave(playTitleBgm_); 
}
