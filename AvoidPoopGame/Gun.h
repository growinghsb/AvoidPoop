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
	void bulletScaleUp();
	void bulletScaleDown();

	LENGTH getLength() const
	{
		return mLength;
	}

	bool isTop() const
	{
		return (int)mPos.mY <= 0;
	}

	void changeBulletSize(int size) 
	{
		if(size > mBulletSize)
		{
			mBulletSize = size;
			setBulletSize();
		}
	}

	int getBulletSize() const
	{
		return mBulletSize;
	}

	void changeBulletOffensePower() 
	{
		if (mBulletOffensePower + 2 < 10)
		{
			mBulletOffensePower += 2;
		}
		else 
		{
			mBulletOffensePower = 10;
		}
		setBulletOffensePower();
	}

private:
	void setBulletScale();
	void setBulletSize();
	void setBulletOffensePower();
	
	FPOINT mPos;
	LENGTH mLength;

	list<class Bullet*> mBullets;
	float mBulletSpeed;
	float mBulletScale;
	int mBulletOffensePower;
	int mBulletSize;
	COLOR mBulletColor;
};

