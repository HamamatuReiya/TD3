﻿#include "ResultScene.h"


ResultScene::ResultScene() {}

ResultScene::~ResultScene() {}

void ResultScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	isSceneEnd_ = false;

	resultTextTex[0] = TextureManager::Load("./Resources/resultText1.png");
	resultTextTex[1] = TextureManager::Load("./Resources/resultText2.png");
	resultTextTex[2] = TextureManager::Load("./Resources/resultText3.png");

	resultText[0] = Sprite::Create(resultTextTex[0], {0, 0}, {1, 1, 1, 1}, {0, 0});
	resultText[1] = Sprite::Create(resultTextTex[1], {0, 0}, {1, 1, 1, 1}, {0, 0});
	resultText[2] = Sprite::Create(resultTextTex[2], {-20, 0}, {1, 1, 1, 1}, {0, 0});

	bommLvTex = TextureManager::Load("./Resources/Lv.png");
	bommLv = Sprite::Create(bommLvTex, {480, 314}, {1,1,1,1}, {0,0});

	fade_ = std::make_unique<Fade>();
	fade_->Initialize();

	// 天球
	// 3Dモデルの生成
	modelSpacedome_.reset(Model::CreateFromOBJ("spacedome", true));
	// 天球の生成
	spacedome_ = std::make_unique<Spacedome>();
	// 天球の初期化
	spacedome_->Initialize(modelSpacedome_.get());

	bommEnhance_ = std::make_unique<BommEnhance>();

		// 所持数UIの生成
	itemCounter_ = std::make_unique<ItemCounter>();
	itemCounter_->Initialize();

	resultEarth_ = std::make_unique<ResultEarth>();

	resultEarthModel_[0].reset(Model::CreateFromOBJ("ResultEarth1", true));
	resultEarthModel_[1].reset(Model::CreateFromOBJ("ResultEarth2", true));
	resultEarthModel_[2].reset(Model::CreateFromOBJ("ResultEarth3", true));
	resultEarthModel_[3].reset(Model::CreateFromOBJ("ResultEarth4", true));
	resultEarthModel_[4].reset(Model::CreateFromOBJ("ResultEarth5", true));
	resultEarthModel_[5].reset(Model::CreateFromOBJ("ResultEarth6", true));
	resultEarthModel_[6].reset(Model::CreateFromOBJ("ResultEarth7", true));
	resultEarthModel_[7].reset(Model::CreateFromOBJ("ResultEarth8", true));
	resultEarthModel_[8].reset(Model::CreateFromOBJ("ResultEarth9", true));
	resultEarthModel_[9].reset(Model::CreateFromOBJ("ResultEarth10", true));
	resultEarthModel_[10].reset(Model::CreateFromOBJ("ResultEarth11", true));
	resultEarthModel_[11].reset(Model::CreateFromOBJ("ResultEarth12", true));
	resultEarthModel_[12].reset(Model::CreateFromOBJ("ResultEarth13", true));
	resultEarthModel_[13].reset(Model::CreateFromOBJ("ResultEarth14", true));

	resultEarth_->Initialize(
	    resultEarthModel_[0].get(), resultEarthModel_[1].get(), resultEarthModel_[2].get(),
	    resultEarthModel_[3].get(), resultEarthModel_[4].get(), resultEarthModel_[5].get(),
	    resultEarthModel_[6].get(), resultEarthModel_[7].get(), resultEarthModel_[8].get(),
	    resultEarthModel_[9].get(), resultEarthModel_[10].get(), resultEarthModel_[11].get(),
	    resultEarthModel_[12].get(), resultEarthModel_[13].get());


	//サウンド読み込み
	resultbgmHandle_ = audio_->LoadWave("BGM/ResultBgm.mp3");
}

void ResultScene::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd_ = true;
	}

	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A && fadeFlag_ == false) {
			fadeFlag_ = true;
			fade_->FadeOutStart();
		}
	}
	if (fadeFlag_ == true) {
		fadeTimer_--;
	}
	if (fadeTimer_ <= 0) {
		isSceneEnd_ = true;
	}

	fade_->Update();

	// 天球の更新
	spacedome_->Update();

	resultEarth_->Update();

	//itemCounter_->Update();

}

void ResultScene::Draw() {
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

	resultEarth_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//itemCounter_->Draw();
	bommEnhance_->ResultDraw();
	bommLv->Draw();
	if (bommEnhance_->GetBommLv() <= 9) {
		resultText[0]->Draw();
	} else if (bommEnhance_->GetBommLv() >= 10) {
		resultText[1]->Draw();
	}
	resultText[2]->Draw();

	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void ResultScene::SceneReset() { 
	fadeFlag_ = false;
	isSceneEnd_ = false;
	fadeTimer_ = kFadeTimer_;
}

void ResultScene::BGMReset() { 
	playResultBgm_ = audio_->PlayWave(resultbgmHandle_, true, 0.1f); 
}

void ResultScene::BGMStop() { 
	audio_->StopWave(playResultBgm_); }


