#include "FixedCamera.h"

void FixedCamera::Initialize() {
	// x,y,zの方向のを設定
	worldTransform_.translation_ = {0.0f, 10.0f, -50.0f};

	// ワールド変換の初期化
	worldTransform_.Initialize();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void FixedCamera::Update() {
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    {1.0f, 1.0f, 1.0f}, worldTransform_.rotation_, worldTransform_.translation_);

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
}
