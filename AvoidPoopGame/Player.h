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
		if (mHP + int(mHP * 0.2) < 100)
		{
			mHP += int(mHP * 0.2);
		}
		else
		{
			mHP = 100;
		}
	}

	// ���� Ȯ��
	bool isAlive()
	{
		return mHP > 0;
	}

private:
	float mSpeed;
	float mScale;
	bool mLaunchMode; // �ӻ�, ���� ��� ���� 
	class Gun* mGun;
	int mHP;
	COLOR mHPBarColor;
	class Texture* mTexture;
};

