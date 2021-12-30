#include "CBullet.h"
#include "CObj.h"
#include "TimeManager.h"
#include "Texture.h"

CBullet::CBullet(wstring tag, FPOINT pos, POINT size, Texture* texture, ObjLayer* layer)
	: CObj(tag, pos, size, texture)
	, mLayer(layer)
	, mSpeed(350.0f)
	, mSpeedWeight(1.0f)
{
}

void CBullet::init()
{
}

void CBullet::update()
{
	mPos.mY -= (mSpeed * DS) * mSpeedWeight;
}

void CBullet::render(HDC backDC)
{
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, mSize.x, mSize.y, mTexture->getTextureDC(), 0, 0, mSize.x, mSize.y, COLOR_WHITE);
}

void CBullet::collision()
{
}
