#include "Monster.h"
#include "Core.h"
#include "TimeManager.h"

Monster::Monster(FPOINT pos, int size, float speed, float scale, float regenTime, int hp)
	: Obj(pos, size, "monster")
	, mSpeed(speed)
	, mScale(scale)
	, mRegenTime(regenTime)
	, mHP(hp)
	, mBodyColor{ 115 , 22, 161 }
	, mHPBarColor{ 200, 0, 0 }
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
	SelectObject(backDC, GetStockObject(DC_BRUSH));

	SetDCBrushColor(backDC, RGB(mBodyColor.r, mBodyColor.g, mBodyColor.b)); // ���� �����
	Ellipse(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mSize, (int)mPos.mY + mSize); // monster

	int hpBarY = (int)mPos.mY - 15;
	SetDCBrushColor(backDC, RGB(mHPBarColor.r, mHPBarColor.g, mHPBarColor.b)); // ������
	Rectangle(backDC, (int)mPos.mX, hpBarY, (int)mPos.mX + (mHP * 10), hpBarY + 5); // Hp Bar
}

bool Monster::isValid()
{
	return (int)mPos.mY <= WINDOW.bottom;
}

