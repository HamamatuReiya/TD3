﻿#include "Bomm.h"

void Bomm::Initialize(const std::vector<Model*>& models) {
	BaseCharacter::Initialize(models);
	/*modelBomm_ = modelBomm;*/
	// 初期化
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 10.0f};
	isAni_ = false;
}



void Bomm::Update() {
	//// 上下アニメーション
	//if (isAni_ == false) {
	//	worldTransform_.scale_.y+=0.1f;
	//	worldTransform_.scale_.x += 0.1f;
	//	worldTransform_.scale_.z += 0.1f;
	//	if (worldTransform_.scale_.y>=12) {
	//		isAni_ = true;
	//	}
	//}
	//if (isAni_ == true) {
	//	worldTransform_.scale_.y -=0.1f;
	//	worldTransform_.scale_.x -= 0.1f;
	//	worldTransform_.scale_.z -= 0.1f;
	//	if (worldTransform_.scale_.y <= 10) {
	//		isAni_ = false;
	//	}
	//}
	
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Bomm::Draw(const ViewProjection& viewProjection) { 
	models_[0]->Draw(worldTransform_, viewProjection);
}

Vector3 Bomm::GetCenterPosition() const { 
	// ローカル座標のオフセット
	const Vector3 offset = {0.0f, 1.5f, 0.0f};
	// ワールド座標変換
	Vector3 worldPos = Transform(offset, worldTransform_.matWorld_);

	return worldPos;
}
