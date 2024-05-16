#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Explosion {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// ワールド変換
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};
