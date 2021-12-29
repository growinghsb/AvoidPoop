#include "CBullet.h"
#include "CObj.h"
#include "TimeManager.h"
#include "Texture.h"

CBullet::CBullet(wstring tag, FPOINT pos, POINT size, Texture* texture, ObjLayer* layer)
	: CObj(tag, pos, size, texture)
	, mLayer(layer)
	, mSpeed(350.0f)
	, mSpeedWeigth(1.0f)
{
}

void CBullet::init()
{
}

void CBullet::update()
{
	mPos.mY -= (mSpeed * DS) * mSpeedWeigth;
}

void CBullet::render(HDC backDC)
{
	POINT tRes = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, tRes.x, tRes.y, mTexture->getTextureDC(), 0, 0, tRes.x, tRes.y, COLOR_GREEN);
}

void CBullet::collision()
{
}
