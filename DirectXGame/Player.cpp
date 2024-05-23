#include "Player.h"
#include "MT.h"
#include <ImGuiManager.h>

void Player::Initialize(const std::vector<Model*>& models)
{
	BaseCharacter::Initialize(models);

	isPushX_ = false;
	isController = true;
	for (int x = 0; x < 11; x++) {
		houseInFlag[x] = {false};
		inMoveFlag[x] = {true};
		outMoveFlag[x] = {true};
		isItemGetFlag[x] = {false};
		offFlag[x] = {false};
		itemGetCount[x] = {0};
		itemGetFlag2[x] = {false};
		itemGetFlag3[x] = {false};
	}
	
	// 初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm.Initialize();
	worldTransformR_arm.Initialize();
	worldTransformL_leg.Initialize();
	worldTransformR_leg.Initialize();
	worldTransformAxe_.Initialize();
	// 初期化
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {-1.292f, 0.0f, -30.178f};
	// 体の初期化
	worldTransformBody_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformBody_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.translation_ = {0.0f, 2.0f, 0.0f};
	// 頭の初期化
	worldTransformHead_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformHead_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHead_.translation_ = {0.0f, 5.0f, 0.0f};
	// 左腕の初期化
	worldTransformL_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_arm.translation_ = {0.0f, 5.0f, 0.0f};
	// 右腕の初期化
	worldTransformR_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm.translation_ = {0.0f, 5.0f, 0.0f};
	// 左脚の初期化
	worldTransformL_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_leg.translation_ = {0.0f, 2.0f, 0.0f};
	// 右脚の初期化
	worldTransformR_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_leg.translation_ = {0.0f, 2.0f, 0.0f};
	//斧の初期化
	worldTransformAxe_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformAxe_.rotation_ = {1.077f, 0.0f, 0.0f};
	worldTransformAxe_.translation_ = {2.155f, 2.0f, 1.077f};
	
	//調べるボタン
	isInvestigatebutton_ = false;
	// テクスチャ
	uint32_t textureButton = TextureManager::Load("ActionButton.png");
	// スプライト生成
	spriteButton_ =
	    Sprite::Create(textureButton, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	//
	isStartTimer_ = 0;

	Speed = 0.6f;
}
	

void Player::MotionRunInitialize() { 
	MotionPickInitialize();
	worldTransform_.translation_.y = 0;
}

void Player::MotionPickInitialize() { 
	//モーション時間初期化
	PickMotionTime_ = 0;
	// 体の初期化
	worldTransformBody_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformBody_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.translation_ = {0.0f, 2.0f, 0.0f};
	// 頭の初期化
	worldTransformHead_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformHead_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHead_.translation_ = {0.0f, 5.0f, 0.0f};
	// 左腕の初期化
	worldTransformL_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_arm.translation_ = {0.0f, 5.0f, 0.0f};
	// 右腕の初期化
	worldTransformR_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm.translation_ = {0.0f, 5.0f, 0.0f};
	// 左脚の初期化
	worldTransformL_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_leg.translation_ = {0.0f, 2.0f, 0.0f};
	// 右脚の初期化
	worldTransformR_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_leg.translation_ = {0.0f, 2.0f, 0.0f};
	// 斧の初期化
	worldTransformAxe_.scale_ = {1.0f,1.0f,1.0f};
	worldTransformAxe_.rotation_ = {1.077f, 0.0f, 0.0f};
	worldTransformAxe_.translation_ = {2.155f, 2.0f, 1.077f};
}

void Player::MotionJumpInitialize() {
	worldTransformBody_.translation_.y = 2;
	worldTransformL_arm.rotation_.x = 0;
	worldTransformR_arm.rotation_.x = 0;
	if (isStartTimer_>60) {
		// ジャンプ初速
		const float kJumpFirstSpeed = 1.0f;
		// ジャンプ初速を与える
		velocity_.y = kJumpFirstSpeed;
	}
}

void Player::MotionAxeInitialize() {
	// 斧フラグ
	useAxe_ = false;
}

void Player::Update() {
	
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
			case Motion::kJump:
				MotionJumpInitialize();
				break;
			case Motion::kAxe:
				MotionAxeInitialize();
			}
			motionRequest_ = std::nullopt;
		}
		switch (motion_) {
		case Motion::kRun:
		default:
		    if (inHouseControllerFlag == true) {

			    MotionRunUpdate();
		    }
			break;
		case Motion::kPick:
		    
			MotionPickUpdate();
		    
			break;
		case Motion::kJump:
		    
			MotionJumpUpdate();
		    
			break;
		case Motion::kAxe:
		    
			MotionAxeUpdate();
		    
		}
		// ゲームパッドの状態を得る変数
		XINPUT_STATE joyState;
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			// 拾うモーション
			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_X && useAxe_ == false) {
				motionRequest_ = Motion::kPick;
				isPushX_ = true;
			} else {
				isPushX_ = false;
			}
		}
		// アクションボタン
		ActionButtonUpdate();
	    if (isController == false||inHouseControllerFlag==false) {
		    motionRequest_ = Motion::kRun;
	    }
	//
	isStartTimer_++;

	BaseCharacter::Update();
	// 行列の更新
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm.UpdateMatrix();
	worldTransformR_arm.UpdateMatrix();
	worldTransformL_leg.UpdateMatrix();
	worldTransformR_leg.UpdateMatrix();
	worldTransformAxe_.UpdateMatrix();

	//Imgui
	Debug();
	
}

