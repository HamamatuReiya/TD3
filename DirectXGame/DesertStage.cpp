#include "DesertStage.h"

DesertStage::DesertStage() {}

DesertStage::~DesertStage() {}

void DesertStage::Initialize() {

	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

		// 数字の画像
	uint32_t numHandle;
	numHandle = TextureManager::Load("./Resources/number/0.png");

	// 取得した数
	textureNumber_ =
	    Sprite::Create(numHandle, {50.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}

void DesertStage::Update() {

}

void DesertStage::Draw() {
	textureNumber_->Draw();
}

void DesertStage::StageReset() {}