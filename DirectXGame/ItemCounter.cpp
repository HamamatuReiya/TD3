#include "ItemCounter.h"
#include "TextureManager.h"

void ItemCounter::Initialize() {

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

	// 取得した数 石
	for (int i = 0; i < 10; i++) {
		textureNumberStone_[i] = Sprite::Create(
		    numHandle_[i], {i * 50.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 金
	for (int i = 0; i < 10; i++) {
		textureNumberGold_[i] = Sprite::Create(
		    numHandle_[i], {i * 50.0f, 80.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 樹脂
	for (int i = 0; i < 10; i++) {
		textureNumberJushi_[i] = Sprite::Create(
		    numHandle_[i], {i * 50.0f, 160.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 貝
	for (int i = 0; i < 10; i++) {
		textureNumberShell_[i] = Sprite::Create(
		    numHandle_[i], {i * 50.0f, 240.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

}

void ItemCounter::Update(int stone, int gold, int jushi, int shell) {

	//石
	int sn = stone;
	stoneNum[0] = sn / 10;
	sn = sn % 10;
	stoneNum[1] = sn;

	for (int i = 0; i < 2; i++) {
		textureNumberStone_[i]->SetTextureHandle(numHandle_[stoneNum[i]]);
	}

	//金
	int gn = gold;
	goldNum[0] = gn / 10;
	gn = gn % 10;
	goldNum[1] = gn;

	for (int i = 0; i < 2; i++) {
		textureNumberGold_[i]->SetTextureHandle(numHandle_[goldNum[i]]);
	}

	//樹脂
	int jn = jushi;
	jushiNum[0] = jn / 10;
	jn = jn % 10;
	jushiNum[1] = jn;

	for (int i = 0; i < 2; i++) {
		textureNumberJushi_[i]->SetTextureHandle(numHandle_[jushiNum[i]]);
	}

	//貝
	int shn = shell;
	shellNum[0] = shn / 10;
	shn = shn % 10;
	shellNum[1] = shn;

	for (int i = 0; i < 2; i++) {
		textureNumberShell_[i]->SetTextureHandle(numHandle_[shellNum[i]]);
	}
}

void ItemCounter::Draw() {
	// 石
	for (int i = 0; i < 2; i++) {
		textureNumberStone_[i]->Draw();
	}
	// 金
	for (int i = 0; i < 2; i++) {
		textureNumberGold_[i]->Draw();
	}
	// 樹脂
	for (int i = 0; i < 2; i++) {
		textureNumberJushi_[i]->Draw();
	}
	// 貝
	for (int i = 0; i < 2; i++) {
		textureNumberShell_[i]->Draw();
	}
}
