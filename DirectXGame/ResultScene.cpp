#include "ResultSCene.h"



ResultScene::ResultScene() {}

ResultScene::~ResultScene() {}

void ResultScene::Initialize() {

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	// �r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
}

void ResultScene::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd_ = true;
	}
}

void ResultScene::Draw() {}

void ResultScene::SceneReset() {}


