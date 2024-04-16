#pragma once
#include <Sprite.h>
#include <TextureManager.h>
class UI {
public:
	// デストラクタ

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 描画
	/// </summary>
	void ExclamationMarkDraw();

private:
	// スプライト
	Sprite* spriteWindow_ = nullptr; 
	//ビックリマークスプライト
	Sprite* spriteExclamationMark_ = nullptr;

	
};
