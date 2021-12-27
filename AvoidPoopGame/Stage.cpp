#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "Core.h"
#include "TimeManager.h"
#include "Bullet.h"
#include "Item.h"

Stage* Stage::mStage = nullptr;

Stage::Stage()
	: mMonsterScale(1.f)
	, mMonsterRegenTime(0.4f)
	, mItemTypes{ ITEM_TYPE::BULLTE_SIZE_UP,
				ITEM_TYPE::OFFENCE_POWER_UP }
{
	mObjs.reserve(128);
	mObjs.push_back(new Player(FPOINT{ 80, 80 }, 60, 200.f));

	createMonster();
}

Stage::~Stage()
{
	int size = (int)mObjs.size();

	for (int i = size - 1; i >= 0; --i)
	{
		delete mObjs[i];
		mObjs.pop_back();
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

	// item
	auto itemIter = mItems.begin();
	auto itemEndIter = mItems.end();

	while (itemIter != itemEndIter) 
	{
		(*itemIter)->update();
		++itemIter;
	}
}

void Stage::render(HDC backDC)
{
	// monster
	auto iter = mMonsters.begin();
	auto endIter = mMonsters.end();

	for (; iter != endIter; ++iter)
	{
		(*iter)->render(backDC);
	}

	// obj
	SetDCBrushColor(backDC, RGB(255, 255, 255));

	for (int i = 0; i < mObjs.size(); ++i)
	{
		mObjs[i]->render(backDC);
	}

	// item
	auto itemIter = mItems.begin();
	auto itemEndIter = mItems.end();
	SetDCBrushColor(backDC, RGB(238, 247, 106));

	while (itemIter != itemEndIter)
	{
		(*itemIter)->render(backDC);
		++itemIter;
	}
}

void Stage::createMonster()
{
	float randX = float(rand() % WINDOW.right);
	int randSize = rand() % 130 + 20;
	float randSpeed = (float)(rand() % 500) + 200;
	int hp = randSize / 10;

	if (mMonsters.empty())
	{
		mMonsters.push_back(new Monster(FPOINT{ randX, 0 }, randSize, randSpeed, mMonsterScale, mMonsterRegenTime, hp));
	}
	else
	{
		if (mMonsters.front()->isValid())
		{
			mMonsters.push_back(new Monster(FPOINT{ randX, 0 }, randSize, randSpeed, mMonsterScale, mMonsterRegenTime, hp));
		}
		else
		{
			Monster* inValidMonster = mMonsters.front();
			mMonsters.pop_front();

			inValidMonster->changePos(FPOINT{ randX, 0 });
			inValidMonster->changeSize(randSize);
			inValidMonster->changeSpeed(randSpeed);
			inValidMonster->changeHP(hp);

			mMonsters.push_back(inValidMonster);
		}
	}
}

void Stage::createItem(Monster& monster)
{
	int typeNum = rand() % (UINT)ITEM_TYPE::END;

	if (mItems.empty())
	{
		mItems.push_back(new Item(FPOINT{ monster.getPos() }, 30, monster.getSpeed(), mItemTypes[typeNum]));
	}
	else 
	{
		if (mItems.front()->isValid()) 
		{
			mItems.push_back(new Item(FPOINT{ monster.getPos() }, 30, monster.getSpeed(), mItemTypes[typeNum]));
		}
		else 
		{
			Item* inValidItem = mItems.front();
			mItems.pop_front();

			inValidItem->changePos(monster.getPos());
			inValidItem->changeSpeed(monster.getSpeed());
			inValidItem->changeItemType(mItemTypes[typeNum]);

			mItems.push_back(inValidItem);
		}
	}
}

// 총알 하나에 대해서 모든 몬스터 충돌 체크
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
			// HP 비교 후 죽었는지 체크, 죽었으면 지우고, 아니면 그대로 진행
			(*iter)->changeHP((*iter)->getHP() - bullet.getOffensePower());

			if ((*iter)->isDie())
			{
				createItem(*(*iter)); // 몬스터 위치로부터 아이템 생성
				mMonsters.erase(iter);
			}
			return true;
		}
		++iter;
	}
	return false;
}