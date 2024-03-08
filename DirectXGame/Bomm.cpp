#include "Bomm.h"

void Bomm::Initialize(Model* modelBomm) { 
	modelBomm_ = modelBomm;
	// 初期化
	worldTransform_.Initialize();
	worldTransform_.scale_ = {10.0f, 10.0f, 10.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 3.5f, 12.0f};
	isAni_ = false;
}

void Bomm::Update() {
	// 上下アニメーション
	if (isAni_ == false) {
		worldTransform_.scale_.y+=0.1f;
		worldTransform_.scale_.x += 0.1f;
		worldTransform_.scale_.z += 0.1f;
		if (worldTransform_.scale_.y>=12) {
			isAni_ = true;
		}
	}
	if (isAni_ == true) {
		worldTransform_.scale_.y -=0.1f;
		worldTransform_.scale_.x -= 0.1f;
		worldTransform_.scale_.z -= 0.1f;
		if (worldTransform_.scale_.y <= 10) {
			isAni_ = false;
		}
	}
	

	
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Bomm::Draw(ViewProjection& viewProjection) { 
	modelBomm_->Draw(worldTransform_, viewProjection);
}
