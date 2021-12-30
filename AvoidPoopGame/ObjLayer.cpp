#include "ObjLayer.h"
#include "CObj.h"
#include "TimeManager.h"
#include "Texture.h"
#include "Core.h"
#include "ResourceManager.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "StageManager.h"
#include "CItem.h" // �޸� �����ÿ��� ��Ŭ��尡 �ʿ��ϴ�.
#include "CBullet.h"

ObjLayer::ObjLayer()
	: mItemList{ ITEM_LIST::HP, ITEM_LIST::MP, ITEM_LIST::OFFENCE_POWER }
{
}

ObjLayer::~ObjLayer()
{
	// �Ҹ��ڿ����� ������ nullptr �ʱ�ȭ ����, 
	// �޸𸮸� �����ָ� �ȴ�.
	// ��� ������Ʈ�� ������ �Ҹ��� ����Ѵ�.

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
	// ���� ���������� �̾ �÷��̾� �ؽ�ó ������ �� �÷��̾� ����
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

	// ��ȿ���� ���� ������Ʈ ����
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
				// �÷��̾��� ��� �÷��̾ ������ true ��ȯ
				// �ٷ� ��Ʈ�� ȭ������ �̵��Ѵ�. 
				StageManager::getInstance()->changeIntroStage();
				return;
			}
			else if ((*iter)->getTag() == L"item")
			{
				// �浹 ���µ� �������̸� ���⼭ ������ ����
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
	Texture* texture = (Texture*)ResourceManager::getInstance()->findResource(L"HPPotion1");
	int validTime = rand() % 20 + 10;
	int itemCategory = 0; // rand() % (UINT)ITEM_LIST::END;  

	mCObjs.push_back(new CItem(L"item", pos, texture->getResolution(), texture, this, validTime, mItemList[itemCategory]));
}

void ObjLayer::createEnemy()
{
	Texture* texture = getTexture(L"enemy");
	POINT size = texture->getResolution();
	float x = float(rand() % (WINDOW.right - size.x));
	float speed = float((rand() % 300) + 200);
	int	  hp = rand() % 15 + 5;

	mCObjs.push_back(new CEnemy(L"enemy", FPOINT{ x, 0 }, size, texture, this, speed, hp));
}

Texture* ObjLayer::getTexture(const wchar_t* tag)
{
	wstring wstag(tag);
	wstag += to_wstring(rand() % 5 + 1);
	return (Texture*)ResourceManager::getInstance()->findResource(wstag.c_str());
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