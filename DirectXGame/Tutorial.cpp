#include "Tutorial.h"

void Tutorial::TutorialInitialize() {
	// テクスチャ
	uint32_t texturetutorial = TextureManager::Load("Tutorial.png");
	// スプライト生成
	spritetTuorial_ =
	    Sprite::Create(texturetutorial, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	//
	isTuorial_ = false;
}

void Tutorial::TutorialUpdate() {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 拾うモーション
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A) {
			isTuorial_ = true;
		}
	}
}

void Tutorial::TutorialDraw() {
	if (isTuorial_==true) {
		spritetTuorial_->Draw(); 
	}
}
