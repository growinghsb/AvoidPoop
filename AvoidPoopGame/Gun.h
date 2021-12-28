#pragma once

#include "Game.h"

// player ������
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

private:
	void setBulletScale();

	class Player* mPlayer;
	list<class Bullet*> mBullets;
	float mBulletSpeed;
	float mBulletScale;
	int mBulletOffensePower;
	int mBulletSize;
	COLOR mBulletColor;
};

