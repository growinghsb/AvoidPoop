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
	// 해당 마우스 이벤트 클릭 후 
	// 아래 코드가 돌기전에 다른 곳을 누르면
	// 그 입력 역시 이쪽으로 들어와서 다른 
	// 좌표로 업데이트 될 수 있다. 
	// 찰나긴 하지만 클릭 자체를 모든 윈도우에서
	// 받아서 비동기로 처리하기 때문이다. 
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

// 전방선언으로는 해당 클래스에 대해서 소멸자 호출이 불가능하다. 
// 불완전한 유형이라고 해서 전방선언만으로는 해당 소멸자를
// 알 수 없어 호출하지 않아, 메모리 릭이 난다. 해서 꼭
// include 를 하거나, include 된 cpp 로 빼서 처리해야 한다.
// C4150 - 컴파일에러 번호
void IntroStage::stageClear()
{
	for (int i = 0; i < BUTTON_COUNT; ++i)
	{
		delete mButtons[i];
	}
	mButtons.clear();
}

