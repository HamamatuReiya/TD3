#include "BommEnhance.h"
#include <ImGuiManager.h>

void BommEnhance::Initialize() { 

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
