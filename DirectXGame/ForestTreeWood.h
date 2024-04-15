#pragma once
#include "Model.h"
#include "WorldTransform.h"

class ForestTreeWood {
public:
	/// <summary>
	/// 更新
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
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};
