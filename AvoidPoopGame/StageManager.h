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

	class Texture* getCurrentPlayerTexture() const
	{
		return mCurrentPlayer;
	}

	void setCurrentPlayer(Texture* texture) 
	{
		mCurrentPlayer = texture;
	}

private:
	StageManager();
	~StageManager();

	static StageManager* mStageManager;
	vector<class Stage*> mStages;
	class Stage* mCurrentStage;
	class Texture* mCurrentPlayer;
};

