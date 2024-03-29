﻿#include "Spacedome.h"
#include "cassert"

void Spacedome::Initialize(Model* model) {
	// 引数から受け取ったモデルが読み込まれているかチェック
	assert(model);
	// 引数からモデルとテクスチャハンドルを受け取る
	model_ = model;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// x,y,z方向のスケーリングを設定
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	// x,y,z方向の回転を設定
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	// x,y,zの方向のを設定
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Spacedome::Update() { 
	worldTransform_.UpdateMatrix();
	worldTransform_.rotation_.y += 0.0005f;
}

void Spacedome::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
