#include "Explosion.h"

void Explosion::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Explosion::Update() {
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Explosion::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}
