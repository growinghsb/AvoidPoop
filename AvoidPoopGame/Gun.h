#pragma once

#include "Game.h"

// player Á¾¼ÓÀû
class Gun
{
public:
	Gun(FPOINT pos, LENGTH length);
	~Gun();

	void update(FPOINT pos, LENGTH length);
	void render(HDC backDC);
	void createBullet();

	LENGTH getLength()
	{
		return mLength;
	}

	bool isTop() 
	{
		return (int)mPos.mY <= 0;
	}

private:
	FPOINT mPos;
	LENGTH mLength;

	list<class Bullet*> mBullets;
};

