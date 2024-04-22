﻿#pragma once
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

	/*int GetmovePlayer() { return ismovePlayer_; }*/

private:
	// チュートリアルスプライト
	Sprite* spritetTuorial_[4] = {nullptr,nullptr,nullptr,nullptr};
	//フラグ
	bool isTuorial_[4];
	//プレイヤーに動いてもらう
	bool ismovePlayer_;
	//ボタンクールダウン
	int ButtonCoolDown_;

};
