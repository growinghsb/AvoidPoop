#pragma once

#include "Game.h"

class CObj
{
public:
	CObj(wstring tag, FPOINT pos, POINT size, class Texture* texture);
	virtual ~CObj() = default;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render(HDC backDC) = 0;
	virtual void collision() = 0;

	const wstring& getTag() const;
	FPOINT getPos() const;
	POINT getSize() const;
	const class Texture& getTexture() const;

	void changeTag(const wchar_t* tag) 
	{
		mTag = tag;
	}

	void changePos(const FPOINT pos)
	{
		mPos = pos;
	}

	void changeSize(const POINT size)
	{
		mSize = size;
	}

	void changeTexture(class Texture* const texture)
	{
		mTexture = texture;
	}

protected:
	wstring mTag;
	FPOINT mPos;
	POINT mSize;
	class Texture* mTexture;
};

