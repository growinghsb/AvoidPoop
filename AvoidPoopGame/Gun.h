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

private:
	FPOINT mPos;
	LENGTH mLength;

	list<class Bullet*> mBullets;
};

