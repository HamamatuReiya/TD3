#include "FollowCamera.h"
#include "ImGuiManager.h"
#include <MT.h>

void FollowCamera::Initialize() {
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクション
	viewProjection_.Initialize();

	input_ = Input::GetInstance();

	////角度
	viewProjection_.rotation_.y = 3.16f;
	viewProjection_.rotation_.x = 90.0f;
}

void FollowCamera::Update() {

	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 55.0f, 20.0f};
		offset = TransformNormal(offset, MakeRotateYmatrix(viewProjection_.rotation_.y));
		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float rotate = 0.04f;
		viewProjection_.rotation_.y += joyState.Gamepad.sThumbRX / SHRT_MAX * rotate;
	}
	
	//Imgui
	Debug();

	// 行列の更新
	viewProjection_.UpdateMatrix();
}

void FollowCamera::Debug() {

#ifdef _DEBUG

	// デバック
	float cameraRot[3] = {
	    viewProjection_.rotation_.x, viewProjection_.rotation_.y, viewProjection_.rotation_.z};

	// 画面の座標を表示
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("Rot", cameraRot, -90.0f, 90.0f);
	ImGui::End();

	// 回転
	viewProjection_.rotation_.x = cameraRot[0];
	viewProjection_.rotation_.y = cameraRot[1];
	viewProjection_.rotation_.z = cameraRot[2];
	
#endif !_DEBUG
}