#pragma once

#include "Game.h"

class Layer
{
public:	
	Layer() = default;
	virtual	~Layer() = default;
	
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void collision() = 0;
	virtual void render(HDC backDC) = 0;
};

