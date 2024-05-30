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
#include "Earth.h"

#include "fade/Fade.h"
#include "Spacedome.h"
#include <Stage.h>

class SelectScene : public StageSelect {
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

	//ステージ選択
	void StageSelect();

public:
	void SceneReset();

	//島
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
	Vector2 cursorPos_ = {0, 350};
	Vector2 cursorSpeed_ = {0, 0};
	int stageCount_ = 0;
	const int kMaxStage_ = 4; 

	Sprite* stageTitle_[2];

	//天球
	std::unique_ptr<Spacedome> spacedome_;
	//  3Dモデル
	std::unique_ptr<Model> modelSpacedome_;

	std::unique_ptr<Earth> earth_[2];

	std::unique_ptr<Model> modelEarth_[2];

	float earthPos_;
	bool isSelectEarth = false;

	//シーンを終わらせる変数
	bool isSceneEnd_ = false;

	//スティックのフラグ
	bool padStateFlag_ = false;
	bool dPadStateFlag_ = false;

	bool isPushLight_ = false;
	bool isPushReft_ = false;
	bool isPush_ = false;

	// フェード
	std::unique_ptr<Fade> fade_;
	bool fadeTimerFlag_;
	const float kFadeTimer_ = 1.657f * 60.0f;
	float fadeTimer_ = kFadeTimer_;
};
