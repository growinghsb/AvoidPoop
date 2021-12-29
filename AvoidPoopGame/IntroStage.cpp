#include "IntroStage.h"
#include "Core.h"
#include "StageManager.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "GenericButton.h"
#include "InputManager.h"

extern bool gameStart;

IntroStage::IntroStage(int order)
	: Stage(order)
{
	mButtons.reserve(BUTTON_COUNT);

	wstring tag(L"player1");
	Texture* texture = FIND_TEXTURE(tag.c_str());

	enum { PADDING = 30 };
	int textureSize = texture->getResolution().x + PADDING;

	float startX = float(WINDOW.right - textureSize * BUTTON_COUNT) / 2;

	for (int i = 0; i < BUTTON_COUNT; ++i)
	{
		tag.erase(tag.size() - 1);
		tag += to_wstring(i + 1);

		mButtons.push_back(new GenericButton(FPOINT{ startX + (i * textureSize), (float)WINDOW.bottom / 2 }, textureSize - PADDING, FIND_TEXTURE(tag.c_str())));
	}
}

IntroStage::~IntroStage()
{
	stageClear();
}

void IntroStage::enter()
{
	gameStart = false;
	TimeManager::deleteInstance();
	
	enum { LENGTH = 128 };
	wchar_t text[LENGTH] = {};
	swprintf(text, LENGTH, L"Shotting Game");
	SetWindowTextW(Core::getInstance()->getHWnd(), text);

	init();
}

void IntroStage::init()
{
}

void IntroStage::update()
{
	// �ش� ���콺 �̺�Ʈ Ŭ�� �� 
	// �Ʒ� �ڵ尡 �������� �ٸ� ���� ������
	// �� �Է� ���� �������� ���ͼ� �ٸ� 
	// ��ǥ�� ������Ʈ �� �� �ִ�. 
	// ������ ������ Ŭ�� ��ü�� ��� �����쿡��
	// �޾Ƽ� �񵿱�� ó���ϱ� �����̴�. 
	if (ISTIC(KEY_LIST::LBUTTON))
	{
		POINT pos;
		GetCursorPos(&pos);
		ScreenToClient(Core::getInstance()->getHWnd(), &pos);

		for (int i = 0; i < BUTTON_COUNT; ++i) 
		{
			int buttonX = (int)mButtons[i]->getPos().mX;
			int buttonY = (int)mButtons[i]->getPos().mY;

			if (buttonX < pos.x
				&& buttonX + mButtons[i]->getSize() > pos.x 
				&& buttonY < pos.y
				&& buttonY + mButtons[i]->getSize() > pos.y) 
			{
				StageManager::getInstance()->setCurrentPlayer(mButtons[i]->getTexture());
				mButtons[i]->isClicked();
				return;
			}
		}
	}
}

void IntroStage::render(HDC backDC)
{
	for (int i = 0; i < BUTTON_COUNT; ++i)
	{
		mButtons[i]->render(backDC);
	}
}

void IntroStage::exit()
{
	gameStart = true;
	TimeManager::getInstance()->init();
}

// ���漱�����δ� �ش� Ŭ������ ���ؼ� �Ҹ��� ȣ���� �Ұ����ϴ�. 
// �ҿ����� �����̶�� �ؼ� ���漱�����δ� �ش� �Ҹ��ڸ�
// �� �� ���� ȣ������ �ʾ�, �޸� ���� ����. �ؼ� ��
// include �� �ϰų�, include �� cpp �� ���� ó���ؾ� �Ѵ�.
// C4150 - �����Ͽ��� ��ȣ
void IntroStage::stageClear()
{
	for (int i = 0; i < BUTTON_COUNT; ++i)
	{
		delete mButtons[i];
	}
	mButtons.clear();
}

