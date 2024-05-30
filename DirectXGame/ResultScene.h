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
#include "ItemCounter.h"
#include "BommEnhance.h"
#include "fade/Fade.h"

class ResultScene{
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

	std::unique_ptr<ItemCounter> itemCounter_;

	std::unique_ptr<BommEnhance> bommEnhance_;

	std::unique_ptr<Fade> fade_;

	bool fadeFlag_=false;
	const float kFadeTimer_ = 1.657f * 60.0f;
	float fadeTimer_ = kFadeTimer_;

	Sprite* bommLv;
	uint32_t bommLvTex; 

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// サウンド
	uint32_t resultbgmHandle_;
	uint32_t playResultBgm_;
	bool isResultBgm_;
};
