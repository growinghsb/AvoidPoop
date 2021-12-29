#pragma once

#include "CObj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer(wstring tag, FPOINT pos, POINT size, class Texture* texture, float speed);
	virtual ~CPlayer() = default;

	void init() override;
	void update() override;
	void render(HDC backDC) override;
	void collision() override;

private:
	void createBullet();
	void itemCollision();
	void enemyCollision();

	float mSpeed;
	float mSpeedWeight;
	int mMaxHp;
	bool mLaunchMode;
	list<class CBullet*> mBullets;
};

