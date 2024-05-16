#include "Model.h"
#include "WorldTransform.h"

class Earth {
public:
	void Initialize(Model* model,float pos);

	void Update();

	void Draw(ViewProjection& viewProjection);

	Vector3 SetScale(Vector3 s) { return scale = s; }

	float SetPos(float pos) { return worldTransform_.translation_.x = pos; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;

	Vector3 scale;

};