#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "TimeManager.h"
#include "Bullet.h"

Stage* Stage::mStage = nullptr;

Stage::Stage()
{
	mObjs.reserve(128);
	mObjs.push_back(new Player(FPOINT{ 80, 80 }, 60, 200.f));

	createMonster();
}

Stage::~Stage()
{
	size_t size = mObjs.size();
	for (size_t i = 0; i < size; ++i)
	{
		delete mObjs[i];
		mObjs[i] = nullptr;
	}

	while (!mMonsters.empty())
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
	// monster 
	static float ds = 0.f;
	ds += DS;

	float regenTime = mMonsters.empty() ? 0.4f : mMonsters.front()->getRegenTime();
	if (ds >= regenTime)
	{
		ds -= 0.4f;
		createMonster();
	}

	auto iter = mMonsters.begin();
	auto endIter = mMonsters.end();

	for (; iter != endIter; ++iter)
	{
		(*iter)->update();
	}

	// obj
	for (int i = 0; i < mObjs.size(); ++i)
	{
		mObjs[i]->update();
	}
}

void Stage::render(HDC backDC)
{
	auto iter = mMonsters.begin();
	auto endIter = mMonsters.end();

	SelectObject(backDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(backDC, RGB(200, 0, 0));
	for (; iter != endIter; ++iter)
	{
		(*iter)->render(backDC);
	}

	SetDCBrushColor(backDC, RGB(255, 255, 255));
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

			inValidMonster->changePos(FPOINT{ randX, 0 });
			inValidMonster->changeSize(randSize);
			inValidMonster->changeSpeed(randSpeed);

			mMonsters.push_back(inValidMonster);
		}
	}
}

// �Ѿ� �ϳ��� ���ؼ� ��� ���� �浹 üũ
bool Stage::CrushMonsterRemove(Bullet& bullet)
{
	auto iter = mMonsters.begin();
	auto endIter = mMonsters.end();

	int x2;
	int y2;
	int x2y2;
	int radiusSum;

	while (iter != endIter)
	{
		x2 = abs((*iter)->getCenter().x - bullet.getCenter().x);
		x2 *= x2;

		y2 = abs((*iter)->getCenter().y - bullet.getCenter().y);
		y2 *= y2;

		x2y2 = x2 + y2;

		radiusSum = (*iter)->getSize() / 2 + bullet.getSize() / 2;
		radiusSum *= radiusSum;

		if (x2y2 <= radiusSum)
		{
			// ������ �������� ���߿��� hp ��°ɷ� ����
			mMonsters.erase(iter);
			return true;
		}
		++iter;
	}
	return false;
}