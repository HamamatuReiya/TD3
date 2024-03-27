#pragma once
#include "Collider.h"
#include <list>
#include"Model.h"
class CollisionManager {
public:
	// リセット
	void Reset();

	/// 当たり判定を行いたいオブジェクトを登録
	void AddCollider(Collider* collider);

	void ChackAllCollisions();

	//初期化
	void Initialize();

	//ワールドトランスフォームの更新
	void UpdateWorldtransform();

	//描画
	void Draw(ViewProjection& viewProjection);

private:
	/// コライダー二つの当たり判定
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	// コライダー
	std::list<Collider*> colliders_;
	////デバッグ表示用モデル
	//std::unique_ptr<Model> colliderModel_;
	// ワールド変換
	WorldTransform worldTransform_;
	
};
