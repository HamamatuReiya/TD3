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

void FollowCamera::UpView() {
	viewProjection_.rotation_.x = 3.358f;
	viewProjection_.translation_.y = 4.03f;
	viewProjection_.translation_.z = -9.0f;
}



void FollowCamera::Debug() {

#ifdef _DEBUG

	// デバック
	float cameraRot[3] = {
	    viewProjection_.rotation_.x, viewProjection_.rotation_.y, viewProjection_.rotation_.z};
	// デバック
	float cameraPos[3] = {
	    viewProjection_.translation_.x, viewProjection_.translation_.y,
	    viewProjection_.translation_.z};

	// 画面の座標を表示
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("Rot", cameraRot, -15.0f,15.0f);
	ImGui::SliderFloat3("Pos", cameraPos, -30.0f, 30.0f);
	ImGui::End();

	// 回転
	viewProjection_.rotation_.x = cameraRot[0];
	viewProjection_.rotation_.y = cameraRot[1];
	viewProjection_.rotation_.z = cameraRot[2];

	// 移動
	viewProjection_.translation_.x = cameraPos[0];
	viewProjection_.translation_.y = cameraPos[1];
	viewProjection_.translation_.z = cameraPos[2];
	
#endif !_DEBUG
}

