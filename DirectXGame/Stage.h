#pragma once
enum Stage {
	kTutorial,
	kTown,
	kForest,
	kVolcano,
};

class StageSelect
{ 
protected:
	static int stageNo;

public:
	int GetStageNo();
};