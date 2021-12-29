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
	// ���� ���콺 Ŭ�� �̺�Ʈ ����
	StageManager::getInstance()->changeNextStage();
}	
