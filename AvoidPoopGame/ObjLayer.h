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

	list<class CObj*>& getObstacle() 
	{
		return mLists[(UINT)OBJ_TYPE::OBSTACLE];
	}

	class CPlayer& getPlayer() 
	{
		return *(CPlayer*)mLists[(UINT)OBJ_TYPE::PLAYER].front();
	}

private:
	class Texture* itemChoice(ITEM_LIST item);
	void createObstacle();
	void createEnemy();
	void deleteObject();

	list<class CObj*> mLists[(UINT)OBJ_TYPE::END];
	ITEM_LIST mItemList[(UINT)ITEM_LIST::END];
};