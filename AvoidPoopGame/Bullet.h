#pragma once

#include "Obj.h"

class Bullet
	: public Obj
{
public:
	Bullet(FPOINT pos, int size, float speed, float scale);
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

private:
	float mSpeed;
	float mScale;
};

