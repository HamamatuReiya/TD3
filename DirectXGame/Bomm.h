#pragma once
#include "Model.h"
#include "WorldTransform.h"
#define _USE_MATH_DEFINES
#include <Input.h>
#include <math.h>
#include <optional>

class Bomm {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* modelBomm);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//ワールド変換
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	// 3Dモデル
	Model* modelBomm_;
	//上下アニメーション
	bool isAni_;
	

};
