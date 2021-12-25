#include "Gun.h"
#include "Bullet.h"

Gun::Gun(FPOINT pos, LENGTH length, float bulletSpeed)
	: mPos(pos)
	, mLength(length)
	, mBulletSpeed(bulletSpeed)
{
}

Gun::~Gun()
{
	int size = (int)mBullets.size();
	for (int i = 0; i < size; ++i)
	{
		delete mBullets.front();
		mBullets.pop_front();
	}
}

void Gun::update(FPOINT pos, LENGTH length)
{
	mPos = pos;
	mLength = length;
}

void Gun::render(HDC backDC)
{
	Rectangle(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mLength.mWidth, mLength.mVertical);

	list<Bullet*>::iterator iter = mBullets.begin();
	list<Bullet*>::iterator endIter = mBullets.end();

	for (; iter != endIter; ++iter)
	{
		(*iter)->update();
		(*iter)->render(backDC);
	}
}

void Gun::createBullet()
{
	if (mBullets.empty())
	{
		mBullets.push_back(new Bullet(FPOINT{ mPos.mX, mPos.mY - (float)mLength.mWidth }, mLength.mWidth, mBulletSpeed));
	}
	else
	{
		if (mBullets.front()->isValid())
		{
			mBullets.push_back(new Bullet(FPOINT{ mPos.mX, mPos.mY - (float)mLength.mWidth }, mLength.mWidth, mBulletSpeed));
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
	list<Bullet*>::iterator iter = mBullets.begin();
	list<Bullet*>::iterator endIter = mBullets.end();

	for (; iter != endIter; ++iter)
	{
		(*iter)->scaleUp();
	}
}

void Gun::bulletScaleDown()
{
	list<Bullet*>::iterator iter = mBullets.begin();
	list<Bullet*>::iterator endIter = mBullets.end();

	for (; iter != endIter; ++iter)
	{
		(*iter)->scaleDown();
	}
}
