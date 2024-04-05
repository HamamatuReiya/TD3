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
//#include "Score.h"
//#include "Ranking.h"

class TitleScene {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

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
	SceneType NextScene() { return SceneType::kSelect; }

private:
    void Select();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	/*std::unique_ptr<Score> score_;

	std::unique_ptr<Ranking> ranking_;*/

	//タイトル画像
	Sprite* textureTitle_;
	uint32_t titleHandle_;

	//タイトル文字画像
	Sprite* textureSubTitle_;
	uint32_t subTitleHandle_;

	Vector4 subTitleColor_ = {1.0f, 1.0f, 1.0f, 0.0f};

	// 矢印 カーソル
	Sprite* textureCursor_;
	Vector2 cursorPos_ = {350.0f, 495.0f};
	Vector2 cursorSpeed_ = {0, 30};
	int selectCount_ = 0;

	// スティックのフラグ
	bool padStateFlag_ = false;
	bool dPadStateFlag_ = false;

	// 天球
	std::unique_ptr<Spacedome> spacedome_;
	//  3Dモデル
	std::unique_ptr<Model> modelSpacedome_;

	// フェード
	std::unique_ptr<Fade> fade_;
	bool fadeTimerFlag_;
	const float kFadeTimer_ = 1.657f * 60.0f;
	float fadeTimer_ = kFadeTimer_;
};
