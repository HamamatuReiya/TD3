﻿#include "BommEnhance.h"

void BommEnhance::Initialize() { 
	for (int i = 0; i < 10; i++) {
		expMax[i] = 10 * i;
	}
	 
}

void BommEnhance::Update(int stone, int gold, int jushi, int shell) {
	
	exp += stone;
	exp += gold;
	exp += jushi;
	exp += shell;

	for (int i = 0; i < 10; i++) {
		if (exp >= expMax[i]) {
			bommLv += 1;
			exp = 0;
		}
	}
}
