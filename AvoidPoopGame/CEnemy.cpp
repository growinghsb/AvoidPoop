#include "CEnemy.h"
#include "CBullet.h"
#include "Texture.h"
#include "TimeManager.h"

CEnemy::CEnemy(wstring tag, FPOINT pos, POINT size, Texture* texture, ObjLayer* layer, float speed, int maxHp)
	: CObj(tag, pos, size, texture)
	, mLayer(layer)
	, mSpeed(speed)
	, mSpeedWeight(1.0f)
	, mMaxHp(maxHp)
{
}

void CEnemy::init()
{
}

void CEnemy::update()
{
	mPos.mY += (mSpeed * DS) * mSpeedWeight;
}

void CEnemy::render(HDC backDC)
{
	SelectObject(backDC, GetStockObject(DC_BRUSH));

	int hpBarY = (int)mPos.mY - 15;
	SetDCBrushColor(backDC, COLOR_RED); // 빨간색
	Rectangle(backDC, (int)mPos.mX, hpBarY, (int)mPos.mX + mMaxHp, hpBarY + 5); // Hp Bar

	SetDCBrushColor(backDC, COLOR_WHITE); // 다시 흰색으로 변경

	POINT res = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, res.x, res.y, mTexture->getTextureDC(), 0, 0, res.x, res.y, COLOR_WHITE);
}

void CEnemy::collision()
{
	bulletCollision();
}

void CEnemy::bulletCollision()
{
}
