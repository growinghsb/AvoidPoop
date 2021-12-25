#pragma once

#include "Game.h"

class Obj
{
public:
	virtual ~Obj() = default;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render(HDC backDC) = 0;

	virtual FPOINT getPos() const
	{
		return mPos;
	}

	virtual int getSize() const
	{
		return mSize;
	}

	virtual void changePos(FPOINT pos)
	{
		mPos = pos;
	}

	virtual void changeSize(int size)
	{
		mSize = size;
	}

	virtual POINT getCenter()
	{
		int halfSize = mSize / 2;
		return POINT{ (long)mPos.mX + halfSize, (long)mPos.mY + halfSize };
	}

protected:
	Obj(FPOINT pos, int size);

	FPOINT mPos;
	int mSize;
};

