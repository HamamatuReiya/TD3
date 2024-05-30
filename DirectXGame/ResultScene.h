#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include <Stage.h>
#include "Scene.h"

#include "Spacedome.h"
#include "ResultEarth.h"

class ResultScene {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	ResultScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResultScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	void SceneReset();

	bool isSceneEnd_ = false;

	bool IsSceneEnd() { return isSceneEnd_; }
	SceneType NextScene() { return SceneType::kTitle; }

	void BGMReset();

	void BGMStop();

private: // メンバ変数

	// 天球
	std::unique_ptr<Spacedome> spacedome_;
	//  3Dモデル
	std::unique_ptr<Model> modelSpacedome_;

	std::unique_ptr<ResultEarth> resultEarth_;
	// 家ステージのモデル
	std::unique_ptr<Model> resultEarthModel_[14] = {nullptr};

	DirectXCommon* dxCommon_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// サウンド
	uint32_t resultbgmHandle_;
	uint32_t playResultBgm_;
	bool isResultBgm_;
};
