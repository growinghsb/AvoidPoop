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
	, mItemColors{ COLOR{238, 247, 106}, COLOR{255, 264, 238} }
{
	mObjs.reserve(128);
	mObjs.push_back(new Player(FPOINT{ 80, 80 }, 60, 200.f));

	createMonster();
}

Stage::~Stage()
{
	int size = (int)mObjs.size();
	for (int i = 0; i < size; ++i)
	{
		delete mObjs[i];
	}
	mObjs.clear();

	while (!mMonsters.empty())
	{
		delete mMonsters.front();
		mMonsters.pop_front();
	}

	while (!mItems.empty())
	{
		delete mItems.front();
		mItems.pop_front();
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

	auto monsterIter = mMonsters.begin();
	auto monsterEndIter = mMonsters.end();

	while (monsterIter != monsterEndIter)
	{
		(*monsterIter)->update();
		++monsterIter;
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
	auto monsterIter = mMonsters.begin();
	auto monsterEndIter = mMonsters.end();

	for (; monsterIter != monsterEndIter; ++monsterIter)
	{
		(*monsterIter)->render(backDC);
	}

	// obj
	SetDCBrushColor(backDC, COLOR_WHITE);
	for (int i = 0; i < mObjs.size(); ++i)
	{
		mObjs[i]->render(backDC);
	}

	// item
	auto itemIter = mItems.begin();
	auto itemEndIter = mItems.end();
	COLOR color;

	while (itemIter != itemEndIter)
	{
		color = (*itemIter)->getItemColor();
		SetDCBrushColor(backDC, RGB(color.r, color.g, color.b));
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
	int colorNum = rand() % (UINT)ITEM_TYPE_COLOR::END;

	if (mItems.empty())
	{
		mItems.push_back(new Item(FPOINT{ monster.getPos() }, 30, monster.getSpeed(), mItemTypes[typeNum], mItemColors[colorNum]));
	}
	else
	{
		if (mItems.front()->isValid())
		{
			mItems.push_back(new Item(FPOINT{ monster.getPos() }, 30, monster.getSpeed(), mItemTypes[typeNum], mItemColors[colorNum]));
		}
		else
		{
			Item* inValidItem = mItems.front();
			mItems.pop_front();

			inValidItem->changePos(monster.getPos());
			inValidItem->changeSpeed(monster.getSpeed());
			inValidItem->changeItemType(mItemTypes[typeNum]);
			inValidItem->changeItemColor(mItemColors[colorNum]);
			mItems.push_back(inValidItem);
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

	int bulletCenterX = bullet.getCenter().x;
	int bulletCenterY = bullet.getCenter().y;
	int bulletRadius = bullet.getSize() / 2;
	int bulletOffensePower = bullet.getOffensePower();

	while (iter != endIter)
	{
		x2 = abs((*iter)->getCenter().x - bulletCenterX);
		x2 *= x2;

		y2 = abs((*iter)->getCenter().y - bulletCenterY);
		y2 *= y2;

		x2y2 = x2 + y2;

		radiusSum = (*iter)->getSize() / 2 + bulletRadius;
		radiusSum *= radiusSum;

		if (x2y2 <= radiusSum)
		{
			// HP �� �� �׾����� üũ, �׾����� �����, �ƴϸ� �״�� ����
			(*iter)->changeHP((*iter)->getHP() - bulletOffensePower);

			if ((*iter)->isDie())
			{
				if (rand() % 3 == 0) 
				{
					createItem(*(*iter)); // ���� ��ġ�κ��� ������ ����
				}

				// �� erase �ϱ� ���� �����͸� ���� �����ؾ� �Ѵ�. 
				// �׷��� �ּҸ� �Ҿ������ �ʰ� ���� �� �ִ�. 
				delete (*iter);
				mMonsters.erase(iter);
			}
			return true;
		}
		++iter;
	}
	return false;
}