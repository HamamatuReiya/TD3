#pragma once
#include <Vector3.h>
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"

class Collider {
public:
	virtual ~Collider() = default;
	// 衝突時に呼ばれる関数
	virtual void OnCollision() {}
	// 中心座標を取得
	virtual Vector3 GetCenterPosition() const = 0;

	// 半径を取得
	float GetRadius() { return radius_; }
	// 半径を設定
	void SetRadius(float radius) { radius_ = radius; }
	//初期化
	void Initialize();
	//ワールドトランスフォームの更新
	void UpdateWorldTransform();
	


	/*/// <summary>
	/// 描画
	/// </summary>
	void Draw(Model* model,const ViewProjection& viewProjection);*/

private:
	// 衝突半径
	float radius_ = 1.5f;
	//ワールド変換
	WorldTransform worldTransform_;
};
