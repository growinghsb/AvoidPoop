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

	void setSpeedWeight(bool upDown) 
	{
		// true 면 증가, false 면 감소
		if (upDown) 
		{
			mSpeedWeight += 0.1f;

			if (mSpeedWeight > 2.0f)
			{
				mSpeedWeight = 2.0f;
			}
		}
		else 
		{
			mSpeedWeight -= 0.1f;

			if (mSpeedWeight < 1.0f) 
			{
				mSpeedWeight = 1.0f;
			}
		}
	}

private:
	class ObjLayer* mLayer;
	float mSpeed;
	float mSpeedWeight;

};

