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

	int getSize() const
	{
		return mSize;
	}

	void changePos(FPOINT pos)
	{
		mPos = pos;
	}

	void changeSize(int size)
	{
		mSize = size;
	}

	POINT getCenter() const 
	{
		int halfSize = mSize / 2;
		return POINT{ (long)mPos.mX + halfSize, (long)mPos.mY + halfSize };
	}

	// �簢�� �� �簢�� �浹 �� ���
	bool isOverlapX(float x) const
	{
		if (x <= mPos.mX + mSize || x >= mPos.mX)
		{
			return true;
		}
		return false;
	}

	// �簢�� �� �簢�� �浹 �� ���
	bool isOverlapY(float y) const
	{
		return y >= mPos.mY;
	}

	string getTag() const
	{
		return mObjTag;
	}
	

protected:
	Obj(FPOINT pos, int size, string objTag);

	FPOINT mPos;
	int mSize;
	string mObjTag;
};

