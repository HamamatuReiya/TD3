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

	bool GetIsTutorialEnd_() { return isTutorialEnd_; }
	bool SetIsTutorialEnd_(bool tutorialEnd) { return isTutorialEnd_ = tutorialEnd; }

	bool GetIsView_() { return isView_; }
	bool SetIsView_(bool isview) { return isView_ = isview; }

	bool GetisTutorial2Flag() { return isTutorial2Flag_; }
	bool SetisTutorial2Flag(bool isTutorial2Flag) { return isTutorial2Flag_ = isTutorial2Flag; }
	
	void RoopInitilize();


private:
	// チュートリアルスプライト
	Sprite* spritetTuorial_[4] = {nullptr,nullptr,nullptr,nullptr};
	//フラグ
	bool isTuorial_[4];
	//プレイヤーに動いてもらう
	bool ismovePlayer_;
	//ボタンクールダウン
	int ButtonCoolDown_;
	//チュートリアルフラグ
	bool isTutorialEnd_;
	//
	bool isView_;
	//
	bool isTutorial2Flag_;
};
