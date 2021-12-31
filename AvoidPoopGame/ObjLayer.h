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

	void createItem(FPOINT pos);

	class Texture* getTexture(const wchar_t* tag, int range);

	list<class CObj*>& getObjs() 
	{
		return mCObjs;
	}

	class CPlayer& getPlayer() 
	{
		return *(CPlayer*)mCObjs.front();
	}

private:
	class Texture* itemChoice(ITEM_LIST item);
	void createEnemy();
	void deleteObject();

	list<class CObj*> mCObjs;
	ITEM_LIST mItemList[(UINT)ITEM_LIST::END];
};