#include "BommEnhance.h"
#include <ImGuiManager.h>
#include "TextureManager.h"

void BommEnhance::Initialize() { 

	// 数字の画像
	numHandle_[0] = TextureManager::Load("./Resources/number/0.png");
	numHandle_[1] = TextureManager::Load("./Resources/number/1.png");
	numHandle_[2] = TextureManager::Load("./Resources/number/2.png");
	numHandle_[3] = TextureManager::Load("./Resources/number/3.png");
	numHandle_[4] = TextureManager::Load("./Resources/number/4.png");
	numHandle_[5] = TextureManager::Load("./Resources/number/5.png");
	numHandle_[6] = TextureManager::Load("./Resources/number/6.png");
	numHandle_[7] = TextureManager::Load("./Resources/number/7.png");
	numHandle_[8] = TextureManager::Load("./Resources/number/8.png");
	numHandle_[9] = TextureManager::Load("./Resources/number/9.png");

	// 取得した数
	for (int i = 0; i < 2; i++) {
		textureLevel_[i] = Sprite::Create(
		    numHandle_[i], {630.0f + i * 50.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

	for (int i = 0; i < 10; i++) {
		expMax[i] = 10 * (i + 1);
	}
	 
}

void BommEnhance::Update(int stone, int gold, int jushi, int shell) {
	exp += stone * 2;
	exp += gold * 2;
	exp += jushi * 2;
	exp += shell * 2;


	for (int i = 0; i < 10; i++) {
		if (exp >= expMax[i] && bommLv == i + 1) {
			bommLv += 1;

			if (exp <= 10) {
				exp = 0;
			} 
			else if (exp > 10) {
				int num = exp / 10;
				exp -= 10 * num;
			}
		}
	}

	Level[0] = bommLv / 10;
	bommLv = bommLv % 10;

	Level[1] = bommLv;

	for (int i = 0; i < 2; i++) {
		textureLevel_[i]->SetTextureHandle(numHandle_[Level[i]]);
	}

	//// 1
	//if (exp >= expMax[0] && bommLv == 1) {
	//	bommLv += 1;
	//	exp = 0;
	//}
	//// 2 
	//if (exp >= expMax[1] && bommLv == 2) {
	//	bommLv += 1;
	//	exp = 0;
	//}
	//// 3
	//if (exp >= expMax[2] && bommLv == 3) {
	//	bommLv += 1;
	//	exp = 0;
	//}
	//// 4
	//if (exp >= expMax[3] && bommLv == 4) {
	//	bommLv += 1;
	//	exp = 0;
	//}
	//// 5
	//if (exp >= expMax[4] && bommLv == 5) {
	//	bommLv += 1;
	//	exp = 0;
	//}
	//// 6
	//if (exp >= expMax[5] && bommLv == 6) {
	//	bommLv += 1;
	//	exp = 0;
	//}
	//// 7
	//if (exp >= expMax[6] && bommLv == 7) {
	//	bommLv += 1;
	//	exp = 0;
	//}
	//// 8
	//if (exp >= expMax[7] && bommLv == 8) {
	//	bommLv += 1;
	//	exp = 0;
	//}
	//// 9
	//if (exp >= expMax[8] && bommLv == 9) {
	//	bommLv += 1;
	//	exp = 0;
	//}

	// ゲームパッドの状態を得る変数
	/*XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {

		}
	}*/
#ifdef _DEBUG
	ImGui::Begin("BommEnhance");
	ImGui::Text("exp : %d", exp);
	ImGui::Text("bommLv : %d", bommLv);
	ImGui::End();
#endif !_DEBUG
}

void BommEnhance::Draw() {
	/*for (int i = 0; i < 2; i++) {
		textureLevel_[i]->Draw();
	}*/
	if (bommLv >= 10) {
		textureLevel_[0]->Draw();
	}

	textureLevel_[1]->Draw();
}
