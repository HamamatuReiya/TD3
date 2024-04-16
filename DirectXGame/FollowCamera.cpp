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
	viewProjection_.rotation_.x = 90.0f;
	viewProjection_.rotation_.y = -15.0f;
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 55.0f, 25.0f};
		offset = TransformNormal(offset, MakeRotateYmatrix(viewProjection_.rotation_.y)); 
		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}
	
	// 行列の更新
	viewProjection_.UpdateMatrix();
}
