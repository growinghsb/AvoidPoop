#pragma once

#include "CObj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer(wstring tag, FPOINT pos, POINT size, class Texture* texture, class ObjLayer* layer, float speed, list<class CBullet*>& bullets);
	virtual ~CPlayer() = default;

	void init() override;
	void update() override;
	void render(HDC backDC) override;
	void collision() override;

private:
	void createBullet();
	void changeBulletWeight(bool upDown);
	void enemyCollision();

	class ObjLayer* mLayer;
	float mSpeed;
	float mSpeedWeight;
	int mMaxHp;
	bool mLaunchMode;

	list<class CBullet*>& mRefBullets;
	int mBulletOffencePower;
};

