#include "UI.h"


void UI::Initialize() { 
	// テクスチャ
	uint32_t textureWindow = TextureManager::Load("Window.png");
	uint32_t textureExclamationMark = TextureManager::Load("!.png");
	uint32_t textureButtonHint = TextureManager::Load("Buttonhint.png");
	// スプライト生成
	spriteWindow_ =
	    Sprite::Create(textureWindow, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	// スプライト生成
	spriteExclamationMark_ = Sprite::Create(
	    textureExclamationMark, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	// スプライト生成
	spriteButtonHint_ = Sprite::Create(textureButtonHint, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}

void UI::Draw() { 
	spriteWindow_->Draw(); }

void UI::ExclamationMarkDraw() { spriteExclamationMark_->Draw(); }

void UI::ButtonHintDraw() { spriteButtonHint_->Draw(); }
