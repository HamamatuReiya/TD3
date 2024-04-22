#pragma once
#include <Sprite.h>
#include <TextureManager.h>
#include "Input.h"

class Tutorial {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void TutorialInitialize();

	/// <summary>
	/// 更新
	/// </summary>
	void TutorialUpdate();


	/// <summary>
	/// 描画
	/// </summary>
	void TutorialDraw();

private:
	// チュートリアルスプライト
	Sprite* spritetTuorial_ = nullptr;
	//フラグ
	bool isTuorial_;
};
