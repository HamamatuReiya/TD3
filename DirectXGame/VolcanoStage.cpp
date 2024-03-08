#include "VolcanoStage.h"

VolcanoStage::VolcanoStage() {}

VolcanoStage::~VolcanoStage() {}

void VolcanoStage::Initialize() {
	
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void VolcanoStage::Update() {
	
}

void VolcanoStage::Draw() {

}

void VolcanoStage::StageReset() {}

