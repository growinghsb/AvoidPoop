#pragma once

#include "CObj.h"

class CBullet
	: public CObj
{
public:
	CBullet(wstring tag, FPOINT pos, POINT size, class Texture* texture, class ObjLayer* layer, FPOINT ownerPos, float speedWeight, int offencePower, float angle);
	virtual ~CBullet() = default;

	virtual void init();
	virtual void update();
	virtual void render(HDC backDC);
	virtual bool collision();

	bool isValid() const
	{
		return (int)mPos.mY > 0;
	}

	int getOffencePower() const
	{
		return mOffencePower;
	}

	void setSpeedWeight(const float weight)
	{
		mSpeedWeight = weight;
	}

	void setOffencePower(const int power)
	{
		mOffencePower = power;
	}

	void setOwnerPos(const FPOINT pos) 
	{
		mOwnerPos = pos;
	}
	
private:
	class ObjLayer* mLayer;
	FPOINT mOwnerPos;
	float mSpeed;
	float mSpeedWeight;
	int mOffencePower;
	float mAngle;
};

