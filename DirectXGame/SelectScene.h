#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"

#include "fade/Fade.h"
#include "Spacedome.h"

class SelectScene {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	SelectScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectScene();

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

private:
	// 画像の初期化
	void TextureInitialize();

public:
	void sceneReset();

	bool isSceneEnd_ = false;

	bool IsSceneEnd() { return isSceneEnd_; }
	SceneType NextScene() { return SceneType::kGamePlay; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	//数字の画像
	Sprite* textureNumber_[10];
	//矢印 カーソル
	Sprite* textureCursor_;
	Vector2 cursorPos_ = {0, 330};
	Vector2 cursorSpeed_ = {0, 0};
	int stageCount = 1;

	//天球
	std::unique_ptr<Spacedome> spacedome_;
	//  3Dモデル
	std::unique_ptr<Model> modelSpacedome_;

	// フェード
	std::unique_ptr<Fade> fade_;
	bool fadeTimerFlag_;
	const float kFadeTimer_ = 1.657f * 60.0f;
	float fadeTimer_ = kFadeTimer_;
};
