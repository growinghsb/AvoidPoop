#pragma once
#include "Stage.h"

class IntroStage :
	public Stage
{
public:
	IntroStage(int order);
	~IntroStage();

	void init()				override;
	void update()		    override;
	void render(HDC backDC) override;

	void stageClear()		override;


	void enter() override;
	void exit()  override;

private:
	enum {BUTTON_COUNT = 5};
	vector<class CButton*> mButtons;
};

