#include "Texture.h"
#include "ResourceManager.h"
#include "Core.h"

Texture::Texture(wstring tag)
	: CResource(tag)
	, mTextureBitmap(nullptr)
	, mTextureDC(nullptr)
	, mResolution{}
{
	mTextureDC = CreateCompatibleDC(Core::getInstance()->getDC());
}

Texture::~Texture()
{ 
	DeleteObject(mTextureBitmap);
	DeleteDC(mTextureDC);
}

bool Texture::load()
{
	wstring path = ResourceManager::getInstance()->getAbsolutePullpath();
	path += L"\\" + mResourceTag + L".bmp";

	mTextureBitmap = (HBITMAP)LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	if (nullptr == mTextureBitmap) 
	{
		return false;
	}

	BITMAP bitmapInfo;
	GetObject(mTextureBitmap, sizeof(BITMAP), &bitmapInfo);

	mResolution.x = bitmapInfo.bmWidth;
	mResolution.y = bitmapInfo.bmHeight;

	HBITMAP oldBitmap = (HBITMAP)SelectObject(mTextureDC, mTextureBitmap);
	DeleteObject(oldBitmap);

	return true;
}
