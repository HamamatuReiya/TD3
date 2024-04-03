#include "Ranking.h"
#include "TextureManager.h"

void Ranking::Initialize() {
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
	for (int i = 0; i < 5; i++) {
		textureRanking1_[i] = Sprite::Create(
		    numHandle_[i], {300.0f + i * 50.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

		textureRanking2_[i] = Sprite::Create(
		    numHandle_[i], {300.0f + i * 50.0f, 120.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

		textureRanking3_[i] = Sprite::Create(
		    numHandle_[i], {300.0f + i * 50.0f, 240.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

		textureRanking4_[i] = Sprite::Create(
		    numHandle_[i], {300.0f + i * 50.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

		textureRanking5_[i] = Sprite::Create(
		    numHandle_[i], {300.0f + i * 50.0f, 480.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

	ranking[0] = 14000;
	ranking[1] = 11000;
	ranking[2] = 10000;
	ranking[3] = 9900;
	ranking[4] = 8000;
}

void Ranking::Update(int score) {
	
	score_ = score;

	for (int i = 0; i < 5; i++) {
		if (ranking[i] < score_) {
			scoreKeep_ = ranking[i];
			ranking[i] = score_;
			score_ = scoreKeep_;
		}
	}


	Division(ranking[0], ranking[1], ranking[2], ranking[3], ranking[4]);

	for (int i = 0; i < 5; i++) {
		textureRanking1_[i]->SetTextureHandle(numHandle_[num1[i]]);
		textureRanking2_[i]->SetTextureHandle(numHandle_[num2[i]]);
		textureRanking3_[i]->SetTextureHandle(numHandle_[num3[i]]);
		textureRanking4_[i]->SetTextureHandle(numHandle_[num4[i]]);
		textureRanking5_[i]->SetTextureHandle(numHandle_[num5[i]]);
		
	}
}

void Ranking::Draw() {
	for (int i = 0; i < 5; i++) {
		textureRanking1_[i]->Draw();
		textureRanking2_[i]->Draw();
		textureRanking3_[i]->Draw();
		textureRanking4_[i]->Draw();
		textureRanking5_[i]->Draw();
	}
}

void Ranking::Division(int rank1, int rank2, int rank3, int rank4, int rank5) {

	//1位
	num1[0] = rank1 / 10000;
	rank1 = rank1 % 10000;

	num1[1] = rank1 / 1000;
	rank1 = rank1 % 1000;

	num1[2] = rank1 / 100;
	rank1 = rank1 % 100;

	num1[3] = rank1 / 10;
	rank1 = rank1 % 10;

	num1[4] = rank1;

	//2位
	num2[0] = rank2 / 10000;
	rank2 = rank2 % 10000;

	num2[1] = rank2 / 1000;
	rank2 = rank2 % 1000;

	num2[2] = rank2 / 100;
	rank2 = rank2 % 100;

	num2[3] = rank2 / 10;
	rank2 = rank2 % 10;

	num2[4] = rank2;

	//3位
	num3[0] = rank3 / 10000;
	rank3 = rank3 % 10000;

	num3[1] = rank3 / 1000;
	rank3 = rank3 % 1000;

	num3[2] = rank3 / 100;
	rank3 = rank3 % 100;

	num3[3] = rank3 / 10;
	rank3 = rank3 % 10;

	num3[4] = rank3;

	//4位
	num4[0] = rank4 / 10000;
	rank4 = rank4 % 10000;

	num4[1] = rank4 / 1000;
	rank4 = rank4 % 1000;

	num4[2] = rank4 / 100;
	rank4 = rank4 % 100;

	num4[3] = rank4 / 10;
	rank4 = rank4 % 10;

	num4[4] = rank4;

	//5位
	num5[0] = rank5 / 10000;
	rank5 = rank5 % 10000;

	num5[1] = rank5 / 1000;
	rank5 = rank5 % 1000;

	num5[2] = rank5 / 100;
	rank5 = rank5 % 100;

	num5[3] = rank5 / 10;
	rank5 = rank5 % 10;

	num5[4] = rank5;
}
