#include "Monster.h"
#include "Core.h"
#include "TimeManager.h"

Monster::Monster(FPOINT pos, int size, float speed, float scale)
	: Obj(pos, size)
	, mSpeed(speed)
	, mScale(scale)
{
}

void Monster::init()
{
}

void Monster::update()
{
	mPos.mY += (mSpeed * DS) * mScale;
}

void Monster::render(HDC backDC)
{
	Ellipse(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mSize, (int)mPos.mY + mSize);
}

bool Monster::isValid()
{
	return (int)mPos.mY <= WINDOW.bottom;
}

