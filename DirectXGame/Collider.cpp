#include"Collider.h"

void Collider::Initialize() { 
	worldTransform_.Initialize();
}

void Collider::UpdateWorldTransform() { 
	worldTransform_.translation_ = GetCenterPosition();
	// 行列の更新
	worldTransform_.UpdateMatrix();
}



