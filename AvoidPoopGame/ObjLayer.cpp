#include "ObjLayer.h"
#include "CObj.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Core.h"
#include "ResourceManager.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "StageManager.h"
#include "CItem.h" // 메모리 해제시에도 인클루드가 필요하다.
#include "CBullet.h"

ObjLayer::ObjLayer()
	: mLists{}
	, mItemList{
	ITEM_LIST::HP,
	ITEM_LIST::MP,
	ITEM_LIST::OFFENCE_POWER,
	ITEM_LIST::BULLET_UP }
{
}

ObjLayer::~ObjLayer()
{
	// 소멸자에서는 별도의 nullptr 초기화 없이, 
	// 메모리만 지워주면 된다.
	// 모든 오브젝트의 생성과 소멸을 담당한다.

	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		auto iter = mLists[i].begin();
		auto endIter = mLists[i].end();

		while (iter != endIter)
		{
			delete (*iter);
			iter = mLists[i].erase(iter);
			endIter = mLists[i].end();
		}
	}
}

void ObjLayer::init()
{
	// 이전 스테이지에 이어서 플레이어 텍스처 가져온 뒤 플레이어 생성
	Texture* texture = StageManager::getInstance()->getCurrentPlayerTexture();
	mLists[(UINT)OBJ_TYPE::PLAYER].push_back(new CPlayer(L"player", FPOINT{ (float)WINDOW.right / 2, (float)WINDOW.bottom / 2 }, texture->getResolution(), texture, this, 200.0f));

	createObstacle();

	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		auto iter = mLists[i].begin();
		auto endIter = mLists[i].end();

		while (iter != endIter)
		{
			(*iter)->init();
			++iter;
		}
	}
}

void ObjLayer::update()
{
	static float obstacleRegen = 0.f;
	obstacleRegen += DS;

	if (obstacleRegen > 0.35f)
	{
		createObstacle();
		obstacleRegen = 0.f;
	}

	static float enemyRegen = 0.f;
	enemyRegen += DS;

	if (enemyRegen > 10 && mLists[(UINT)OBJ_TYPE::ENEMY].size() < 3)
	{
		createEnemy();
		enemyRegen = 0.f;
	}

	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		auto iter = mLists[i].begin();
		auto endIter = mLists[i].end();

		while (iter != endIter)
		{
			(*iter)->update();
			++iter;
		}
	}

	// 유효하지 않은 오브젝트 삭제
	deleteObject();
}

void ObjLayer::collision()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		auto iter = mLists[i].begin();
		auto endIter = mLists[i].end();

		while (iter != endIter)
		{
			if ((*iter)->collision())
			{
				if ((*iter)->getTag() == L"player")
				{
					// 플레이어의 경우 플레이어가 죽으면 true 반환
					// 바로 인트로 화면으로 이동한다. 
					StageManager::getInstance()->changeIntroStage();
					return;
				}

				if ((*iter)->getTag() == L"item")
				{
					// 충돌 났는데 아이템이면 여기서 아이템 삭제
					delete (*iter);
					iter = mLists[i].erase(iter);
					endIter = mLists[i].end();
				}
			}
			else
			{
				++iter;
			}
		}
	}
}

void ObjLayer::render(HDC backDC)
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		auto iter = mLists[i].begin();
		auto endIter = mLists[i].end();

		while (iter != endIter)
		{
			(*iter)->render(backDC);
			++iter;
		}
	}
}

void ObjLayer::createItem(FPOINT pos)
{
	ITEM_LIST item = mItemList[rand() % (UINT)ITEM_LIST::END];
	Texture* texture = itemChoice(item);

	int validTime = rand() % 10 + 5;

	mLists[(UINT)OBJ_TYPE::ITEM].push_back(new CItem(L"item", pos, texture->getResolution(), texture, this, validTime, item));
}

Texture* ObjLayer::itemChoice(ITEM_LIST item)
{
	Texture* texture;

	switch (item)
	{
	case ITEM_LIST::HP:
		texture = getTexture(L"HPPotion", 1);
		break;

	case ITEM_LIST::MP:
		texture = getTexture(L"MPPotion", 1);
		break;

	case ITEM_LIST::OFFENCE_POWER:
		texture = getTexture(L"bulletPowerPotion", 1);
		break;

	case ITEM_LIST::BULLET_UP:
		texture = FIND_TEXTURE(L"missileCountUp");
		break;

	default:
		texture = getTexture(L"HPPotion", 1);
		break;
	}
	return texture;
}

Texture* ObjLayer::getTexture(const wchar_t* tag, int range)
{
	wstring wstag(tag);
	wstag += to_wstring(rand() % range + 1);
	return FIND_TEXTURE(wstag.c_str());
}

void ObjLayer::createObstacle()
{
	Texture* texture = getTexture(L"obstacle", 5);
	POINT size = texture->getResolution();
	float x = float(rand() % (WINDOW.right - size.x));
	float speed = float((rand() % 300) + 200);
	int	  hp = rand() % 15 + 10;

	mLists[(UINT)OBJ_TYPE::OBSTACLE].push_back(new CEnemy(L"obstacle", FPOINT{ x, 0 }, size, texture, this, speed, hp));
}

void ObjLayer::createEnemy()
{
	Texture* texture = getTexture(L"enemy", 5);
	POINT size = texture->getResolution();
	float x = float(rand() % (WINDOW.right - size.x));
	float y = float(rand() % 100 + 50);
	float speed = 0.f;
	int	  hp = rand() % 51 + 50;

	mLists[(UINT)OBJ_TYPE::ENEMY].push_back(new CEnemy(L"enemy", FPOINT{ x, y }, size, texture, this, speed, hp));
}

void ObjLayer::deleteObject()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; ++i)
	{
		auto iter = mLists[i].begin();
		auto endIter = mLists[i].end();

		while (iter != endIter)
		{
			if ((*iter)->getPos().mY > WINDOW.bottom)
			{
				delete (*iter);
				iter = mLists[i].erase(iter);
				endIter = mLists[i].end();
			}
			else if ((*iter)->getTag() == L"item")
			{
				CItem* item = (CItem*)(*iter);

				if (!item->isValidTime())
				{
					delete (*iter);
					iter = mLists[i].erase(iter);
					endIter = mLists[i].end();
				}
				else
				{
					++iter;
				}
			}
			else
			{
				++iter;
			}
		}
	}
}