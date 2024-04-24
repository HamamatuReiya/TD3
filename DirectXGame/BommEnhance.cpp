#include "BommEnhance.h"
#include <ImGuiManager.h>

void BommEnhance::Initialize() { 
	for (int i = 0; i < 10; i++) {
		expMax[i] = 10 * i;
	}
	 
}

void BommEnhance::Update(int stone, int gold, int jushi, int shell) {
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A &&
		    !(joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)) {
			exp += stone;
			exp += gold;
			exp += jushi;
			exp += shell;

			for (int i = 0; i < 10; i++) {
				if (exp >= expMax[i] && bommLv >= i + 1) {
					bommLv += 1;
					exp = 0;
				}
			}
		}
	}
	
	ImGui::Begin("BommEnhance");
	ImGui::Text("exp : %d", exp);
	ImGui::Text("bommLv : %d", bommLv);
	ImGui::End();
}
