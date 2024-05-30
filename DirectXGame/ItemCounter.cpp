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

	multiplyHandle_ = TextureManager::Load("./Resources/number/x.png");

	stoneHandle_ = TextureManager::Load("./Resources/material/miniStone.png");
	goldHandle_ = TextureManager::Load("./Resources/material/miniGold.png");
	jushiHandle_ = TextureManager::Load("./Resources/material/miniJushi.png");
	shellHandle_ = TextureManager::Load("./Resources/material/miniShell.png");
	

	// 取得した数 石
	for (int i = 0; i < 10; i++) {
		textureNumberStone_[i] = Sprite::Create(
		    numHandle_[i], {i * 55.0f + 100, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 金
	for (int i = 0; i < 10; i++) {
		textureNumberGold_[i] = Sprite::Create(
		    numHandle_[i], {i * 55.0f + 100, 80.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 樹脂
	for (int i = 0; i < 10; i++) {
		textureNumberJushi_[i] = Sprite::Create(
		    numHandle_[i], {i * 55.0f + 100, 160.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 貝
	for (int i = 0; i < 10; i++) {
		textureNumberShell_[i] = Sprite::Create(
		    numHandle_[i], {i * 55.0f + 100, 240.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

	//ウィンドウ
	//  取得した数 石 
	for (int i = 0; i < 10; i++) {
		textureNumberWindowStone_[i] = Sprite::Create(
		    numHandle_[i], {i * 55.0f + 150.0f, 400.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 金
	for (int i = 0; i < 10; i++) {
		textureNumberWindowGold_[i] = Sprite::Create(
		    numHandle_[i], {i * 55.0f + 320.0f, 600.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 樹脂
	for (int i = 0; i < 10; i++) {
		textureNumberWindowJushi_[i] = Sprite::Create(
		    numHandle_[i], {i * 55.0f + 890.0f, 600.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 貝
	for (int i = 0; i < 10; i++) {
		textureNumberWindowShell_[i] = Sprite::Create(
		    numHandle_[i], {i * 55.0f + 1070.0f, 400.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

	//　取得した石
	textureStone_ =
	    Sprite::Create(stoneHandle_, {1.0f, 5.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	//　取得した金
	textureGold_ =
	    Sprite::Create(goldHandle_, {1.0f, 85.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	//　取得した樹脂
	textureJushi_ =
	    Sprite::Create(jushiHandle_, {1.0f, 165.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	//　取得した貝
	textureShell_ =
	    Sprite::Create(shellHandle_, {1.0f, 245.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	//掛ける
	for (int i = 0; i < 4; i++) {
		textureMultiply_[i] = Sprite::Create(
		    multiplyHandle_, {50.0f, i * 80.0f + 5}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	
}

void ItemCounter::Update(int stone, int gold, int jushi, int shell) {

	// 石
	int sn = stone;
	stoneNum[0] = sn / 10;
	sn = sn % 10;
	stoneNum[1] = sn;

	for (int i = 0; i < 2; i++) {
		textureNumberStone_[i]->SetTextureHandle(numHandle_[stoneNum[i]]);
	}
	for (int i = 0; i < 2; i++) {
		textureNumberWindowStone_[i]->SetTextureHandle(numHandle_[stoneNum[i]]);
	}

	// 金
	int gn = gold;
	goldNum[0] = gn / 10;
	gn = gn % 10;
	goldNum[1] = gn;

	for (int i = 0; i < 2; i++) {
		textureNumberGold_[i]->SetTextureHandle(numHandle_[goldNum[i]]);
	}
	for (int i = 0; i < 2; i++) {
		textureNumberWindowGold_[i]->SetTextureHandle(numHandle_[goldNum[i]]);
	}

	// 樹脂
	int jn = jushi;
	jushiNum[0] = jn / 10;
	jn = jn % 10;
	jushiNum[1] = jn;

	for (int i = 0; i < 2; i++) {
		textureNumberJushi_[i]->SetTextureHandle(numHandle_[jushiNum[i]]);
	}
	for (int i = 0; i < 2; i++) {
		textureNumberWindowJushi_[i]->SetTextureHandle(numHandle_[jushiNum[i]]);
	}

	// 貝
	int shn = shell;
	shellNum[0] = shn / 10;
	shn = shn % 10;
	shellNum[1] = shn;

	for (int i = 0; i < 2; i++) {
		textureNumberShell_[i]->SetTextureHandle(numHandle_[shellNum[i]]);
	}
	for (int i = 0; i < 2; i++) {
		textureNumberWindowShell_[i]->SetTextureHandle(numHandle_[shellNum[i]]);
	}

	//掛ける
	for (int i = 0; i < 4; i++) {
		textureMultiply_[i]->SetTextureHandle(multiplyHandle_);
	}

	//石
	textureStone_->SetTextureHandle(stoneHandle_);
	//金
	textureGold_->SetTextureHandle(goldHandle_);
    //樹脂
	textureJushi_->SetTextureHandle(jushiHandle_);
	//貝
	textureShell_->SetTextureHandle(shellHandle_);
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

	for (int i = 0; i < 4; i++) {
		textureMultiply_[i]->Draw();
	}

	// 石
	textureStone_->Draw();
	// 金
	textureGold_->Draw();
	// 樹脂
	textureJushi_->Draw();
	// 貝
	textureShell_->Draw();
}

void ItemCounter::WindowDraw() {
	// ウィンドウ
	//  石
	for (int i = 0; i < 2; i++) {
		textureNumberWindowStone_[i]->Draw();
	}
	// 金
	for (int i = 0; i < 2; i++) {
		textureNumberWindowGold_[i]->Draw();
	}
	// 樹脂
	for (int i = 0; i < 2; i++) {
		textureNumberWindowJushi_[i]->Draw();
	}
	// 貝
	for (int i = 0; i < 2; i++) {
		textureNumberWindowShell_[i]->Draw();
	}
}
