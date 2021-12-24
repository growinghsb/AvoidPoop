#pragma once

#include "Game.h"

class TimeManager
{
public:
	static TimeManager* getInstance();
	static void deleteInstance();

	void init();
	void update(HWND hWnd);
	
	float getDS() const 
	{
		return mDS;
	}

private:
	TimeManager();
	~TimeManager() = default;

	static TimeManager* mTimeManager;

	LARGE_INTEGER mFrequency;
	LARGE_INTEGER mPrevCounter;
	LARGE_INTEGER mCurCounter;

	float mDS;
	int	  mFPS;
	int   mSecond;
};

