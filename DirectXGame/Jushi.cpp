#include "Jushi.h"
#include <assert.h>
#include <ImGuiManager.h>

void Jushi::Initialize(Model* model, Vector3 position) {
	// 引数から受け取ったモデルが読み込まれているかチェック
	assert(model);
	model_ = model;

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	isExclamation_ = false;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

void Jushi::Update() { 
	worldTransform_.UpdateMatrix();
}

void Jushi::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}

void Jushi::OnCollision() { isDead_ = true; }

Vector3 Jushi::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
