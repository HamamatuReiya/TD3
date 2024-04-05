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
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	

private:
	
	// スプライト
	Sprite* spriteWindow_ = nullptr; 
	
};
