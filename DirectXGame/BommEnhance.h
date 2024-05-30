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

	void ResultDraw();

	void RoopInitialize();

	int GetBommLv();

	/// <summary>
	/// 描画
	/// </summary>
	//void Draw();

private:
	int exp = 0;
	int expMax[12];
	

	// 数字の画像の読み込み
	uint32_t numHandle_[10];

	

	int Level[2];
	int expP[3];
};