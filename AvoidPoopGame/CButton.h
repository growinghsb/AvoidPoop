#pragma once

#include "Obj.h"

class CButton
	: public Obj
{
public:
	CButton(FPOINT mps, int size, class Texture* texture);
	virtual ~CButton() = default;

	virtual void init();
	virtual void update();
	virtual void render(HDC backDC);
	virtual void isClicked() = 0;

	class Texture* getTexture() 
	{
		return mTexture;
	}

private:
	class Texture* mTexture;
};

