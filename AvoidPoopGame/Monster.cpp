#include "Monster.h"
#include "Core.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Texture.h"

Monster::Monster(FPOINT pos, Texture* texture,  float speed, float scale, float regenTime, int hp)
	: Obj(pos, texture->getResolution().x, "monster")
	, mTexture(texture)
	, mSpeed(speed)
	, mScale(scale)
	, mRegenTime(regenTime)
	, mHP(hp)
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

	int hpBarY = (int)mPos.mY - 15;
	SetDCBrushColor(backDC, RGB(mHPBarColor.r, mHPBarColor.g, mHPBarColor.b)); // 빨간색
	Rectangle(backDC, (int)mPos.mX, hpBarY, (int)mPos.mX + mHP, hpBarY + 5); // Hp Bar
	
	SetDCBrushColor(backDC, COLOR_WHITE); // 다시 흰색으로 변경

	// monster
	BitBlt(backDC, (int)mPos.mX, (int)mPos.mY, mTexture->getResolution().x, mTexture->getResolution().y, mTexture->getTextureDC(), 0, 0, SRCCOPY);
}

bool Monster::isValid()
{
	return (int)mPos.mY <= WINDOW.bottom;
}

