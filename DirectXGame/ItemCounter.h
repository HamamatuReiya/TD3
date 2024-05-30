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

	void WindowDraw();

private:
	// 数字の画像
	Sprite* textureNumberStone_[10];
	Sprite* textureNumberGold_[10];
	Sprite* textureNumberJushi_[10];
	Sprite* textureNumberShell_[10];

	Sprite* textureNumberWindowStone_[10];
	Sprite* textureNumberWindowGold_[10];
	Sprite* textureNumberWindowJushi_[10];
	Sprite* textureNumberWindowShell_[10];
	// 素材の画像
	Sprite* textureStone_;
	Sprite* textureGold_;
	Sprite* textureJushi_;
	Sprite* textureShell_;

	Sprite* textureMultiply_[4];

	// 数字の画像の読み込み
	uint32_t numHandle_[10];
	uint32_t multiplyHandle_;

	//素材の画像の読み込み
	uint32_t stoneHandle_;
	uint32_t goldHandle_;
	uint32_t jushiHandle_;
	uint32_t shellHandle_;

	int stoneNum[2];
	int goldNum[2];
	int jushiNum[2];
	int shellNum[2];

};
