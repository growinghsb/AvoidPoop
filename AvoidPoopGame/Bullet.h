#pragma once

#include "Game.h"
#include "Obj.h"

class Bullet
	: public Obj
{
public:
	Bullet(FPOINT pos, int size);
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

private:
	float mSpeed;
};

