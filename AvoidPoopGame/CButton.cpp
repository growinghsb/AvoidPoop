#include "CButton.h"
#include "Texture.h"

CButton::CButton(FPOINT pos, int size, Texture* texture)
	: Obj(pos, size, "button")
	, mTexture(texture)
{
}

void CButton::init()
{
}

void CButton::update()
{

}

void CButton::render(HDC backDC)
{
	POINT resolution = mTexture->getResolution();
	TransparentBlt(backDC, (int)mPos.mX, (int)mPos.mY, resolution.x, resolution.y, mTexture->getTextureDC(), 0, 0, resolution.x, resolution.y, COLOR_WHITE);
}
