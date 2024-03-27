#pragma once

#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class VolcanoStage {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	VolcanoStage();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~VolcanoStage();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	void StageReset();

private: // メンバ変数
	
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
};
