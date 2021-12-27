#pragma once

#include "Game.h"

class StageManager
{
public:
	static StageManager* getInstance();
	static void deleteInstance();
	
	void init();
	void update();
	void render(HDC backDC);

	void changeNextStage();
	void changePrevStage();

	class Stage* getCurrentStage() const;

private:
	StageManager();
	~StageManager();

	static StageManager* mStageManager;
	vector<class Stage*> mStages;
	class Stage* mCurrentStage;
};

