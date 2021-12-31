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
	: mItemList{
	ITEM_LIST::HP,
	ITEM_LIST::MP,
	ITEM_LIST::OFFENCE_POWER,
	ITEM_LIST::BULLET1,
	ITEM_LIST::BULLET2,
	ITEM_LIST::BULLET3,
	ITEM_LIST::MISSILE}
{
}

ObjLayer::~ObjLayer()
{
	// 소멸자에서는 별도의 nullptr 초기화 없이, 
	// 메모리만 지워주면 된다.
	// 모든 오브젝트의 생성과 소멸을 담당한다.

	auto iter = mCObjs.begin();
	auto endIter = mCObjs.end();

	while (iter != endIter)
	{
		delete (*iter);

		iter = mCObjs.erase(iter);
		endIter = mCObjs.end();
	}
}

void ObjLayer::init()
{
	// 이전 스테이지에 이어서 플레이어 텍스처 가져온 뒤 플레이어 생성
	Texture* texture = StageManager::getInstance()->getCurrentPlayerTexture();
	mCObjs.push_back(new CPlayer(L"player", FPOINT{ (float)WINDOW.right / 2, (float)WINDOW.bottom / 2 }, texture->getResolution(), texture, this, 200.0f));

	createEnemy();

	auto iter = mCObjs.begin();
	auto endIter = mCObjs.end();

	while (iter != endIter)
	{
		(*iter)->init();
		++iter;
	}
}

void ObjLayer::update()
{
	static float regen = 0.f;
	regen += DS;

	if (regen > 0.35f)
	{
		createEnemy();
		regen = 0.f;
	}

	auto iter = mCObjs.begin();
	auto endIter = mCObjs.end();

	while (iter != endIter)
	{
		(*iter)->update();
		++iter;
	}

	// 유효하지 않은 오브젝트 삭제
	deleteObject();
}

void ObjLayer::collision()
{
	auto iter = mCObjs.begin();
	auto endIter = mCObjs.end();

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
				iter = mCObjs.erase(iter);
				endIter = mCObjs.end();
			}
		}
		else
		{
			++iter;
		}
	}
}

void ObjLayer::render(HDC backDC)
{
	auto iter = mCObjs.begin();
	auto endIter = mCObjs.end();

	while (iter != endIter)
	{
		(*iter)->render(backDC);
		++iter;
	}
}

void ObjLayer::createItem(FPOINT pos)
{
	ITEM_LIST item = mItemList[rand() % (UINT)ITEM_LIST::END];
	Texture* texture = itemChoice(item);

	int validTime = rand() % 20 + 10;

	mCObjs.push_back(new CItem(L"item", pos, texture->getResolution(), texture, this, validTime, item));
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

	case ITEM_LIST::BULLET1:
		texture = FIND_TEXTURE(L"bullet1");
		break;

	case ITEM_LIST::BULLET2:
		texture = FIND_TEXTURE(L"bullet2");
		break;

	case ITEM_LIST::BULLET3:
		texture = FIND_TEXTURE(L"bullet3");
		break;

	case ITEM_LIST::MISSILE:
		texture = FIND_TEXTURE(L"missileCountUp");
		break;

	default:
		texture = getTexture(L"HPPotion", 1);
		break;
	}
	return texture;
}

void ObjLayer::createEnemy()
{
	Texture* texture = getTexture(L"enemy", 5);
	POINT size = texture->getResolution();
	float x = float(rand() % (WINDOW.right - size.x));
	float speed = float((rand() % 300) + 200);
	int	  hp = rand() % 15 + 10;

	mCObjs.push_back(new CEnemy(L"enemy", FPOINT{ x, 0 }, size, texture, this, speed, hp));
}

Texture* ObjLayer::getTexture(const wchar_t* tag, int range)
{
	wstring wstag(tag);
	wstag += to_wstring(rand() % range + 1);
	return FIND_TEXTURE(wstag.c_str());
}

void ObjLayer::deleteObject()
{
	auto iter = mCObjs.begin();
	auto endIter = mCObjs.end();

	while (iter != endIter)
	{
		if ((*iter)->getPos().mY - 10 > WINDOW.bottom)
		{
			delete (*iter);
			iter = mCObjs.erase(iter);
			endIter = mCObjs.end();
		}
		else if ((*iter)->getTag() == L"item")
		{
			CItem* item = (CItem*)(*iter);

			if (!item->isValidTime())
			{
				delete (*iter);
				iter = mCObjs.erase(iter);
				endIter = mCObjs.end();
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