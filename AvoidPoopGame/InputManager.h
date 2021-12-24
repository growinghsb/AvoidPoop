#pragma once

#include "Game.h"

class InputManager
{
public:
	static InputManager* getInstance();
	static void deleteInstance();

	void init();
	void update();

	bool isPress(KEY_LIST key) const
	{
		return	mKeyInfo[(UINT)key].mKeyState == KEY_STATE::PRESS ?
				true : false;
	}

	bool isTic(KEY_LIST key) const
	{
		return	mKeyInfo[(UINT)key].mKeyState == KEY_STATE::TIC ?
			true : false;
	}

private:
	InputManager();
	~InputManager() = default;

	static InputManager* mInputManager;

	vector<KEY_INFO> mKeyInfo;
	int mKeyCodes[(UINT)KEY_LIST::END];
};

