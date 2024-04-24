﻿#include "Bomm.h"

void Bomm::Initialize(const std::vector<Model*>& models) {
	BaseCharacter::Initialize(models);
	// 初期化
	worldTransform_.Initialize();
	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 2.0f, 0.0f};
}

void Bomm::Update() {
	
	//アニメーション
	worldTransform_.rotation_.y += 0.02f;

	worldTransform_.parent_ = &worldTransform_;

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Bomm::Draw(const ViewProjection& viewProjection) { 
	models_[0]->Draw(worldTransform_, viewProjection);
}

Vector3 Bomm::GetCenterPosition() const { 
	// ローカル座標のオフセット
	const Vector3 offset = {0.0f, -0.5f, 0.0f};
	// ワールド座標変換
	Vector3 worldPos = Transform(offset, worldTransform_.matWorld_);

	return worldPos;
}

void Bomm::RoopInitialize() {// 初期化
	worldTransform_.Initialize();
	worldTransform_.scale_ = {3.0f, 3.0f, 3.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 2.0f, 0.0f};
}
