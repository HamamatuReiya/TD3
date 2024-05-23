#include "Timer.h"
#include "TextureManager.h"

void Timer::Initialize() {
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
	for (int i = 0; i < 3; i++) {
		textureTimer_[i] = Sprite::Create(
		    numHandle_[i], {600.0f + i * 50.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
}

void Timer::Update(int timer) {
	timer = timer / 60;
	int n = timer;

	if (n >= 0) {
		num[0] = n / 100;
		n = n % 100;

		num[1] = n / 10;
		n = n % 10;

		num[2] = n;
	}
	
	for (int i = 0; i < 3; i++) {
		textureTimer_[i]->SetTextureHandle(numHandle_[num[i]]);
	}
}

void Timer::Draw() {
	for (int i = 0; i < 3; i++) {
		textureTimer_[i]->Draw();
	}
}
