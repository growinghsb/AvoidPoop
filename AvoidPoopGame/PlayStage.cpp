#include "PlayStage.h"
#include "Core.h"
#include "Player.h"
#include "TimeManager.h"
#include "Monster.h"
#include "Item.h"
#include "Bullet.h"
#include "StageManager.h"

PlayStage::PlayStage(int order)
	: Stage(order)
	, mMonsterScale(1.f)
	, mMonsterRegenTime(0.4f)
	, mItemTypes{ ITEM_TYPE::BULLTE_SIZE_UP,
				ITEM_TYPE::OFFENCE_POWER_UP }
	, mItemColors{ COLOR{238, 247, 106}, COLOR{255, 264, 238} }
{
	mObjs.reserve(128);
}

PlayStage::~PlayStage()
{
	stageClear();
}

// �ش� ���������� ó�� �ö���� �� �ؾ� �� ���� �ϴ� �Լ�
// �ϴ� �⺻������ init �� ȣ���� �־�� �Ѵ�. 
// ���⼭�ۿ� init() �� �θ� �� �ִ�. ����.
void PlayStage::enter()
{
	init();
}

void PlayStage::init()
{
	mObjs.push_back(new Player(FPOINT{ (float)WINDOW.right / 2, (float)WINDOW.bottom / 2 }, 50, 200.f));

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

	// ���⼭ ���� �� �÷��̾� �浹üũ
	crushCheckWithPlayer();

	// item
	auto itemIter = mItems.begin();
	auto itemEndIter = mItems.end();

	while (itemIter != itemEndIter)
	{
		(*itemIter)->update();
		++itemIter;
	}
}

void PlayStage::render(HDC backDC)
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

void PlayStage::crushCheckWithPlayer()
{
	Player* player = (Player*)mObjs[0]; // ������ 0���� ������ player �̴�. 

	auto monsterIter = mMonsters.begin();
	auto monsterEndIter = mMonsters.end();

	int x2 = 0;
	int y2 = 0;
	int x2y2 = 0;
	int radius = 0;

	int monsterX = 0;
	int monsterY = 0;

	while (monsterIter != monsterEndIter)
	{
		if (player->isOverlapY((*monsterIter)->getPos().mY + (*monsterIter)->getSize()))
		{
			// ���� ������
			radius = (*monsterIter)->getSize() / 2;
			radius *= radius;

			monsterX = (*monsterIter)->getCenter().x;
			monsterY = (*monsterIter)->getCenter().y;

			// �簢���� �������� ���� ������ �Ÿ�
			x2 = abs((int)player->getPos().mX - monsterX);
			y2 = abs((int)player->getPos().mY - monsterY);

			x2 *= x2;
			y2 *= y2;
			x2y2 = x2 + y2;

			if (x2y2 <= radius)
			{
				player->decreaseHP((*monsterIter)->getHP());
				
				if (player->isAlive()) 
				{
					delete (*monsterIter);

					monsterIter = mMonsters.erase(monsterIter);
					monsterEndIter = mMonsters.end();

					continue;
				}
				else 
				{
					StageManager::getInstance()->changePrevStage();
					return;
				}
			}

			// �簢���� �ٸ��� �������� ���� ������ �Ÿ�
			x2 = abs((int)player->getPos().mX + player->getSize() - monsterX);
			y2 = abs((int)player->getPos().mY + player->getSize() - monsterY);

			x2 *= x2;
			y2 *= y2;
			x2y2 = x2 + y2;

			if (x2y2 <= radius)
			{
				if (player->isAlive())
				{
					delete (*monsterIter);

					monsterIter = mMonsters.erase(monsterIter);
					monsterEndIter = mMonsters.end();

					continue;
				}
				else
				{
					StageManager::getInstance()->changePrevStage();
					return;
				}
			}
			++monsterIter;
		}
		else
		{
			++monsterIter;
		}
	}
}

void PlayStage::createMonster()
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

void PlayStage::createItem(Monster& monster)
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