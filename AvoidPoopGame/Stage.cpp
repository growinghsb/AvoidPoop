#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "TimeManager.h"

Stage* Stage::mStage = nullptr;

Stage::Stage()
{
	mObjs.reserve(128);
	mObjs.push_back(new Player(FPOINT{ 80, 80 }, 60, 200.f));

	createMonster();
}

Stage::~Stage()
{
	int size = mObjs.size();
	for (int i = 0; i < size; ++i)
	{
		delete mObjs[i];
		mObjs[i] = nullptr;
	}

	size = mMonsters.size();
	for (int i = 0; i < size; ++i) 
	{
		delete mMonsters.front();
		mMonsters.pop_front();
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
	for (int i = 0; i < mObjs.size(); ++i)
	{
		mObjs[i]->init();
	}
}

void Stage::update()
{
	static float ds = 0.f;
	ds += DS;

	if (ds >= 0.5f) 
	{
		ds -= 0.5f;
		createMonster();
	}

	auto iter = mMonsters.begin();
	auto endIter = mMonsters.end();

	for (; iter != endIter; ++iter) 
	{
		(*iter)->update();
	}

	for (int i = 0; i < mObjs.size(); ++i)
	{
		mObjs[i]->update();
	}
}

void Stage::render(HDC backDC)
{
	auto iter = mMonsters.begin();
	auto endIter = mMonsters.end();

	for (; iter != endIter; ++iter)
	{
		(*iter)->render(backDC);
	}

	for (int i = 0; i < mObjs.size(); ++i)
	{
		mObjs[i]->render(backDC);
	}
}

void Stage::createMonster()
{
	

	float randX = float(rand() % WINDOW.right);
	int randSize = rand() % 130 + 20;
	float randSpeed = (float)(rand() % 500) + 200;

	if (mMonsters.empty())
	{
		mMonsters.push_back(new Monster(FPOINT{ randX, 0 }, randSize, randSpeed, 1.f));
	}
	else
	{
		if (mMonsters.front()->isValid())
		{
			mMonsters.push_back(new Monster(FPOINT{ randX, 0 }, randSize, randSpeed, 1.f));
		}
		else
		{
			Monster* inValidMonster = mMonsters.front();
			mMonsters.pop_front();

			inValidMonster->changePos(FPOINT{randX, 0});
			inValidMonster->changeSize(randSize);
			inValidMonster->changeSpeed(randSpeed);

			mMonsters.push_back(inValidMonster);
		}
	}
}