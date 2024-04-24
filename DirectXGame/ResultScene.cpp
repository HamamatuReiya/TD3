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
}

void ResultScene::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd_ = true;
	}
}

void ResultScene::Draw() {}

void ResultScene::SceneReset() { isSceneEnd_ = false; }


