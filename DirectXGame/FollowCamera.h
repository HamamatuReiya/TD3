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
	//
	void LowView();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	bool GetIsController() { return isController; };
	bool SetIsController(bool flag) { return isController = flag; }

	/*bool GetIsController() { return isController; };
	bool SetIsController(bool flag) { return isController = flag; }*/

	/// <summary>
	/// カメラ
	/// </summary>
	enum class Camera {
		kBomm,
		kUp,
	};

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// キーボード
	Input* input_ = nullptr;

	bool isController = true;

	//
	float offsetZ;
	float offsetY;

private:
	// 追従対象
	const WorldTransform* target_ = nullptr;

	//シェイク
	bool isShake_;

};
