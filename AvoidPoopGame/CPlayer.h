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
	void bulletLevelUp();

	void increaseHp(int hp)
	{
		mCurrentHp += hp;

		if (mCurrentHp > mMaxHp)
		{
			mCurrentHp = mMaxHp;
		}
	}

	void increaseMp(int mp)
	{
		mCurrentMp += mp;

		if (mCurrentMp > mMaxMp)
		{
			mCurrentMp = mMaxMp;
		}
	}

	void bulletOffencePowerUp(int power)
	{
		mBulletOffencePower += power;

		if (mBulletOffencePower > 10)
		{
			mBulletOffencePower = 10;
		}
	}

	list<class CBullet*>* getBullets()
	{
		return &mBullets;
	}

private:
	void enemyCollision();
	void createBullet();
	void createMissile();
	void changeBulletWeight();
	void changeBulletTexture(class Texture* texture);
	
	bool decreaseMp(const int usage) 
	{
		if (mCurrentMp - usage >= 0) 
		{
			mCurrentMp -= usage;
			return true;
		}
		return false;
	}

	list<class CBullet*> mBullets;
	list<class CBullet*> mMissiles;

	class ObjLayer* mLayer;
	float mSpeed;
	float mSpeedWeight;
	int mCurrentHp;
	int mMaxHp;
	int mCurrentMp;
	int mMaxMp;
	class Texture* mBulletTexture;
	int mBulletCurLevel;
	int mBulletMaxLevel;
	float mBulletSpeedWeight;
	int mBulletOffencePower;
};

