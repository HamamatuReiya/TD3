﻿#include "Player.h"
#include "MT.h"
#include <ImGuiManager.h>

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
	worldTransformL_arm.translation_ = {0.0f, 3.0f, 0.0f};
	// 右腕の初期化
	worldTransformR_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm.translation_ = {0.0f, 3.0f, 0.0f};
	// 左脚の初期化
	worldTransformL_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_leg.translation_ = {0.0f, 0.0f, 0.0f};
	// 右脚の初期化
	worldTransformR_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_leg.translation_ = {0.0f, 0.0f, 0.0f};
}

void Player::MotionRunInitialize() { 
	MotionPickInitialize();
	MotionDiveInitialize();
}

void Player::MotionPickInitialize() { 
	//モーション時間初期化
	PickMotionTime_ = 0;
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
	worldTransformL_arm.translation_ = {0.0f, 3.0f, 0.0f};
	// 右腕の初期化
	worldTransformR_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm.translation_ = {0.0f, 3.0f, 0.0f};
	// 左脚の初期化
	worldTransformL_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_leg.translation_ = {0.0f, 0.0f, 0.0f};
	// 右脚の初期化
	worldTransformR_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_leg.translation_ = {0.0f, 0.0f, 0.0f};
}

void Player::MotionDiveInitialize() {
	// 場所初期化
	worldTransformBody_.rotation_.x = 0.0f;
	
}


void Player::Update() {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 拾うモーション
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_X) {
			motionRequest_ = Motion::kPick;
		}
		// 潜るモーション
		if (worldTransform_.translation_.x<=-12) {
			motionRequest_ = Motion::kDive;
		} else {
			ArmDelayTime_ = 0;
		}
		// モーション切り替え
		if (motionRequest_) {
			motion_ = motionRequest_.value();
			switch (motion_) {
			case Motion::kRun:
			default:
				MotionRunInitialize();
				break;
			case Motion::kPick:
				MotionPickInitialize();
				break;
			case Motion::kDive:
				MotionDiveInitialize();
				break;
			}
			motionRequest_ = std::nullopt;
		}
		switch (motion_) {
		case Motion::kRun:
		default:
			MotionRunUpdate();
			break;
		case Motion::kPick:
			MotionPickUpdate();
			break;
		case Motion::kDive:
			MotionDiveUpdate();
			break;
		}

		// 行列の更新
		worldTransform_.UpdateMatrix();
		worldTransformBody_.UpdateMatrix();
		worldTransformHead_.UpdateMatrix();
		worldTransformL_arm.UpdateMatrix();
		worldTransformR_arm.UpdateMatrix();
		worldTransformL_leg.UpdateMatrix();
		worldTransformR_leg.UpdateMatrix();
	}

#ifdef _DEBUG
	// デバック
	float playerPos[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	// デバック
	float playerRot[3] = {
	    worldTransform_.rotation_.x, worldTransform_.rotation_.y,
		worldTransform_.rotation_.z};
	// 画面の座標を表示
	ImGui::Begin("Player");
	ImGui::SliderFloat3("Pos", playerPos, -28.0f, 28.0f);
	ImGui::SliderFloat3("Rot", playerRot, -28.0f, 28.0f);
	ImGui::End();
	//移動
	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];
	//回転
	worldTransform_.rotation_.x = playerRot[0];
	worldTransform_.rotation_.y = playerRot[1];
	worldTransform_.rotation_.z = playerRot[2];
#endif !_DEBUG
}

void Player::MotionRunUpdate() {
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
		move = Multiply(speed, Normalize(move));

		move = TransformNormal(move, MakeRotateYmatrix(viewProjection_->rotation_.y));

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

		if (Length(move) != 0) {
			worldTransform_.rotation_.y = std::atan2(move.x, move.z);
		}
	}
};

void Player::MotionPickUpdate() { 
	// 拾うモーション時間
	PickMotionTime_++;

	//腕
	if (PickMotionTime_ < 7.5f) {
		worldTransformR_arm.rotation_.x -= 0.1f;
		worldTransformR_arm.translation_.y -= 0.05f;
		worldTransformL_arm.translation_.y -= 0.05f;
	} else {
		worldTransformR_arm.rotation_.x += 0.1f;
		worldTransformR_arm.translation_.y += 0.05f;
		worldTransformL_arm.translation_.y += 0.05f;
	}
	//体と頭
	if (PickMotionTime_ < 7.5f) {
		worldTransformBody_.translation_.y -= 0.05f;
		worldTransformHead_.translation_.y -= 0.05f;
	} else {
		worldTransformBody_.translation_.y += 0.05f;
		worldTransformHead_.translation_.y += 0.05f;
	}
	
	// 拾うモーション時間
	if (PickMotionTime_>15.0f) {
		motionRequest_ = Motion::kRun;
	} else {
		worldTransform_.translation_.y =  0.0f;
	}
}

void Player::MotionDiveUpdate() {
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
		move = Multiply(speed, Normalize(move));

		move = TransformNormal(move, MakeRotateYmatrix(viewProjection_->rotation_.y));

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

		if (Length(move) != 0) {
			worldTransform_.rotation_.y = std::atan2(move.x, move.z);
		}
	}

	// 腕
	worldTransformR_arm.rotation_.x += 0.3f;
	ArmDelayTime_++;
	if (ArmDelayTime_>5) {
		worldTransformL_arm.rotation_.x += 0.3f;
	}
	worldTransformR_arm.translation_.y = 0.2f;
	worldTransformL_arm.translation_.y = 0.2f;
	worldTransformR_arm.translation_.z = 1.35f;
	worldTransformL_arm.translation_.z = 1.35f;
	
	// 体
	worldTransformBody_.rotation_.x = -30.0f;
	worldTransformBody_.translation_.y = 0.2f;
	worldTransformBody_.translation_.z = -1.5f;

	// 頭
	worldTransformHead_.translation_.y = -0.05f;
	worldTransformHead_.translation_.z = 2.2f;

	//足
	worldTransformL_leg.translation_.z = -1.5f;
	worldTransformR_leg.translation_.z = -1.5f;
	worldTransformR_leg.rotation_.x = 1.4f;
	worldTransformL_leg.rotation_.x = 1.4f;


	// 潜るモーション範囲
	if (worldTransform_.translation_.x > -12) {
		motionRequest_ = Motion::kRun;
	}
	
}


void Player::Draw(ViewProjection& viewProjection) {
	modelFighterBody_->Draw(worldTransformBody_, viewProjection);
	modelFighterHead_->Draw(worldTransformHead_, viewProjection);
	modelFighterL_arm->Draw(worldTransformL_arm, viewProjection);
	modelFighterR_arm->Draw(worldTransformR_arm, viewProjection);
	modelFighterL_leg->Draw(worldTransformL_leg, viewProjection);
	modelFighterR_leg->Draw(worldTransformR_leg, viewProjection);
}


