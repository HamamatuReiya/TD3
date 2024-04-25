#include "Input.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class FollowCamera {
public:
	/// 初期化
	void Initialize();
	// 更新
	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; };

	// Imgui
	void Debug();

	//アップ
	void UpView();


	const ViewProjection& GetViewProjection() { return viewProjection_; }

	bool GetIsController() { return isController; };
	bool SetIsController(bool flag) { return isController = flag; }

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// キーボード
	Input* input_ = nullptr;

	bool isController = true;

private:
	// 追従対象
	const WorldTransform* target_ = nullptr;
};
