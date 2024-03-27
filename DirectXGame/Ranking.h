#pragma once
#include "Sprite.h"

class Ranking {
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
	//
	void Division(int rank1, int rank2, int rank3, int rank4, int rank5);

private:
	int ranking[5];
	
	int score_;	

	int a = 0;
				
	// 数字の画像
	Sprite* textureRanking1_[5];
	Sprite* textureRanking2_[5];
	Sprite* textureRanking3_[5];
	Sprite* textureRanking4_[5];
	Sprite* textureRanking5_[5];

	// 数字の画像の読み込み
	uint32_t numHandle_[10];

	int num1[10];
	int num2[10];
	int num3[10];
	int num4[10];
	int num5[10];
};
