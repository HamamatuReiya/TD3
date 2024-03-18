#include "Score.h"
#include "TextureManager.h"

void Score::Initialize() {

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
	for (int i = 0; i < 10; i++) {
		textureNumber_[i] = Sprite::Create(
		    numHandle_[i], {i * 50.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
}

void Score::Update(int score) {
	
	int n = score;
	num[0] = n / 10000;
	n = n % 10000;
	
	num[1] = n / 1000;
	n = n % 1000;

	num[2] = n / 100;
	n = n % 100;

	num[3] = n / 10;
	n = n % 10;

	num[4] = n;

	textureNumber_[0]->SetTextureHandle(numHandle_[num[0]]);
	textureNumber_[1]->SetTextureHandle(numHandle_[num[1]]);
	textureNumber_[2]->SetTextureHandle(numHandle_[num[2]]);
	textureNumber_[3]->SetTextureHandle(numHandle_[num[3]]);
	textureNumber_[4]->SetTextureHandle(numHandle_[num[4]]);
}

void Score::Draw() {

	for (int i = 0; i < 5; i++) {
		textureNumber_[i]->Draw();
	}
}
