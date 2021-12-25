#pragma once

#include "Game.h"

// player Á¾¼ÓÀû
class Gun
{
public:
	Gun(FPOINT pos, LENGTH length, float bulletSpeed);
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

	void bulletScaleUp();
	void bulletScaleDown();

private:
	FPOINT mPos;
	LENGTH mLength;

	list<class Bullet*> mBullets;
	float mBulletSpeed;
};

