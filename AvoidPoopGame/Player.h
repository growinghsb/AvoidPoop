#pragma once
#include "Obj.h"

class Player :
	public Obj
{
public:
	Player(FPOINT pos, int size, float speed, class Texture* texture);
	~Player();

	void init()				override;
	void update()			override;
	void render(HDC backDC) override;

	void decreaseHP(int offensePower);
	void increaseHP()
	{
		if (mHP + 7 < 100)
		{
			mHP += 7;
		}
		else
		{
			mHP = 100;
		}
	}

	// 생사 확인
	bool isAlive()
	{
		return mHP > 0;
	}

private:
	float mSpeed;
	float mScale;
	bool mLaunchMode; // 속사, 연사 모드 설정 
	class Gun* mGun;
	int mHP;
	COLOR mHPBarColor;
	class Texture* mTexture;
};

