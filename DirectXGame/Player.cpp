#include "Player.h"
#include "MT.h"

void Player::Initialize(
    Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm, Model* modelL_leg,
    Model* modelR_leg) {

	modelFighterBody_ = modelBody;
	modelFighterHead_ = modelHead;
	modelFighterL_arm = modelL_arm;
	modelFighterR_arm = modelR_arm;
	modelFighterL_leg = modelL_leg;
	modelFighterR_leg = modelR_leg;

	// 初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm.Initialize();
	worldTransformR_arm.Initialize();
	worldTransformL_leg.Initialize();
	worldTransformR_leg.Initialize();
	// 初期化
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	// 体の初期化
	worldTransformBody_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformBody_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.translation_ = {0.0f, 0.0f, 0.0f};
	// 頭の初期化
	worldTransformHead_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformHead_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHead_.translation_ = {0.0f, 3.0f, 0.0f};
	// 左腕の初期化
	worldTransformL_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_arm.translation_ = {0.0f, 0.0f, 0.0f};
	// 右腕の初期化
	worldTransformR_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm.translation_ = {0.0f, 0.0f, 0.0f};
	// 左脚の初期化
	worldTransformL_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_leg.translation_ = {0.0f, -2.0f, 0.0f};
	// 右脚の初期化
	worldTransformR_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_leg.translation_ = {0.0f, -2.0f, 0.0f};
}

void Player::Update() {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;
		worldTransformBody_.parent_ = &worldTransform_;
		worldTransformHead_.parent_ = &worldTransform_;
		worldTransformL_arm.parent_ = &worldTransform_;
		worldTransformR_arm.parent_ = &worldTransform_;
		worldTransformL_leg.parent_ = &worldTransform_;
		worldTransformR_leg.parent_ = &worldTransform_;
		// 移動量
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * -speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * -speed};
		// 移動量に速さを反映
		move = VectorMultiply(speed, Normalize(move));

		move = TransformNormal(move, MakeRotateYMatrix(viewProjection_->rotation_.y));

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

		if (move.z != 0 || move.y != 0) {
			worldTransform_.rotation_.y = std::atan2(move.x, move.z);
		}
	};

	// 行列の更新
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm.UpdateMatrix();
	worldTransformR_arm.UpdateMatrix();
	worldTransformL_leg.UpdateMatrix();
	worldTransformR_leg.UpdateMatrix();
}

void Player::InitializeFloatingGimmick() { floatingParamerer_ = 0.0f; }


void Player::Draw(ViewProjection& viewProjection) {
	modelFighterBody_->Draw(worldTransformBody_, viewProjection);
	modelFighterHead_->Draw(worldTransformHead_, viewProjection);
	modelFighterL_arm->Draw(worldTransformL_arm, viewProjection);
	modelFighterR_arm->Draw(worldTransformR_arm, viewProjection);
	modelFighterL_leg->Draw(worldTransformL_leg, viewProjection);
	modelFighterR_leg->Draw(worldTransformR_leg, viewProjection);
}
