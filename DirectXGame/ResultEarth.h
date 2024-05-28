#pragma once
#include "Model.h"
#include "WorldTransform.h"

class ResultEarth {
public:
	void Initialize(
	    Model* model, Model* model1, Model* model2, Model* model3, Model* model4, Model* model5,
	    Model* model6, Model* model7, Model* model8, Model* model9, Model* model10, Model* model11,
	    Model* model12, Model* model13);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void RoopInitialize();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	float speed;

	// モデル
	Model* model_[99] = {nullptr};
};
