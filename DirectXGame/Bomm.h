#pragma once
#include "Model.h"
#include "WorldTransform.h"
#define _USE_MATH_DEFINES
#include <Input.h>
#include "MT.h"
#include <optional>
#include "BaseCharacter.h"

class Bomm : public BaseCharacter {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::vector<Model*>&models)override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection)override;

	// 中心座標を取得
	Vector3 GetCenterPosition() const override;

	void RoopInitialize();

private:
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//ワールド変換
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	// 3Dモデル
	Model* modelBomm_;
 
};
