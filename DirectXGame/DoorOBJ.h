#pragma once
#include "Model.h"
#include "WorldTransform.h"

class DoorOBJ {
public:
	void Initialize(Model* model1, Model* model2,Vector3 pos,float rotate);

	void Update();

	void Update2();

	void Draw(ViewProjection& viewProjection);

	Vector3 GetWorldPosition();

	void Collision();

	bool GetKeyFlag() { return keyFlag; }

	void SetKeyFlag(bool setKeyFlag) { keyFlag = setKeyFlag; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	bool keyFlag;
	bool doorOpenFlag;
	// モデル
	Model* model_[2] = {nullptr};
};
