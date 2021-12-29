#pragma once

#include "CObj.h"

class CBullet
	: public CObj
{
public:
	CBullet(wstring tag, FPOINT pos, POINT size, class Texture* texture, class ObjLayer* layer);
	virtual ~CBullet() = default;

	virtual void init();
	virtual void update();
	virtual void render(HDC backDC);
	virtual void collision();

	bool isValid() const
	{
		return (int)mPos.mY > 0;
	}

private:
	class ObjLayer* mLayer;
	float mSpeed;
	float mSpeedWeigth;

};

