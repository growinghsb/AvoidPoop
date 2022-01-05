#include "PlayStage.h"
#include "Core.h"
#include "Player.h"
#include "TimeManager.h"
#include "Monster.h"
#include "Item.h"
#include "Bullet.h"
#include "StageManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "EventManager.h"

PlayStage::PlayStage(int order)
	: Stage(order)
	, mMonsterScale(1.f)
	, mMonsterRegenTime(0.4f)
{
	mObjs.reserve(128);
}

PlayStage::~PlayStage()
{
	stageClear();
}

// 해당 스테이지가 처음 올라왔을 때 해야 할 일을 하는 함수
// 일단 기본적으로 init 을 호출해 주어야 한다. 
// 여기서만 init() 을 부를 수 있다.
void PlayStage::enter()
{
	init();
}

void PlayStage::init()
{
	mObjs.push_back(new Player(FPOINT{ (float)WINDOW.right / 2, (float)WINDOW.bottom / 2 }, 50, 200.f, StageManager::getInstance()->getCurrentPlayerTexture()));

	createMonster();

	for (int i = 0; i < mObjs.size(); ++i)
	{
		mObjs[i]->init();
	}
}

void PlayStage::update()
{
	static float second = 0.f;
	second += DS;

	if ((int)second >= 3) 
	{
		ChangeStage(eEVENT_TYPE::CHANGE_STAGE, STAGE_MODE::NEXT);
		second = 0.f;

		return;
	}

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

	while (iter != endIter)
	{
		(*iter)->update();
		++iter;
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

	// 아이템 대 플레이어 충돌체크
	crushCheckItemPlayer();

	// 몬스터 대 플레이어 충돌체크
	crushCheckMonsterPlayer();
}

void PlayStage::render(HDC backDC)
{
	// monster
	auto iter = mMonsters.begin();
	auto endIter = mMonsters.end();

	for (; iter != endIter; ++iter)
	{
		(*iter)->render(backDC);
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

// 해당 스테이지가 다음이든, 이전이든,
// 다른 스테이지로 바뀔 때 호출되는 함수
// 여기서 해당 스테이지에 대한 정리를 한다
// 다시 들어왔을 때 문제 생기지 않도록
void PlayStage::exit()
{
	stageClear();
}

void PlayStage::stageClear()
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

bool PlayStage::crushMonsterRemove(Bullet& bullet)
{
	auto iter = mMonsters.begin();
	auto endIter = mMonsters.end();

	while (iter != endIter)
	{
		if (circleCrushCircle(bullet.getCenter(), bullet.getSize() / 2, (*iter)->getCenter(), (*iter)->getSize() / 2))
		{
			// HP 비교 후 죽었는지 체크, 죽었으면 지우고, 아니면 그대로 진행
			(*iter)->changeHP((*iter)->getHP() - bullet.getOffensePower());

			if ((*iter)->isDie())
			{
				if (rand() % 4 == 0)
				{
					createItem(*(*iter)); // 몬스터 위치로부터 아이템 생성
				}

				// 꼭 erase 하기 전에 포인터를 먼저 해제해야 한다. 
				// 그래야 주소를 잃어버리지 않고 지울 수 있다. 
				delete (*iter);
				mMonsters.erase(iter);
			}
			return true;
		}
		else
		{
			++iter;
		}
	}
	return false;
}

void PlayStage::crushCheckMonsterPlayer()
{
	Player* player = (Player*)mObjs[0];

	auto iter = mMonsters.begin();
	auto endIter = mMonsters.end();

	while (iter != endIter)
	{
		if (RectangleCrushRactangle(player->getPos(), player->getSize(), (*iter)->getPos(), (*iter)->getSize()))
		{
			player->decreaseHP((*iter)->getHP());

			if (player->isAlive())
			{
				delete (*iter);
				iter = mMonsters.erase(iter);
				endIter = mMonsters.end();
			}
			else
			{
				ChangeStage(eEVENT_TYPE::CHANGE_STAGE, STAGE_MODE::PREV);
				return;
			}
		}
		else
		{
			++iter;
		}
	}
}

void PlayStage::crushCheckItemPlayer()
{
	Player* player = (Player*)mObjs[0];

	auto iter = mItems.begin();
	auto endIter = mItems.end();

	while (iter != endIter)
	{
		if (circleCrushCircle(player->getCenter(), player->getSize() / 2, (*iter)->getCenter(), (*iter)->getSize() / 2))
		{
			player->increaseHP();

			delete (*iter);
			iter = mItems.erase(iter);
			endIter = mItems.end();
		}
		else
		{
			++iter;
		}
	}
}

void PlayStage::createMonster()
{
	float randX = float(rand() % WINDOW.right);
	float randSpeed = (float)(rand() % 500) + 200;
	int hp = rand() % 15 + 5;
	wstring tag(L"enemy");
	tag += to_wstring(rand() % 5 + 1);

	if (mMonsters.empty())
	{
		mMonsters.push_back(new Monster(FPOINT{ randX, 0 }, (Texture*)ResourceManager::getInstance()->findResource(tag.c_str()), randSpeed, mMonsterScale, mMonsterRegenTime, hp));
	}
	else
	{
		if (mMonsters.front()->isValid())
		{
			mMonsters.push_back(new Monster(FPOINT{ randX, 0 }, (Texture*)ResourceManager::getInstance()->findResource(tag.c_str()), randSpeed, mMonsterScale, mMonsterRegenTime, hp));
		}
		else
		{
			Monster* inValidMonster = mMonsters.front();
			mMonsters.pop_front();

			inValidMonster->changePos(FPOINT{ randX, 0 });
			inValidMonster->changeSpeed(randSpeed);
			inValidMonster->changeHP(hp);

			mMonsters.push_back(inValidMonster);
		}
	}
}

void PlayStage::createItem(Monster& monster)
{
	if (mItems.empty())
	{
		mItems.push_back(new Item(FPOINT{ monster.getPos() }, 40, monster.getSpeed(), COLOR{ 200, 0,0 }));
	}
	else
	{
		if (mItems.front()->isValid())
		{
			mItems.push_back(new Item(FPOINT{ monster.getPos() }, 40, monster.getSpeed(), COLOR{ 200, 0,0 }));
		}
		else
		{
			Item* inValidItem = mItems.front();
			mItems.pop_front();

			inValidItem->changePos(monster.getPos());
			inValidItem->changeSpeed(monster.getSpeed());

			mItems.push_back(inValidItem);
		}
	}
}

bool PlayStage::circleCrushCircle(POINT center1, int radius1, POINT center2, int radius2)
{
	int x2 = abs(center1.x - center2.x);
	int y2 = abs(center1.y - center2.y);

	x2 *= x2;
	y2 *= y2;
	int x2y2 = x2 + y2;

	int radius = radius1 + radius2;
	radius *= radius;

	return x2y2 <= radius;
}

bool PlayStage::RectangleCrushRactangle(FPOINT pos1, int size1, FPOINT pos2, int size2)
{
	return	pos1.mX < pos2.mX + size2 &&
		pos1.mX + size1 > pos2.mX &&
		pos1.mY < pos2.mY + size2 &&
		pos1.mY + size1 > pos2.mY;
}
