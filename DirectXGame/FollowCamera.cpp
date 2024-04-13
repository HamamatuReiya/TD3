#include "FollowCamera.h"
#include "ImGuiManager.h"
#include <MT.h>

void FollowCamera::Initialize() {
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクション
	viewProjection_.Initialize();

	input_ = Input::GetInstance();
}

void FollowCamera::Update() {
	//// ゲームパッドの状態を得る変数
	//XINPUT_STATE joyState;
	//角度
	viewProjection_.rotation_.x = 90.0f;
	viewProjection_.rotation_.y = -15.0f;
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 25.0f, 10.0f};
		offset = TransformNormal(offset, MakeRotateYmatrix(viewProjection_.rotation_.y)); // 途中
		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}
	//if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	//	// 速さ
	//	const float speed = 0.6f;
	//	// 移動量
	//	Vector3 move = {
	//	    (float)joyState.Gamepad.sThumbRX / SHRT_MAX * -speed, 0.0f,
	//	    (float)joyState.Gamepad.sThumbRY / SHRT_MAX * -speed};
	//	// 移動量に速さを反映
	//	move = Multiply(speed, Normalize(move));
	//	move = TransformNormal(move, MakeRotateYmatrix(viewProjection_.rotation_.x));
	//}
	
	// 行列の更新
	viewProjection_.UpdateMatrix();
}
