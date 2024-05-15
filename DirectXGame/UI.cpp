#include "UI.h"


void UI::Initialize() { 
	// テクスチャ
	uint32_t textureWindow = TextureManager::Load("Window.png");
	uint32_t textureExclamationMark = TextureManager::Load("!.png");
	uint32_t textureButtonHint = TextureManager::Load("Buttonhint.png");
	//素材　画像
	//石
	uint32_t textureStone = TextureManager::Load("material/stone.png");
	//金
	uint32_t textureGold = TextureManager::Load("material/gold.png");
	//樹脂
	uint32_t textureJushi = TextureManager::Load("material/jushi.png");
	//貝
	uint32_t textureShell = TextureManager::Load("material/shell.png");

	
	// スプライト生成
	spriteWindow_ =
	    Sprite::Create(textureWindow, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	// スプライト生成
	spriteExclamationMark_ = Sprite::Create(
	    textureExclamationMark, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	// スプライト生成
	spriteButtonHint_ = Sprite::Create(textureButtonHint, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	
	//
	spriteStone_ =
	    Sprite::Create(textureStone, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	spriteGold_ = Sprite::Create(textureGold, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	spriteJushi_ = Sprite::Create(textureJushi, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	spriteShell_ = Sprite::Create(textureShell, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}

void UI::Draw() { 
	spriteWindow_->Draw();

	spriteStone_->Draw();
	spriteGold_->Draw();
	spriteJushi_->Draw();
	spriteShell_->Draw();
}

void UI::ExclamationMarkDraw() { spriteExclamationMark_->Draw(); }

void UI::ButtonHintDraw() { spriteButtonHint_->Draw(); }


