#include "Model.h"
#include "WorldTransform.h"
#define _USE_MATH_DEFINES
#include "Input.h"
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
	/// 走るモーション更新
	/// </summary>
	void MotionRunUpdate();

	/// <summary>
	/// 拾うモーション更新
	/// </summary>
	void MotionPickUpdate();


	/// <summary>
	/// ジャンプモーション初期化
	/// </summary>
	void MotionJumpInitialize();

	/// <summary>
	/// ジャンプモーション更新
	/// </summary>
	void MotionJumpUpdate();

	/// <summary>
	/// 斧モーション初期化
	/// </summary>
	void MotionAxeInitialize();

	/// <summary>
	/// 斧モーション更新
	/// </summary>
	void MotionAxeUpdate();

	/// <summary>
	/// モーション
	/// </summary>
	enum class Motion {
		kRun,
		kPick,
		kJump,
		kAxe,
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
	
	Vector3 GetWorldPosition();

	float SetTranslationX(float pos) { return worldTransform_.translation_.x = pos; }
	float SetTranslationY(float pos) { return worldTransform_.translation_.y = pos; }
	float SetTranslationZ(float pos) { return worldTransform_.translation_.z = pos; }

	bool GetIsController() { return isController; }
	bool SetIsController(bool controllerFlag) { return isController = controllerFlag; }

	// 中心座標を取得
	Vector3 GetCenterPosition() const override;

	//アクションボタン
	void ActionButtonUpdate();
	//アクションボタン描画
	void ActionbuttonDraw();

	//Imgui
	void Debug();

	/// <summary>
	/// アクションボタン
	/// </summary>
	int GetActionbutton() { return isInvestigatebutton_; }

	void SetMotion();

	void RoopInitialize();

private:
	//ワールド変換
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm;
	WorldTransform worldTransformR_arm;
	WorldTransform worldTransformL_leg;
	WorldTransform worldTransformR_leg;
	WorldTransform worldTransformAxe_;
	// ビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	//インプット
	Input* input_ = nullptr;
	// 3Dモデル
	Model* model_ = nullptr;
	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm;
	Model* modelFighterR_arm;
	Model* modelFighterL_leg;
	Model* modelFighterR_leg;
	//斧
	Model* modelAxe_;
	// 浮遊ギミック媒介変数変数
	float floatingParamerer_ = 0.0f;
	Vector3 velocity_ = {};
	
	//モーション初期化
	Motion motion_ = Motion::kRun;
	std::optional<Motion> motionRequest_ = std::nullopt;

	bool isPushX_;

	//モーションタイム
	float PickMotionTime_;
	float LegMotionTime_;
	bool isLeftLeg_;
	bool isRightLeg_;
	//腕ディレイ
	float ArmDelayTime_;

	//調べるボタン
	bool isInvestigatebutton_;

	// スプライト
	Sprite* spriteButton_ = nullptr; 

	//斧フラグ
	bool useAxe_;

	// スタートフラグ
	int isStartTimer_;

	//コントローラーの入力フラグ
	bool isController;
};