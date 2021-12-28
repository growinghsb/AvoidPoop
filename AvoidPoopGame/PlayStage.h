#pragma once
#include "Stage.h"

class PlayStage :
    public Stage
{
public:
	PlayStage(int order);
	~PlayStage();

	void init() override;
	void update() override;
	void render(HDC backDC) override;
	void enter() override;
	void exit() override;
	
	void stageClear();
	bool crushMonsterRemove(class Bullet& bullet);
	
private:
	void crushCheckMonsterPlayer();
	void crushCheckItemPlayer();
	void createMonster();
	void createItem(class Monster& monster);

	vector<class Obj*> mObjs;
	list<class Monster*> mMonsters;
	float mMonsterScale;
	float mMonsterRegenTime;
	list<class Item*> mItems;
};

