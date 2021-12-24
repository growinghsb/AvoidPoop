#pragma once

#include "Game.h"

class Stage
{
public:
	static Stage* getInstance();
	static void deleteInstance();

	void init();
	void update();
	void render(HDC backDC);

private:
	Stage();
	~Stage();

	static Stage* mStage;

	vector<class Obj*> mObjs;
};