void Player::MotionRunUpdate() {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		worldTransformBody_.parent_ = &worldTransform_;
		worldTransformHead_.parent_ = &worldTransform_;
		worldTransformL_arm.parent_ = &worldTransform_;
		worldTransformR_arm.parent_ = &worldTransform_;
		worldTransformL_leg.parent_ = &worldTransform_;
		worldTransformR_leg.parent_ = &worldTransform_;
		worldTransformAxe_.parent_ = &worldTransform_;
		// 移動量
		if (isController == true) {
			    Vector3 move = {
			        (float)joyState.Gamepad.sThumbLX / SHRT_MAX * -Speed, 0.0f,
			        (float)joyState.Gamepad.sThumbLY / SHRT_MAX * -Speed};

			    // 移動量に速さを反映
			    move = Multiply(Speed, Normalize(move));

			    move = TransformNormal(move, MakeRotateYmatrix(viewProjection_->rotation_.y));

			    // 移動
			    worldTransform_.translation_ = Add(worldTransform_.translation_, move);

			    if (Length(move) != 0) {
				    worldTransform_.rotation_.y = std::atan2(move.x, move.z);
				    // 左足
				    if (isLeftLeg_ == false) {
					    worldTransformL_leg.rotation_.x += 0.1f;
					    if (worldTransformL_leg.rotation_.x >= 1.0f) {
						    isLeftLeg_ = true;
					    }
				    } else if (isLeftLeg_ == true) {
					    worldTransformL_leg.rotation_.x -= 0.1f;
					    if (worldTransformL_leg.rotation_.x <= -1.0f) {
						    isLeftLeg_ = false;
					    }
				    }
				    // 右足
				    if (isRightLeg_ == false) {
					    worldTransformR_leg.rotation_.x -= 0.1f;
					    if (worldTransformR_leg.rotation_.x <= -1.0f) {
						    isRightLeg_ = true;
					    }
				    } else if (isRightLeg_ == true) {
					    worldTransformR_leg.rotation_.x += 0.1f;
					    if (worldTransformR_leg.rotation_.x >= 1.0f) {
						    isRightLeg_ = false;
					    }
				    }
			    } else {
				    worldTransformL_leg.rotation_.x = 0.0f;
				    worldTransformR_leg.rotation_.x = 0.0f;
				    isLeftLeg_ = false;
				    isRightLeg_ = false;
			    }
		}
	}
};

void Player::OnCollision() {
	if (isInvestigatebutton_==false) {
		isInvestigatebutton_ = true;
	}

	motionRequest_ = Motion::kJump;
	
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Player::GetCenterPosition() const {
	// ローカル座標のオフセット
	const Vector3 offset = {0.0f, 1.5f, 0.0f};
	// ワールド座標変換
	Vector3 worldPos = Transform(offset, worldTransform_.matWorld_);
	
	return worldPos;
}

void Player::ActionButtonUpdate() {
	if (worldTransform_.translation_.z > -10.0f && worldTransform_.translation_.z < 11.0f&&
	    worldTransform_.translation_.x > -10.0f && worldTransform_.translation_.x<10.0f) {
		isInvestigatebutton_ = true;
	} else {
		isInvestigatebutton_ = false;
	}
}

void Player::Debug() {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	//斧
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (isController == true) {
			    if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_UP) {
				    useAxe_ = true;
			    }
			    if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_DOWN) {
				    useAxe_ = false;
			    }
		}
	}

