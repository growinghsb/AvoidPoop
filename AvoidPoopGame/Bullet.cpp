#include "Bullet.h"
#include "TimeManager.h"

Bullet::Bullet(FPOINT pos, int size, float speed, float scale, int offensePower)
	: Obj(pos, size)
	, mSpeed(speed)
	, mScale(scale)
	, mOffensePower(offensePower)
{
}

void Bullet::init()
{
}

void Bullet::update()
{
	mPos.mY -= (mSpeed * DS) * mScale;
}

void Bullet::render(HDC backDC)
{
	Ellipse(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mSize, (int)mPos.mY + mSize);
}
