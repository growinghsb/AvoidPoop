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

// �ش� ���������� ó�� �ö���� �� �ؾ� �� ���� �ϴ� �Լ�
// �ϴ� �⺻������ init �� ȣ���� �־�� �Ѵ�. 
// ���⼭�� init() �� �θ� �� �ִ�.
void PlayStage::enter()
{
	init();
}

void PlayStage::init()
{
	mObjs.push_back(new Player(FPOINT{ (float)WINDOW.right / 2, (float)WINDOW.bottom / 2 }, 50, 200.f, (Texture*)ResourceManager::getInstance()->findResource(L"player3")));

	createMonster();

	for (int i = 0; i < mObjs.size(); ++i)
	{
		mObjs[i]->init();
	}
}

void PlayStage::update()
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

	// ������ �� �÷��̾� �浹üũ
	crushCheckItemPlayer();

	// ���� �� �÷��̾� �浹üũ
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

// �ش� ���������� �����̵�, �����̵�,
// �ٸ� ���������� �ٲ� �� ȣ��Ǵ� �Լ�
// ���⼭ �ش� ���������� ���� ������ �Ѵ�
// �ٽ� ������ �� ���� ������ �ʵ���
void PlayStage::exit()
{
	extern bool gameStart;
	gameStart = false;

	TimeManager::deleteInstance();

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
			// HP �� �� �׾����� üũ, �׾����� �����, �ƴϸ� �״�� ����
			(*iter)->changeHP((*iter)->getHP() - bullet.getOffensePower());

			if ((*iter)->isDie())
			{
				if (rand() % 4 == 0)
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
				StageManager::getInstance()->changePrevStage();
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
