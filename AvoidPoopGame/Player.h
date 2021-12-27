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
		
		// ���� �Լ��� �÷��̾� ���� Ȯ�� �� �׾����� Stage �ٽ� ����
		if (mHP <= 0) 
		{
			mHP = 100;
		}
	}

	// �簢�� �� �簢�� �浹 �� ���
	bool isOverlapX(float x) 
	{
		if (x <= mPos.mX + mSize || x >= mPos.mX)
		{
			return true;
		}
		return false;
	}

	// �簢�� �� �簢�� �浹 �� ���
	bool isOverlapY(float y) 
	{
		return y >= mPos.mY;
	}

private:
	float mSpeed;
	float mScale;
	bool mLaunchMode; // �ӻ�, ���� ��� ���� 
	class Gun* mGun;
	int mHP;
	COLOR mHPBarColor;
};

