#include "ResultSCene.h"



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

	//サウンド読み込み
	resultbgmHandle_ = audio_->LoadWave("BGM/ResultBgm.mp3");
}

void ResultScene::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd_ = true;
	}
}

void ResultScene::Draw() {}

void ResultScene::SceneReset() { isSceneEnd_ = false; }

void ResultScene::BGMReset() { 
	playResultBgm_ = audio_->PlayWave(resultbgmHandle_, true, 0.1f); 
}

void ResultScene::BGMStop() { 
	audio_->StopWave(playResultBgm_); }


