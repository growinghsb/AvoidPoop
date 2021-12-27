#pragma once
#include "Obj.h"

class Player :
	public Obj
{
public:
	Player();
	Player(FPOINT pos, int size, float speed);
	~Player();

	void init()				override;
	void update()			override;
	void render(HDC backDC) override;

	void decreaseHP(int offensePower)
	{
		mHP -= offensePower;
		
		// 추후 함수로 플레이어 생사 확인 후 죽었으면 Stage 다시 시작
		if (mHP <= 0) 
		{
			mHP = 100;
		}
	}

	// 사각형 대 사각형 충돌 시 사용
	bool isOverlapX(float x) 
	{
		if (x <= mPos.mX + mSize || x >= mPos.mX)
		{
			return true;
		}
		return false;
	}

	// 사각형 대 사각형 충돌 시 사용
	bool isOverlapY(float y) 
	{
		return y >= mPos.mY;
	}

private:
	float mSpeed;
	float mScale;
	bool mLaunchMode; // 속사, 연사 모드 설정 
	class Gun* mGun;
	int mHP;
	COLOR mHPBarColor;
};

