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

	list<class CBullet*>& getBullets()
	{
		return mBullets;
	}

	list<class CObj*>& getObjs() 
	{
		return mCObjs;
	}

private:
	class Texture* getTexture(const wchar_t* tag);
	void createEnemy();
	void deleteObject();

	list<class CObj*> mCObjs;
	list<class CBullet*> mBullets;
};