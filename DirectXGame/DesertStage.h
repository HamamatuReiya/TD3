#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
//#include "FollowCamera.h"
//#include "Ground.h"
#include "Input.h"
#include "Model.h"
//#include "Player.h"
#include "SafeDelete.h"
//#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include <Scene.h>
#include "fade/Fade.h"

class DesertStage {
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	DesertStage();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DesertStage();

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
	void sceneReset();

	bool isSceneEnd_ = false;

	bool IsSceneEnd() { return isSceneEnd_; }
	SceneType NextScene() { return SceneType::kTitle; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	std::unique_ptr<Model> model_ = nullptr;

	// 数字の画像
	Sprite* textureNumber_;

	// フェード
	std::unique_ptr<Fade> fade_;
	bool fadeTimerFlag_;
	const float kFadeTimer_ = 1.657f * 60.0f;
	float fadeTimer_ = kFadeTimer_;
};
