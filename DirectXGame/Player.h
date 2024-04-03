#include "Model.h"
#include "WorldTransform.h"
#define _USE_MATH_DEFINES
#include <Input.h>
#include <math.h>
#include <optional>
#include "BaseCharacter.h"
#include "UI.h"

class Player : public BaseCharacter {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::vector<Model*>& models) override;

	/// <summary>
	/// 自キャラ
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection)override;

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
	/// ジャンプモーション初期化
	/// </summary>
	void BehaviorJumpInitialize();

	/// <summary>
	/// ジャンプモーション更新
	/// </summary>
	void BehaviorJumpUpdate();

	/// <summary>
	/// モーション
	/// </summary>
	enum class Motion {
		kRun,
		kPick,
		kDive,
		kJump,
	};

	enum class Collision {
		On,
		Out
	};

	/// <summary>
	/// Getter&Setter
	/// </summary>
	WorldTransform& GetWorldTransform() { return worldTransform_; };

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	void OnCollision() override;

	bool GetIsPushX() { return isPushX_; }

	void OutCollision();
	
	Vector3 GetWorldPosition();


	// 中心座標を取得
	Vector3 GetCenterPosition() const override;
	
	/*void SetWorldTransform(WorldTransform worldTransform) {
		worldTransform_ = worldTransform;
	}*/


	/// <summary>
	/// 爆弾との当たり判定
	/// </summary>
	int SetBommCollider_() { return isBommCollider_; }

private:
	//ワールド変換
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm;
	WorldTransform worldTransformR_arm;
	WorldTransform worldTransformL_leg;
	WorldTransform worldTransformR_leg;
	// ビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	// 3Dモデル
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm;
	Model* modelFighterR_arm;
	Model* modelFighterL_leg;
	Model* modelFighterR_leg;
	// 浮遊ギミック媒介変数変数
	float floatingParamerer_ = 0.0f;
	Vector3 velocity_ = {};
	
	//モーション初期化
	Motion motion_ = Motion::kRun;
	std::optional<Motion> motionRequest_ = std::nullopt;
	// コライダー初期化
	Collision collider_ = Collision::Out;

	bool isPushX_;

	//モーションタイム
	float PickMotionTime_;
	float LegMotionTime_;
	bool isLeftLeg_;
	bool isRightLeg_;
	//腕ディレイ
	float ArmDelayTime_;

	//衝突してるか
	bool isBommCollider_;


};