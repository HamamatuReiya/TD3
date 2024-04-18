#pragma once
#include "Sprite.h"

class ItemCounter {
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

private:
	// 数字の画像
	Sprite* textureNumberStone_[10];
	Sprite* textureNumberGold_[10];
	Sprite* textureNumberJushi_[10];
	Sprite* textureNumberShell_[10];


	// 数字の画像の読み込み
	uint32_t numHandle_[10];

	int stoneNum[2];
	int goldNum[2];
	int jushiNum[2];
	int shellNum[2];

};
