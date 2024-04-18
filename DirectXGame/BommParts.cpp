#include "BommParts.h"
#include <assert.h>

void BommParts::InitializeStone(Model* model, Vector3 position) {
	// 引数から受け取ったモデルが読み込まれているかチェック
	assert(model);
	modelStone_ = model;

	// 引数で受け取った初期座標をセット
	worldTransformStone_.translation_ = position;

	// ワールドトランスフォームの初期化
	worldTransformStone_.Initialize();
}

void BommParts::InitializeGold(Model* model, Vector3 position) {
	// 引数から受け取ったモデルが読み込まれているかチェック
	assert(model);
	modelGold_ = model;

	// 引数で受け取った初期座標をセット
	worldTransformGold_.translation_ = position;

	// ワールドトランスフォームの初期化
	worldTransformGold_.Initialize();
}

void BommParts::InitializeJushi(Model* model, Vector3 position) {
	// 引数から受け取ったモデルが読み込まれているかチェック
	assert(model);
	modelJushi_ = model;

	// 引数で受け取った初期座標をセット
	worldTransformJushi_.translation_ = position;

	// ワールドトランスフォームの初期化
	worldTransformJushi_.Initialize();
}

void BommParts::InitializeShell(Model* model, Vector3 position) {
	// 引数から受け取ったモデルが読み込まれているかチェック
	assert(model);
	modelShell_ = model;

	// 引数で受け取った初期座標をセット
	worldTransformShell_.translation_ = position;

	// ワールドトランスフォームの初期化
	worldTransformShell_.Initialize();
}

void BommParts::Update() { 
	worldTransformStone_.UpdateMatrix(); 
	worldTransformGold_.UpdateMatrix();
	worldTransformJushi_.UpdateMatrix();
	worldTransformShell_.UpdateMatrix();
}

void BommParts::Draw(const ViewProjection& viewProjection) {
	modelStone_->Draw(worldTransformStone_, viewProjection);
	modelGold_->Draw(worldTransformGold_, viewProjection);
	modelJushi_->Draw(worldTransformJushi_, viewProjection);
	modelShell_->Draw(worldTransformShell_, viewProjection);
}

void BommParts::OnCollision() { isDead_ = true; }

Vector3 BommParts::GetWorldPositionStone() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransformStone_.matWorld_.m[3][0];
	worldPos.y = worldTransformStone_.matWorld_.m[3][1];
	worldPos.z = worldTransformStone_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 BommParts::GetWorldPositionGold() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransformGold_.matWorld_.m[3][0];
	worldPos.y = worldTransformGold_.matWorld_.m[3][1];
	worldPos.z = worldTransformGold_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 BommParts::GetWorldPositionJushi() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransformJushi_.matWorld_.m[3][0];
	worldPos.y = worldTransformJushi_.matWorld_.m[3][1];
	worldPos.z = worldTransformJushi_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 BommParts::GetWorldPositionShell() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransformShell_.matWorld_.m[3][0];
	worldPos.y = worldTransformShell_.matWorld_.m[3][1];
	worldPos.z = worldTransformShell_.matWorld_.m[3][2];

	return worldPos;
}