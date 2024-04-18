#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <math.h>
#include <sstream>

class BommParts {
public:

	/// <summary>
	/// 初期化　樹脂
	/// </summary>
	void InitializeJushi(Model* model, Vector3 position);

	/// <summary>
	/// 初期化　貝
	/// </summary>
	void InitializeShell(Model* model, Vector3 position);

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
	Vector3 GetWorldPositionJushi();
	// ワールド座標を取得
	Vector3 GetWorldPositionShell();

	bool IsDead() const { return isDead_; }

private:

	
	
	// ワールド変換データ　樹脂
	WorldTransform worldTransformJushi_;
	// ワールド変換データ　貝
	WorldTransform worldTransformShell_;

	// 3Dモデル

	
	Model* modelJushi_;
	Model* modelShell_;

	// デスフラグ
	bool isDead_ = false;

};
