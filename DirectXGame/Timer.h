#pragma once
#include "Sprite.h"

class Timer {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(int timer);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// 数字の画像の読み込み
	uint32_t numHandle_[10];

	// 数字の画像
	Sprite* textureTimer_[5];

	int num[3];
};
