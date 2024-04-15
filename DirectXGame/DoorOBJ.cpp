#include "DoorOBJ.h"

void DoorOBJ::Initialize(Model* model1, Model* model2, Vector3 pos,float rotate) {
	model_[0] = model1;
	model_[1] = model2;
	doorOpenFlag = false;
	keyFlag = false;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, rotate, 0.0f};
	worldTransform_.translation_ = pos;
}

void DoorOBJ::Update() { 
	if (doorOpenFlag == true) {
		worldTransform_.rotation_.y -= 0.075f;
	}
	if (worldTransform_.rotation_.y <=- 1.6f) {
		worldTransform_.rotation_.y =- 1.6f;
	}
	worldTransform_.UpdateMatrix();
}

void DoorOBJ::Update2() {
	if (doorOpenFlag == true) {
		worldTransform_.rotation_.y -= 0.075f;
	}
	if (worldTransform_.rotation_.y <= 3.2f) {
		worldTransform_.rotation_.y = 3.2f;
	}
	worldTransform_.UpdateMatrix();
}

void DoorOBJ::Draw(ViewProjection& viewProjection) {
	model_[0]->Draw(worldTransform_, viewProjection);
	model_[1]->Draw(worldTransform_, viewProjection);
}

Vector3 DoorOBJ::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void DoorOBJ::Collision() { doorOpenFlag = true; }
