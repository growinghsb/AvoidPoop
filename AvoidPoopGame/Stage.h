#pragma once

#include "Game.h"

class Stage
{
public:
	static Stage* getInstance();
	static void deleteInstance();

	void init();
	void update();
	void render(HDC backDC);

	bool CrushMonsterRemove(class Bullet& bullet);

private:
	Stage();
	~Stage();

	void createMonster();
	void createItem(class Monster& monster);

	static Stage* mStage;

	vector<class Obj*> mObjs;
	list<class Monster*> mMonsters;
	float mMonsterScale;
	float mMonsterRegenTime;
	list<class Item*> mItems;
	ITEM_TYPE mItemTypes[(UINT)ITEM_TYPE::END];
};

