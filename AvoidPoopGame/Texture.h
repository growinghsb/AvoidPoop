#pragma once

#include "CResource.h"

class Texture :
	public CResource
{
public:
	Texture(wstring tag);
	~Texture();

	bool load() override;

	HBITMAP getTextureBitmap() const
	{
		return mTextureBitmap;
	}

	HDC getTextureDC() const 
	{
		return mTextureDC;
	}

	POINT getResolution() const 
	{
		return mResolution;
	}

private:
	HBITMAP mTextureBitmap;
	HDC mTextureDC;
	POINT mResolution;
};

