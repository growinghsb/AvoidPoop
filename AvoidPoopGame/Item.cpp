#include "Item.h"
#include "TimeManager.h"
#include "Core.h"

Item::Item(FPOINT pos, int size, float speed, ITEM_TYPE itemType)
	: Obj(pos, size)
	, mSpeed(speed)
	, mScale(1.f)
	, mItemType(itemType)
{
}

void Item::init()
{
}

void Item::update()
{
	mPos.mY += (mSpeed * DS) * mScale;
}

void Item::render(HDC backDC)
{
	Ellipse(backDC, (int)mPos.mX, (int)mPos.mY, (int)mPos.mX + mSize, (int)mPos.mY + mSize);
}

bool Item::isValid()
{
	return (int)mPos.mY <= WINDOW.bottom;
}
