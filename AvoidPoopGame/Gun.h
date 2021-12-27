#pragma once

#include "Game.h"

// player ������
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
	void setBulletScale();
	
	FPOINT mPos;
	LENGTH mLength;

	list<class Bullet*> mBullets;
	float mBulletSpeed;
	float mBulletScale;
	int mBulletOffensePower;
};

