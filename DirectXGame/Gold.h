#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <math.h>
#include <sstream>

class Gold {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Vector3 position);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

public:
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	bool IsDead() const { return isDead_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// 3Dモデル
	Model* model_;

	// デスフラグ
	bool isDead_ = false;
};
