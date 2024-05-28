#include "ResultEarth.h"

void ResultEarth::Initialize(
    Model* model, Model* model1, Model* model2, Model* model3, Model* model4, Model* model5,
    Model* model6, Model* model7, Model* model8, Model* model9, Model* model10, Model* model11,
    Model* model12, Model* model13) {
	model_[0] = model;
	model_[1] = model1;
	model_[2] = model2;
	model_[3] = model3;
	model_[4] = model4;
	model_[5] = model5;
	model_[6] = model6;
	model_[7] = model7;
	model_[8] = model8;
	model_[9] = model9;
	model_[10] = model10;
	model_[11] = model11;
	model_[12] = model12;
	model_[13] = model13;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {13.0f, 13.0f, 13.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {-4.0f, 0.0f, 0.0f};

	speed = 0.001f;

}

void ResultEarth::Update() { 

	worldTransform_.translation_.y += speed;

	if (worldTransform_.translation_.y >= 0.15f) {
		speed *= -1;
	} else if (worldTransform_.translation_.y <= -0.15f) {
		speed *= -1;
	}

	worldTransform_.UpdateMatrix();
}

void ResultEarth::Draw(ViewProjection& viewProjection) {
	model_[0]->Draw(worldTransform_, viewProjection);
	model_[1]->Draw(worldTransform_, viewProjection);
	model_[2]->Draw(worldTransform_, viewProjection);
	model_[3]->Draw(worldTransform_, viewProjection);
	model_[4]->Draw(worldTransform_, viewProjection);
	model_[5]->Draw(worldTransform_, viewProjection);
	model_[6]->Draw(worldTransform_, viewProjection);
	model_[7]->Draw(worldTransform_, viewProjection);
	model_[8]->Draw(worldTransform_, viewProjection);
	model_[9]->Draw(worldTransform_, viewProjection);
	model_[10]->Draw(worldTransform_, viewProjection);
	model_[11]->Draw(worldTransform_, viewProjection);
	model_[12]->Draw(worldTransform_, viewProjection);
	model_[13]->Draw(worldTransform_, viewProjection);
}

void ResultEarth::RoopInitialize() {}
