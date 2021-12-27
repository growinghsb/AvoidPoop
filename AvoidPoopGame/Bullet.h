#pragma once

#include "Obj.h"

class Bullet
	: public Obj
{
public:
	Bullet(FPOINT pos, int size, float speed, float scale, int offensePower);
	~Bullet() = default;

	void init() override;
	void update() override;
	void render(HDC backDC) override;

	bool isValid() const
	{
		return (int)mPos.mY > 0;
	}

	void setScale(float scale)
	{
		mScale = scale;
	}

	int getOffensePower() const
	{
		return mOffensePower;
	}

	void changeOffensePower(int offensePower)
	{
		mOffensePower = offensePower;

		if (mOffensePower < 0)
		{
			mOffensePower = 1;
		}
	}

private:
	float mSpeed;
	float mScale;
	int mOffensePower;
};