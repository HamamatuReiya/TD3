#include "UI.h"


void UI::Initialize() { 
	// テクスチャ
	uint32_t textureWindow = TextureManager::Load("Window.png");
	// スプライト生成
	spriteWindow_ =
	    Sprite::Create(textureWindow, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

}

void UI::Update() {
	
}

void UI::Draw() { 
	spriteWindow_->Draw();
}
