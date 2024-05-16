#pragma once
enum Stage {
	kTutorial,
	kTown,
};

class StageSelect
{ 
protected:
	static int stageNo;

public:
	int GetStageNo();
};