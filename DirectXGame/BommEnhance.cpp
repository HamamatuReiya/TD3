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

	for (int i = 1; i <= 9; i++) {
		expMax[i] = 10 * (i);
	}

	 expMax[10] = 99999;
}

void BommEnhance::Update(int stone, int gold, int jushi, int shell) {
	exp += stone * 1;
	exp += gold * 5;
	exp += jushi * 1;
	exp += shell * 2;

	while (exp >= expMax[bommLv]) {
		exp -= expMax[bommLv];
		bommLv++;
	}

	int Lv = bommLv;

	Level[0] = Lv / 10;
	Lv = Lv % 10;

	Level[1] = Lv;

	for (int i = 0; i < 2; i++) {
		textureLevel_[i]->SetTextureHandle(numHandle_[Level[i]]);
	}

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
	if (bommLv < 10) {
		textureLevel_[1]->Draw();
	} else if (bommLv >= 10) {
		textureLevel_[0]->Draw();
		textureLevel_[1]->Draw();
	}
}
