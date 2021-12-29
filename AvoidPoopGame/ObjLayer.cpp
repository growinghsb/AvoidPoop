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

	auto bulletIter = mBullets.begin();
	auto bulletEndIter = mBullets.end();

	while (bulletIter != bulletEndIter)
	{
		delete (*bulletIter);

		bulletIter = mBullets.erase(bulletIter);
		bulletEndIter = mBullets.end();
	}
}

void ObjLayer::init()
{
	// ���� ���������� �̾ �÷��̾� �ؽ�ó ������ �� �÷��̾� ����
	Texture* texture = StageManager::getInstance()->getCurrentPlayerTexture();
	mCObjs.push_back(new CPlayer(L"player", FPOINT{ (float)WINDOW.right / 2, (float)WINDOW.bottom / 2 }, texture->getResolution(), texture, this, 250.0f, mBullets));

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
		regen -= 0.35f;
		createEnemy();
	}

	auto iter = mCObjs.begin();
	auto endIter = mCObjs.end();

	while (iter != endIter)
	{
		(*iter)->update();
		++iter;
	}

	// �Ҹ��� ���� update �� render ��
	// ���� �÷��̾��ʿ��� ó��

	// ��ȿ���� ���� ������Ʈ ����
	deleteObject();
}

void ObjLayer::collision()
{
	auto iter = mCObjs.begin();
	auto endIter = mCObjs.end();

	while (iter != endIter)
	{
		(*iter)->collision();
		++iter;
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
		else
		{
			++iter;
		}
	}
}
