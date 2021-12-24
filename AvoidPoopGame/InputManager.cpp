#include "InputManager.h"

InputManager* InputManager::mInputManager = nullptr;

InputManager::InputManager() 
    : mKeyCodes{ 
	'A',
	'B',
	'C',
	'D',
	'E',
	'F',
	'G',
	'H',
	'I',
	'J',
	'K',
	'L',
	'M',
	'N',
	'O',
	'P',
	'Q',
	'R',
	'S',
	'T',
	'U',
	'V',
	'W',
	'X',
	'Y',
	'Z',
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9', 
	VK_ESCAPE,
	VK_SPACE,
	VK_LEFT,
	VK_UP,
	VK_RIGHT,
	VK_DOWN,
	VK_LSHIFT,
	VK_LCONTROL,
	VK_LMENU,
}
{
    mKeyInfo.reserve((UINT)KEY_LIST::END);

    for (int i = 0; i < (UINT)KEY_LIST::END; ++i)
    {
        mKeyInfo.push_back(KEY_INFO{KEY_STATE::NONE, false});
    }
}


InputManager* InputManager::getInstance()
{
    if (nullptr == mInputManager) 
    {
        mInputManager = new InputManager;
    }
    return mInputManager;
}

void InputManager::deleteInstance()
{
    if (nullptr != mInputManager) 
    {   
        delete mInputManager;
        mInputManager = nullptr;
    }
}

void InputManager::init()
{
}

void InputManager::update()
{
	for (int i = 0; i < (UINT)KEY_LIST::END; ++i) 
	{
		if (GetAsyncKeyState(mKeyCodes[i]) & 0x8000) 
		{
			if (KEY_STATE::NONE == mKeyInfo[i].mKeyState) 
			{
				mKeyInfo[i].mKeyState = KEY_STATE::TIC;
			}
			else if (KEY_STATE::TIC == mKeyInfo[i].mKeyState)
			{
				mKeyInfo[i].mKeyState = KEY_STATE::PRESS;
			}
		}
		else 
		{
			if (KEY_STATE::TIC == mKeyInfo[i].mKeyState ||
				KEY_STATE::PRESS == mKeyInfo[i].mKeyState)
			{
				mKeyInfo[i].mKeyState = KEY_STATE::ANY;
			}
			else if (KEY_STATE::ANY == mKeyInfo[i].mKeyState)
			{
				mKeyInfo[i].mKeyState = KEY_STATE::NONE;
			}
		}
	}
}