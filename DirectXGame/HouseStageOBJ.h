#pragma once
#include "Model.h"
#include "WorldTransform.h"

class HouseStageOBJ {
public:
	void Initialize(
	    Model* model, Model* model1, Model* model2, Model* model3, Model* model4, Model* model5,
	    Model* model6, Model* model7, Model* model8, Model* model9, Model* model10, Model* model11,
	    Model* model12, Model* model13, Model* model14, Model* model15, Model* model16,
	    Model* model17, Model* model18, Model* model19, Model* model20, Model* model21,
	    Model* model22, Model* model23, Model* model24, Model* model25, Model* model26,
	    Model* model27, Model* model28, Model* model29, Model* model30, Model* model31,
	    Model* model32, Model* model33, Model* model34, Model* model35, Model* model36,
	    Model* model37, Model* model38, Model* model39, Model* model40, Model* model41,
	    Model* model42, Model* model43, Model* model44, Model* model45, Model* model46,
	    Model* model47, Model* model48, Model* model49, Model* model50, Model* model51,
	    Model* model52, Model* model53, Model* model54, Model* model55, Model* model56,
	    Model* model57, Model* model58, Model* model59, Model* model60, Model* model61,
	    Model* model62, Model* model63, Model* model64, Model* model65, Model* model66,
	    Model* model67, Model* model68, Model* model69, Model* model70, Model* model71,
	    Model* model72, Model* model73, Model* model74, Model* model75, Model* model76,
	    Model* model77, Model* model78, Model* model79, Model* model80, Model* model81,
	    Model* model82, Model* model83, Model* model84, Model* model85, Model* model86,
	    Model* model87, Model* model88, Model* model89, Model* model90, Model* model91,
	    Model* model92, Model* model93, Model* model94, Model* model95, Model* model96);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_[99] = {nullptr};
};
