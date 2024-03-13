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
	void Initialize(Model* modelBomm);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	// 中心座標を取得
	Vector3 GetCenterPosition() const override;

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
