#include "BommEnhance.h"
#include <ImGuiManager.h>

void BommEnhance::Initialize() { 
	for (int i = 1; i <= 10; i++) {
		expMax[i] = 10 * i;
	}
	 
}

void BommEnhance::Update(int stone, int gold, int jushi, int shell) {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
		    !(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			exp += stone * 2; 
			exp += gold * 2;
			exp += jushi * 2;
			exp += shell * 2;

			if (exp >= expMax[0] && bommLv >= 2) {
				bommLv += 1;
			}


		}
	}
#ifdef _DEBUG
	ImGui::Begin("BommEnhance");
	ImGui::Text("exp : %d", exp);
	ImGui::Text("bommLv : %d", bommLv);
	ImGui::End();
#endif !_DEBUG
}
