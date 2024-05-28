#include "Earth.h"

void Earth::Initialize(Model* model, float pos) {
	scale = {10.0f, 10.0f, 10.0f};
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {pos, 0.0f, 0.0f};
}

void Earth::Update() { 
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_.y += 0.01f;
	worldTransform_.UpdateMatrix(); }

void Earth::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection); 
}
