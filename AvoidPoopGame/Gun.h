#pragma once

#include "Game.h"

// player Á¾¼ÓÀû
class Gun
{
public:
	Gun(class Player* player, float bulletSpeed);
	~Gun();

	void update();
	void render(HDC backDC);
	void createBullet();
	void bulletScaleUp();
	void bulletScaleDown();

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

	class Player* mPlayer;

	list<class Bullet*> mBullets;
	float mBulletSpeed;
	float mBulletScale;
	int mBulletOffensePower;
	int mBulletSize;
	COLOR mBulletColor;
};

