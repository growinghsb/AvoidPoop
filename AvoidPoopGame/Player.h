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

	void changeHP(int hp)
	{
		mHP = hp;
	}

private:
	float mSpeed;
	float mScale;
	bool mLaunchMode; // 속사, 연사 모드 설정 
	class Gun* mGun;
	int mHP;
	COLOR mHPBarColor;
};

