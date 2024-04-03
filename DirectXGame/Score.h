#pragma once
#include "Sprite.h"

class Score {
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(int score);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	//数字の画像
	Sprite* textureNumber_[10];

	// 数字の画像の読み込み
	uint32_t numHandle_[10];

	int num[10];
};
