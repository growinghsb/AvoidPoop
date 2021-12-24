#include "Stage.h"
#include "Player.h"

Stage* Stage::mStage = nullptr;

Stage::Stage()
{
	mObjs.reserve(128);
	mObjs.push_back(new Player(FPOINT{80, 80}, 60, 200.f));
}

Stage::~Stage()
{
	for (int i = 0; i < mObjs.size(); ++i) 
	{
		delete mObjs[i];
	}
}

Stage* Stage::getInstance()
{
	if (nullptr == mStage) 
	{
		mStage = new Stage;
	}
	return mStage;
}

void Stage::deleteInstance()
{
	if (nullptr != mStage) 
	{
		delete mStage;
		mStage = nullptr;
	}
}

void Stage::init()
{
}

void Stage::update()
{
	for (int i = 0; i < mObjs.size(); ++i) 
	{
		mObjs[i]->update();
	}
}

void Stage::render(HDC backDC)
{
	for (int i = 0; i < mObjs.size(); ++i)
	{
		mObjs[i]->render(backDC);
	}
}
