#include "BommEnhance.h"
#include <ImGuiManager.h>

void BommEnhance::Initialize() { 
	expMax[0] = 10;
	expMax[1] = 20;
	expMax[2] = 30;
	expMax[3] = 40;
	expMax[4] = 50;
	expMax[5] = 60;
	expMax[6] = 70;
	expMax[7] = 80;
	expMax[8] = 90;
	expMax[9] = 100;
	 
}

void BommEnhance::Update(int stone, int gold, int jushi, int shell) {
	exp += stone * 2;
	exp += gold * 2;
	exp += jushi * 2;
	exp += shell * 2;

	// 1
	if (exp >= expMax[0] && bommLv == 1) {
		bommLv += 1;
		exp = 0;
	}
	// 2 
	if (exp >= expMax[1] && bommLv == 2) {
		bommLv += 1;
		exp = 0;
	}
	// 3
	if (exp >= expMax[2] && bommLv == 3) {
		bommLv += 1;
		exp = 0;
	}
	// 4
	if (exp >= expMax[3] && bommLv == 4) {
		bommLv += 1;
		exp = 0;
	}
	// 5
	if (exp >= expMax[4] && bommLv == 5) {
		bommLv += 1;
		exp = 0;
	}
	// 6
	if (exp >= expMax[5] && bommLv == 6) {
		bommLv += 1;
		exp = 0;
	}
	// 7
	if (exp >= expMax[6] && bommLv == 7) {
		bommLv += 1;
		exp = 0;
	}
	// 8
	if (exp >= expMax[7] && bommLv == 8) {
		bommLv += 1;
		exp = 0;
	}
	// 9
	if (exp >= expMax[8] && bommLv == 9) {
		bommLv += 1;
		exp = 0;
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