#ifdef _DEBUG



	// デバック
	float playerPos[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	// デバック
	float playerRot[3] = {
	    worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z};
	//斧デバック
	float axePos[3] = {
	    worldTransformAxe_.translation_.x, worldTransformAxe_.translation_.y,
	    worldTransformAxe_.translation_.z};
	//斧デバック
	float axeRot[3] = {
	    worldTransformAxe_.rotation_.x, worldTransformAxe_.rotation_.y,
	    worldTransformAxe_.rotation_.z};

	// 画面の座標を表示
	ImGui::Begin("Player");
	ImGui::SliderFloat3("Pos", playerPos, -28.0f, 28.0f);
	ImGui::SliderFloat3("Rot", playerRot, -28.0f, 28.0f);
	ImGui::SliderFloat3("AxeP", axePos, -28.0f, 28.0f);
	ImGui::SliderFloat3("AxeR", axeRot, -28.0f, 28.0f);
	ImGui::Text("%f", Speed);
	ImGui::End();
	// 移動
	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];
	// 回転
	worldTransform_.rotation_.x = playerRot[0];
	worldTransform_.rotation_.y = playerRot[1];
	worldTransform_.rotation_.z = playerRot[2];
	// 斧移動
	worldTransformAxe_.translation_.x = axePos[0];
	worldTransformAxe_.translation_.y = axePos[1];
	worldTransformAxe_.translation_.z = axePos[2];
	// 斧回転
	worldTransformAxe_.rotation_.x = axeRot[0];
	worldTransformAxe_.rotation_.y = axeRot[1];
	worldTransformAxe_.rotation_.z = axeRot[2];
#endif !_DEBUG
}

void Player::SetMotion() {
	// モーション初期化
	motion_ = Motion::kRun;
	worldTransform_.translation_.y = 0.0f;
}

void Player::RoopInitialize() {
	isPushX_ = false;
	isController = true;

	// 初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm.Initialize();
	worldTransformR_arm.Initialize();
	worldTransformL_leg.Initialize();
	worldTransformR_leg.Initialize();
	worldTransformAxe_.Initialize();
	// 初期化
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {-1.292f, 0.0f, -30.178f};
	// 体の初期化
	worldTransformBody_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformBody_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformBody_.translation_ = {0.0f, 2.0f, 0.0f};
	// 頭の初期化
	worldTransformHead_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformHead_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformHead_.translation_ = {0.0f, 5.0f, 0.0f};
	// 左腕の初期化
	worldTransformL_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_arm.translation_ = {0.0f, 5.0f, 0.0f};
	// 右腕の初期化
	worldTransformR_arm.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_arm.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_arm.translation_ = {0.0f, 5.0f, 0.0f};
	// 左脚の初期化
	worldTransformL_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformL_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformL_leg.translation_ = {0.0f, 2.0f, 0.0f};
	// 右脚の初期化
	worldTransformR_leg.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformR_leg.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransformR_leg.translation_ = {0.0f, 2.0f, 0.0f};
	// 斧の初期化
	worldTransformAxe_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformAxe_.rotation_ = {1.077f, 0.0f, 0.0f};
	worldTransformAxe_.translation_ = {2.155f, 2.0f, 1.077f};

	// 調べるボタン
	isInvestigatebutton_ = false;

	useAxe_ = false;

	// モーション初期化
	motion_ = Motion::kRun;
	worldTransform_.translation_.y = 0.0f;
	for (int x = 0; x < 11; x++) {
		houseInFlag[x] = {false};
		inMoveFlag[x] = {true};
		outMoveFlag[x] = {true};
		isItemGetFlag[x] = {false};
		offFlag[x] = {false};
		itemGetCount[x] = {0};
	}
	inHouseControllerFlag = true;

	isStartTimer_ = 0;
}

