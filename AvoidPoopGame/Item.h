#pragma once
#include "Obj.h"

class Item :
	public Obj
{
public:
	Item(FPOINT pos, int size, float speed, COLOR itemColor);
	~Item() = default;

	void init() override;
	void update() override;
	void render(HDC backDC) override;

	bool isValid();

	COLOR getItemColor() const
	{
		return mItemColor;
	}

	void changeScale(float scale)
	{
		mScale = scale;
	}

	void changeItemColor(COLOR color)
	{
		mItemColor = color;
	}

	void changeSpeed(float speed)
	{
		mSpeed = speed;
	}

private:
	float mSpeed;
	float mScale;
	COLOR mItemColor;
};

