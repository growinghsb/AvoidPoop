#pragma once

#include "CObj.h"

class CBullet
	: public CObj
{
public:
	CBullet(wstring tag, FPOINT pos, POINT size, class Texture* texture, class ObjLayer* layer, float speedWeight, int offencePower);
	virtual ~CBullet() = default;

	virtual void init();
	virtual void update();
	virtual void render(HDC backDC);
	virtual bool collision();

	bool isValid() const
	{
		return (int)mPos.mY > 0;
	}

	void setSpeedWeight(float weight)
	{
		mSpeedWeight = weight;
	}

	void setOffencePower(int power)
	{
		mOffencePower = power;
	}

	int getOffencePower() const
	{
		return mOffencePower;
	}

private:
	class ObjLayer* mLayer;
	float mSpeed;
	float mSpeedWeight;
	int mOffencePower;
};

