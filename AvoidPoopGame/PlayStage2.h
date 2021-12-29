#pragma once
#include "Stage.h"
class PlayStage2 :
    public Stage
{
public:
	PlayStage2(int order);
	virtual ~PlayStage2();
									
	virtual void init()				override;
	virtual void update()			override;
	virtual void render(HDC backDC) override;
	virtual void enter()			override;
	virtual void exit()				override;
	virtual void stageClear()		override;
};

