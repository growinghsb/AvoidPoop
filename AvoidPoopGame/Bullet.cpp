#include "Bullet.h"
#include "TimeManager.h"

Bullet::Bullet(FPOINT pos, int size)
	: Obj(pos, size)
	, mSpeed(400.f)
{
}

void Bullet::init()
{
}

void Bullet::update()
{
	mPos.mY -= mSpeed * DS;
}

void Bullet::render(HDC backDC)
{
	Ellipse(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mSize, (int)mPos.mY + mSize);
}
