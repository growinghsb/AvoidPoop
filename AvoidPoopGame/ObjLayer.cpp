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
	// 이전 스테이지에 이어서 플레이어 텍스처 가져온 뒤 플레이어 생성
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

	// 불릿에 대한 update 및 render 는
	// 각각 플레이어쪽에서 처리

	// 유효하지 않은 오브젝트 삭제
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
