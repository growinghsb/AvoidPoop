#pragma once

#include "Game.h"

class Timer
{
public:
	static Timer* getInstance();
	static void deleteInstance();

	void init();
	void update(HWND hWnd);

private:
	Timer();
	~Timer() = default;

	static Timer* mTimer;

	LARGE_INTEGER mFrequency;
	LARGE_INTEGER mPrevCounter;
	LARGE_INTEGER mCurCounter;

	float mDS;
	int	  mFPS;
	int   mSecond;
};