void Player::InHouseZ(int number, Vector3 pos, float rotate, float translate) {
	if (houseInFlag[number] == false) {
		worldTransform_.translation_ = {pos};
		worldTransform_.rotation_.y = rotate;
		houseInFlag[number] = true;
		inHouseControllerFlag = false;
	}
	if (inMoveFlag[number] == true && houseInFlag[number] == true) {
		worldTransform_.translation_.z -= 0.3f;
		if (worldTransform_.translation_.z <= translate) {
			    worldTransform_.translation_.z = translate;
			    inMoveFlag[number] = false;
		}
	}
	if (inMoveFlag[number] == false && isItemGetFlag[number] == false) {
		itemGetCount[number]++;
		if (itemGetCount[number] >= 60) {
			    itemGetFlag2[number] = true;
		}
		if (itemGetCount[number] >= 120) {
			    itemGetFlag3[number] = true;
		}
	}
	if (itemGetCount[number] >= itemCount) {
		isItemGetFlag[number] = true;
		itemGetFlag2[number] = false;
		itemGetFlag3[number] = false;
	}
	if (isItemGetFlag[number] == true && outMoveFlag[number] == true) {
		worldTransform_.translation_.z += 0.3f;
		if (worldTransform_.translation_.z >= pos.z) {
			    worldTransform_.translation_.z = pos.z;
			    outMoveFlag[number] = false;
		}
	}
	if (outMoveFlag[number] == false && offFlag[number] == false) {
		inHouseControllerFlag = true;
		offFlag[number] = true;
	}
}

void Player::InHouseZ2(int number, Vector3 pos, float rotate, float translate) {
	if (houseInFlag[number] == false) {
		worldTransform_.translation_ = {pos};
		worldTransform_.rotation_.y = rotate;
		houseInFlag[number] = true;
		inHouseControllerFlag = false;
	}
	if (inMoveFlag[number] == true && houseInFlag[number] == true) {
		worldTransform_.translation_.z += 0.3f;
		if (worldTransform_.translation_.z >= translate) {
			    worldTransform_.translation_.z = translate;
			    inMoveFlag[number] = false;
		}
	}
	if (inMoveFlag[number] == false && isItemGetFlag[number] == false) {
		itemGetCount[number]++;
		if (itemGetCount[number] >= 60) {
			    itemGetFlag2[number] = true;
		}
		if (itemGetCount[number] >= 120) {
			    itemGetFlag3[number] = true;
		}
	}
	if (itemGetCount[number] >= itemCount) {
		isItemGetFlag[number] = true;
		itemGetFlag2[number] = false;
		itemGetFlag3[number] = false;
	}
	if (isItemGetFlag[number] == true && outMoveFlag[number] == true) {
		worldTransform_.translation_.z -= 0.3f;
		if (worldTransform_.translation_.z <= pos.z) {
			    worldTransform_.translation_.z = pos.z;
			    outMoveFlag[number] = false;
		}
	}
	if (outMoveFlag[number] == false && offFlag[number] == false) {
		inHouseControllerFlag = true;
		offFlag[number] = true;
	}
}

void Player::InHouseX(int number,Vector3 pos,float rotate,float translate) {
	if (houseInFlag[number] == false) {
		worldTransform_.translation_ = pos;
		worldTransform_.rotation_.y = rotate;
		houseInFlag[number] = true;
		inHouseControllerFlag = false;
	}
	if (inMoveFlag[number] == true && houseInFlag[number] == true) {
		worldTransform_.translation_.x += 0.3f;
		if (worldTransform_.translation_.x >= translate) {
			    worldTransform_.translation_.x = translate;
			    inMoveFlag[number] = false;
		}
	}
	if (inMoveFlag[number] == false && isItemGetFlag[number] == false) {
		itemGetCount[number]++;
		if (itemGetCount[number] >= 60) {
			    itemGetFlag2[number] = true;
		}
		if (itemGetCount[number] >= 120) {
			    itemGetFlag3[number] = true;
		}
	}
	if (itemGetCount[number] >= itemCount) {
		isItemGetFlag[number] = true;
		itemGetFlag2[number] = false;
		itemGetFlag3[number] = false;
	}
	if (isItemGetFlag[number] == true && outMoveFlag[number] == true) {
		worldTransform_.translation_.x -= 0.3f;
		if (worldTransform_.translation_.x <= pos.x) {
			    worldTransform_.translation_.x = pos.x;
			    outMoveFlag[number] = false;
		}
	}
	if (outMoveFlag[number] == false && offFlag[number] == false) {
		inHouseControllerFlag = true;
		offFlag[number] = true;
	}
}

