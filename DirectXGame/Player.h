#include "Model.h"
#include "WorldTransform.h"
#define _USE_MATH_DEFINES
#include <Input.h>
#include <math.h>
#include <optional>
class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm);

	/// <summary>
	/// 自キャラ
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// 走るモーション初期化
	/// </summary>
	void MotionRunInitialize();

	/// <summary>
	/// 拾うモーション初期化
	/// </summary>
	void MotionPickInitialize();

	/// <summary>
	/// 潜るモーション初期化
	/// </summary>
	void MotionDiveInitialize();

	/// <summary>
	/// 走るモーション更新
	/// </summary>
	void MotionRunUpdate();

	/// <summary>
	/// 拾うモーション更新
	/// </summary>
	void MotionPickUpdate();

	/// <summary>
	/// 潜るモーション更新
	/// </summary>
	void MotionDiveUpdate();

	/// <summary>
	/// モーション
	/// </summary>
	enum class Motion {
		kRun,
		kPick,
		kDive
	};

	/// <summary>
	/// Getter&Setter
	/// </summary>
	WorldTransform& GetWorldTransform() { return worldTransform_; };

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

private:
	//ワールド変換
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm;
	WorldTransform worldTransformR_arm;
	// ビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	// 3Dモデル
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm;
	Model* modelFighterR_arm;
	
	//モーション初期化
	Motion motion_ = Motion::kRun;
	std::optional<Motion> motionRequest_ = std::nullopt;

	//モーションタイム
	float PickMotionTime_;
	//腕ディレイ
	float ArmDelayTime_;

	
};