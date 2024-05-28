#pragma once
#include "Input.h"
#include <Sprite.h>

class BommEnhance {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(int stone, int gold, int jushi, int shell);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 描画
	/// </summary>
	//void Draw();

private:
	int exp = 0;
	int expMax[12];
	int bommLv = 1;

	// 数字の画像の読み込み
	uint32_t numHandle_[10];

	// 数字の画像
	Sprite* textureLevel_[2];
	Sprite* textureExp_[3];

	int Level[2];
	int expP[3];
};
