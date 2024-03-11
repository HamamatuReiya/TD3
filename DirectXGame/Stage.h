#pragma once
enum Stage {
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