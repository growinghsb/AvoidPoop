#pragma once

#include "Game.h"

class Obj
{
public:
	virtual ~Obj() = default;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render(HDC backDC) = 0;

protected:
	Obj(FPOINT pos, int size);

	FPOINT mPos;
	int mSize;
};

