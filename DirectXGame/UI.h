#pragma once
#include"Player.h"
#include <Sprite.h>
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
	// 自キャラ
	std::unique_ptr<Player> player_;
	// スプライト
	Sprite* spriteBommActionButton_ = nullptr; // 爆弾のアクションボタン
	
};
