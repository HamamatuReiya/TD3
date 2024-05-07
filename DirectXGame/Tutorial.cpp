#include "Tutorial.h"

void Tutorial::TutorialInitialize() {
	// テクスチャ
	uint32_t texturetutorial = TextureManager::Load("Tutorial0.png");
	uint32_t texturetutorial1 = TextureManager::Load("Tutorial1.png");
	uint32_t texturetutorial2 = TextureManager::Load("Tutorial.png");
	uint32_t texturetutorial3 = TextureManager::Load("Tutorial3.png");
	// スプライト生成
	spritetTuorial_[0] =
	    Sprite::Create(texturetutorial, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	spritetTuorial_[1] =
	    Sprite::Create(texturetutorial1, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	spritetTuorial_[2] =
	    Sprite::Create(texturetutorial2, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	spritetTuorial_[3] =
	    Sprite::Create(texturetutorial3, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	//
	for (int i = 0; i < 4; i++) {
		isTuorial_[i] = false;
	}

	ButtonCoolDown_ = 60;
	//0
	isTuorial_[0] = true;

	
	isTutorialEnd_ = false;
}

void Tutorial::TutorialUpdate() {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		ButtonCoolDown_--;
		// 1
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A && isTuorial_[0] == true) {
		
			if (ButtonCoolDown_ <= 0) {
				isTuorial_[0] = false;
				isTuorial_[1] = true;
				isTuorial_[2] = false;
				isTuorial_[3] = false;
				ButtonCoolDown_ = 60;
				isView_ = true;
			}
		}
		// 2
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A && isTuorial_[1] == true) {
			if (ButtonCoolDown_ <= 0) {
				isTuorial_[0] = false;
				isTuorial_[1] = false;
				isTuorial_[2] = true;
				isTuorial_[3] = false;
				ButtonCoolDown_ = 60;
				isView_ = false;
			}
		}
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A && isTuorial_[2] == true) {
			if (ButtonCoolDown_ <= 0) {
				isTuorial_[2] = false;
				ButtonCoolDown_ = 60;
				isTutorialEnd_ = true;
			}
		}

		//3
		if (isTutorialEnd_ == false && isTuorial_[2] == false && isTuorial_[0] == false &&
		    isTuorial_[1] == false) {
			if (ButtonCoolDown_ <= 0) {
				isTuorial_[3] = true;
				isTuorial_[2] = false;
				isTuorial_[1] = false;
				isTuorial_[0] = false;
				ButtonCoolDown_ = 60;
			}
		}
		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A && isTuorial_[3] == true) {
			isTutorialEnd_ = true;
		}
		
    }
}


void Tutorial::TutorialDraw() {
	
	// 0
	if (isTuorial_[0] == true) {
		spritetTuorial_[0]->Draw();
	}
	// 1
	if (isTuorial_[1] == true) {
		spritetTuorial_[1]->Draw();
	}
	// 2
	if (isTuorial_[2] == true) {
		spritetTuorial_[2]->Draw();
	}
	// 3
	if (isTuorial_[3] == true) {
		spritetTuorial_[3]->Draw();
	}
	
}

void Tutorial::RoopInitilize() {
	for (int i = 0; i < 4; i++) {
		isTuorial_[i] = false;
	}

	ButtonCoolDown_ = 60;
	// 0
	isTuorial_[0] = true;
	isTutorialEnd_ = false;
}
