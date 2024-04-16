#include "UI.h"


void UI::Initialize() { 
	// テクスチャ
	uint32_t textureWindow = TextureManager::Load("Window.png");
	uint32_t textureExclamationMark_ = TextureManager::Load("!.png");
	// スプライト生成
	spriteWindow_ =
	    Sprite::Create(textureWindow, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	// スプライト生成
	spriteWindow_ = Sprite::Create(
	    textureExclamationMark_, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

}

void UI::Draw() { 
	spriteWindow_->Draw(); }

void UI::ExclamationMarkDraw() { spriteExclamationMark_->Draw(); }
