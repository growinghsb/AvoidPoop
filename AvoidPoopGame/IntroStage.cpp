#include "IntroStage.h"
#include "Core.h"
#include "StageManager.h"
#include "TimeManager.h"

extern bool gameStart;

IntroStage::IntroStage(int order)
	: Stage(order)
{
}

void IntroStage::enter()
{
	init();
}

void IntroStage::init()
{
}

void IntroStage::update()
{
}

void IntroStage::render(HDC backDC)
{
	if (IDYES == MessageBox(Core::getInstance()->getHWnd(), TEXT("������ �����Ͻðڽ��ϱ�?"), TEXT("�ȳ�"), MB_ICONQUESTION | MB_YESNO))
	{
		TimeManager::getInstance()->init();
		gameStart = true;

		StageManager::getInstance()->changeNextStage();
	}
	else
	{
		DestroyWindow(Core::getInstance()->getHWnd());
	}
}


void IntroStage::exit()
{
}
