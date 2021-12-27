#include "Gun.h"
#include "Bullet.h"
#include "Stage.h"

Gun::Gun(FPOINT pos, LENGTH length, float bulletSpeed)
	: mPos(pos)
	, mLength(length)
	, mBulletSpeed(bulletSpeed)
	, mBulletScale(1.f)
	, mBulletOffensePower(3)
{
}

Gun::~Gun()
{
	auto iter = mBullets.begin();
	auto endIter = mBullets.end(); 

	while (iter != endIter) 
	{
		delete (*iter);
		iter = mBullets.erase(iter);
		endIter = mBullets.end();
	}
}

void Gun::update(FPOINT pos, LENGTH length)
{
	mPos = pos;
	mLength = length;

	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	while (iter != endIter) 
	{
		(*iter)->update();

		// 총알 하나에 대해서 몬스터와의 충돌체크
		if (Stage::getInstance()->CrushMonsterRemove(*(*iter)))
		{
			// 몬스터와 충돌 됐으므로 총알 지우기
			delete (*iter);
			iter = mBullets.erase(iter);
			endIter = mBullets.end();
		}
		else
		{
			// 충돌 안됨
			++iter;
		}
	}
}

void Gun::render(HDC backDC)
{
	Rectangle(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mLength.mWidth, mLength.mVertical);
	
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	SelectObject(backDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(backDC, RGB(0, 255, 0));
	for (; iter != endIter; ++iter)
	{
		(*iter)->render(backDC);
	}
	SetDCBrushColor(backDC, RGB(0, 0, 0));
}

void Gun::createBullet()
{
	if (mBullets.empty())
	{
		mBullets.push_back(new Bullet(FPOINT{ mPos.mX, mPos.mY - (float)mLength.mWidth }, mLength.mWidth, mBulletSpeed, mBulletScale, mBulletOffensePower));
	}
	else
	{
		if (mBullets.front()->isValid())
		{
			mBullets.push_back(new Bullet(FPOINT{ mPos.mX, mPos.mY - (float)mLength.mWidth }, mLength.mWidth, mBulletSpeed, mBulletScale, mBulletOffensePower));
		}
		else
		{
			Bullet* invalidBullet = mBullets.front();
			mBullets.pop_front();

			invalidBullet->changePos(FPOINT{ mPos.mX, mPos.mY - (float)mLength.mWidth });
			mBullets.push_back(invalidBullet);
		}
	}
}

void Gun::bulletScaleUp()
{
	if ((int)mBulletScale < 2)
	{
		mBulletScale += 0.1f;
	}
	else
	{
		mBulletScale = 1.9f;
	}
	setBulletScale();
}

void Gun::bulletScaleDown()
{
	if ((int)mBulletScale >= 1)
	{
		mBulletScale -= 0.1f;
	}
	else
	{
		mBulletScale = 1.0f;
	}
	setBulletScale();
}

void Gun::setBulletScale()
{
	auto iter = mBullets.begin();
	auto endIter = mBullets.end();

	for (; iter != endIter; ++iter)
	{
		(*iter)->setScale(mBulletScale);
	}
}