void Player::InHouseX2(int number, Vector3 pos, float rotate, float translate) {
	if (houseInFlag[number] == false) {
		worldTransform_.translation_ = pos;
		worldTransform_.rotation_.y = rotate;
		houseInFlag[number] = true;
		inHouseControllerFlag = false;
	}
	if (inMoveFlag[number] == true && houseInFlag[number] == true) {
		worldTransform_.translation_.x -= 0.3f;
		if (worldTransform_.translation_.x <= translate) {
			    worldTransform_.translation_.x = translate;
			    inMoveFlag[number] = false;
		}
	}
	if (inMoveFlag[number] == false && isItemGetFlag[number] == false) {
		itemGetCount[number]++;
		if (itemGetCount[number] >= 60) {
			    itemGetFlag2[number] = true;
		}
		if (itemGetCount[number] >= 120) {
			    itemGetFlag3[number] = true;
		}
	}
	if (itemGetCount[number] >= itemCount) {
		isItemGetFlag[number] = true;
		itemGetFlag2[number] = false;
		itemGetFlag3[number] = false;
	}
	if (isItemGetFlag[number] == true && outMoveFlag[number] == true) {
		worldTransform_.translation_.x += 0.3f;
		if (worldTransform_.translation_.x >= pos.x) {
			    worldTransform_.translation_.x = pos.x;
			    outMoveFlag[number] = false;
		}
	}
	if (outMoveFlag[number] == false && offFlag[number] == false) {
		inHouseControllerFlag = true;
		offFlag[number] = true;
	}
}

void Player::MotionPickUpdate() { 
	// 拾うモーション時間
	PickMotionTime_++;

	//腕
	if (PickMotionTime_ < 7.5f) {
		worldTransformR_arm.rotation_.x -= 0.1f;
		worldTransform_.translation_.y = 0;
	} else {
		worldTransformR_arm.rotation_.x += 0.1f;
		worldTransform_.translation_.y = 0;
	}
	//体と頭
	if (PickMotionTime_ < 7.5f) {
		
		worldTransform_.translation_.y = 0;
	} else {
		worldTransform_.translation_.y = 0;
	}
	
	// 拾うモーション時間
	if (PickMotionTime_>15.0f) {
		motionRequest_ = Motion::kRun;
	} else {
		worldTransform_.translation_.y =  0.0f;
	}
}

void Player::MotionJumpUpdate() {
	if (worldTransform_.translation_.x<=0) {
		worldTransform_.translation_.x -= 0.07f;
	} else {
		worldTransform_.translation_.x += 0.07f;
	}
	// 移動
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	// 重力加速度
	const float kGravityAcceleration = 0.10f;
	// 加速度ベクトル
	Vector3 accelerationVector = {0, -kGravityAcceleration, 0};
	// 加速する
	velocity_ = Add(velocity_, accelerationVector);
	// 着地
	if (worldTransform_.translation_.y <= 0.0f) {
		worldTransform_.translation_.y = 0;
		// ジャンプ終了
		motionRequest_ = Motion::kRun;
	}
}

void Player::MotionAxeUpdate() {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		//モーション
		if (useAxe_ == true && joyState.Gamepad.wButtons == XINPUT_GAMEPAD_X) {
			    motionRequest_ = Motion::kAxe;
		}
		
	}

}

void Player::Draw(const ViewProjection& viewProjection) {
	// 3Dモデルを描画
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm, viewProjection);
	models_[3]->Draw(worldTransformR_arm, viewProjection);
	models_[4]->Draw(worldTransformL_leg, viewProjection);
	models_[5]->Draw(worldTransformR_leg, viewProjection);
	if (useAxe_==true) {
		// 斧
		models_[6]->Draw(worldTransformAxe_, viewProjection);
	}
}
void Player::ActionbuttonDraw() {
	if (isInvestigatebutton_ == true) {
		spriteButton_->Draw();
	}
}




