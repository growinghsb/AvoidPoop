#pragma once

#include "Obj.h"

class Bullet
	: public Obj
{
public:
	Bullet(FPOINT pos, int size, float speed);
	~Bullet() = default;

	void init() override;
	void update() override;
	void render(HDC backDC) override;

	bool isValid() const
	{
		return (int)mPos.mY > 0;
	}

	void changePos(FPOINT pos) 
	{
		mPos = pos;
	}

	void scaleUp() 
	{
		if ((int)mScale < 2) 
		{
			mScale += 0.1f;
		}
		else 
		{
			mScale = 1.9f;
		}
	}

	void scaleDown() 
	{
		if ((int)mScale >= 1) 
		{
			mScale -= 0.1f;
		}
		else 
		{
			mScale = 1.0f;
		}
	}

private:
	float mSpeed;
	float mScale;
};

