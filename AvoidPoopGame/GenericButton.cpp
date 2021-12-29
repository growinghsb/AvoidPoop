#include "GenericButton.h"
#include "Core.h"
#include "TimeManager.h"
#include "StageManager.h"

GenericButton::GenericButton(FPOINT pos, int size, Texture* texture)
	: CButton(pos, size, texture)
{
}

void GenericButton::isClicked()
{
	// 왼쪽 마우스 클릭 이벤트 수신
	StageManager::getInstance()->changeNextStage();
}	
