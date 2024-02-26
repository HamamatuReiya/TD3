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
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 20.0f, 10.0f};
		offset = TransformNormal(offset, MakeRotateYMatrix(viewProjection_.rotation_.y)); // 途中
		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}
	
	// 行列の更新
	viewProjection_.UpdateMatrix();
}
