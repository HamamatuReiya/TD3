#pragma once
enum Stage {
	kTutorial,
	kIsland,
	kDesert,
	kVolcano,
};

class StageSelect
{ 
protected:
	static int stageNo;

public:
	int GetStageNo();
};