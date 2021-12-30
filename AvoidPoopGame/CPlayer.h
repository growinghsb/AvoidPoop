#pragma once

#include "CObj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer(wstring tag, FPOINT pos, POINT size, class Texture* texture, class ObjLayer* layer, float speed);
	virtual ~CPlayer();

	void init() override;
	void update() override;
	void render(HDC backDC) override;
	bool collision() override;

private:
	void enemyCollision();
	void createBullet();
	void changeBulletWeight();

	list<class CBullet*> mBullets;

	class ObjLayer* mLayer;
	float mSpeed;
	float mSpeedWeight;
	int mMaxHp;
	bool mLaunchMode;
	float mBulletSpeedWeight;
	int mBulletOffencePower;
};

