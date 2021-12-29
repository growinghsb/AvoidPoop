#pragma once

#include "CObj.h"

class CBullet
	: public CObj
{
	CBullet(wstring tag, FPOINT pos, POINT size, class Texture* texture);
	virtual ~CBullet() = default;
};

