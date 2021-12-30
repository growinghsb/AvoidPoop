#pragma once

#include "Layer.h"

class ObjLayer :
	public Layer
{
public:
	ObjLayer();
	~ObjLayer();

	void init() override;
	void update() override;
	void collision() override;
	void render(HDC backDC) override;

	list<class CObj*>& getObjs() 
	{
		return mCObjs;
	}

	class CPlayer& getPlayer() 
	{
		return *(CPlayer*)mCObjs.front();
	}

private:
	class Texture* getTexture(const wchar_t* tag);
	void createEnemy();
	void deleteObject();

	list<class CObj*> mCObjs;
};