#include "ForestTreeWood.h"

void ForestTreeWood::Initialize(
    Model* model, Model* model1, Model* model2, Model* model3, Model* model4, Model* model5,
    Model* model6, Model* model7, Model* model8, Model* model9) {
	model_ = model;
	model1_ = model1;
	model2_ = model2;
	model3_ = model3;
	model4_ = model4;
	model5_ = model5;
	model6_ = model6;
	model7_ = model7;
	model8_ = model8;
	model9_ = model9;

	for (int i = 0; i < 10; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_[i].rotation_ = {0.0f, 0.0f, 0.0f};
	}
	worldTransform_[0].translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[1].translation_ = {0.0f, 0.0f, -100.0f};
	worldTransform_[2].translation_ = {-100.0f, 0.0f, 0.0f};
	worldTransform_[3].translation_ = {-100.0f, 0.0f, -100.0f};
	worldTransform_[4].translation_ = {-200.0f, 0.0f, 0.0f};
	worldTransform_[5].translation_ = {-200.0f, 0.0f, -100.0f};
	worldTransform_[6].translation_ = {-200.0f, 0.0f, -200.0f};
	worldTransform_[7].translation_ = {0.0f, 0.0f, -200.0f};
	worldTransform_[8].translation_ = {-100.0f, 0.0f, -200.0f};
	worldTransform_[9].translation_ = {-300.0f, 0.0f, -200.0f};
}

void ForestTreeWood::Update() {
	for (int i = 0; i < 10; i++) {
		// 行列の更新
		worldTransform_[i].UpdateMatrix();
	}
}

void ForestTreeWood::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_[0], viewProjection);
	model1_->Draw(worldTransform_[1], viewProjection);
	model2_->Draw(worldTransform_[2], viewProjection);
	model3_->Draw(worldTransform_[3], viewProjection);
	model4_->Draw(worldTransform_[4], viewProjection);
	model5_->Draw(worldTransform_[5], viewProjection);
	model6_->Draw(worldTransform_[6], viewProjection);
	model7_->Draw(worldTransform_[7], viewProjection);
	model8_->Draw(worldTransform_[8], viewProjection);
	model9_->Draw(worldTransform_[9], viewProjection);
}
