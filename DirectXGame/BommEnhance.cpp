#include "BommEnhance.h"
#include <ImGuiManager.h>
#include "TextureManager.h"
static int bommLv = 1;
// 数字の画像
static Sprite* textureLevel_[2];
static Sprite* textureExp_[3];
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

	//スラッシュ
	slashHandle_ = TextureManager::Load("./Resources/number/slash.png");
	textureSlash_ = Sprite::Create(
	    slashHandle_, {230.0f, 10.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	//exp
	expHandle_ = TextureManager::Load("./Resources/number/EXP.png");
	texturePowerUpExp_ = Sprite::Create(expHandle_, {1.0f, 10.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	// 取得した数
	for (int i = 0; i < 2; i++) {
		textureLevel_[i] = Sprite::Create(
		    numHandle_[i], {630.0f + i * 55.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

	//経験値表示
	for (int i = 0; i < 3; i++) {
		textureExp_[i] = Sprite::Create(
		    numHandle_[i], {75.0f + i * 55.0f, 10.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

	//経験値の最大値
	for (int i = 0; i < 3; i++) {
		textureMaxexp_[i] = Sprite::Create(
		    numHandle_[i], {280.0f + i * 55.0f, 10.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

	exp = 0;
	for (int i = 1; i <= 9; i++) {
		expMax[i] = 5 * (i);
	}
	
	expMax[10] = 99999;
	int expTex = exp;

	expP[0] = exp / 100;
	expTex = expTex % 100;

	expP[1] = exp / 10;
	expTex = expTex % 10;

	expP[2] = expTex;

	for (int i = 0; i < 3; i++) {
		textureExp_[i]->SetTextureHandle(numHandle_[expP[i]]);
	}

	int expMaxDisplay = expMax[bommLv];
	expMaxP[0] = expMax[bommLv] / 100;
	expMaxDisplay = expMaxDisplay % 100;

	expMaxP[1] = expMax[bommLv] / 10;
	expMaxDisplay = expMaxDisplay % 10;

	expMaxP[2] = expMaxDisplay;

	for (int i = 0; i < 3; i++) {
		textureMaxexp_[i]->SetTextureHandle(numHandle_[expMaxP[i]]);
	}
}

void BommEnhance::Update(int stone, int gold, int jushi, int shell) {
	exp += stone * 2;
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

	int expTex = exp;

	expP[0] = exp / 100;
	expTex = expTex % 100;

	expP[1] = exp / 10;
	expTex = expTex % 10;

	expP[2] = expTex;

	for (int i = 0; i < 3; i++) {
		textureExp_[i]->SetTextureHandle(numHandle_[expP[i]]);
	}

	int expMaxDisplay = expMax[bommLv];
	expMaxP[0] = expMax[bommLv] / 100;
	expMaxDisplay = expMaxDisplay % 100;

	expMaxP[1] = expMax[bommLv] / 10;
	expMaxDisplay = expMaxDisplay % 10;

	expMaxP[2] = expMaxDisplay;

	for (int i = 0; i < 3; i++) {
		textureMaxexp_[i]->SetTextureHandle(numHandle_[expMaxP[i]]);
	}

	textureSlash_->SetTextureHandle(slashHandle_);

	texturePowerUpExp_->SetTextureHandle(expHandle_);

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

	for (int i = 0; i < 3; i++) {
		textureExp_[i]->Draw();
	}

	for (int i = 0; i < 3; i++) {
		textureMaxexp_[i]->Draw();
	}

	textureSlash_->Draw();
	texturePowerUpExp_->Draw();
}

void BommEnhance::ResultDraw() {
	if (bommLv < 10) {
		textureLevel_[1]->Draw();
	} else if (bommLv >= 10) {
		textureLevel_[0]->Draw();
		textureLevel_[1]->Draw();
	}
}

void BommEnhance::RoopInitialize() { 
	bommLv = 1;
	for (int i = 1; i <= 9; i++) {
		expMax[i] = 5 * (i);
	}
	exp = 0;
	expMax[10] = 99999;
}
