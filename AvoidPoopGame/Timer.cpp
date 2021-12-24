#include "Timer.h"

Timer* Timer::mTimer = nullptr;

Timer::Timer()
	: mFrequency{}
	, mPrevCounter{}
	, mCurCounter{}
	, mDS(0.f)
	, mFPS(0)
	, mSecond(0)
{
}

Timer* Timer::getInstance()
{
	if (nullptr == mTimer)
	{
		mTimer = new Timer;
	}
	return mTimer;
}

void Timer::deleteInstance()
{
	if (nullptr != mTimer)
	{
		delete mTimer;
		mTimer = nullptr;
	}
}

void Timer::init()
{
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mPrevCounter);
}

void Timer::update(HWND hWnd)
{
	static float ds = 0.f;

	QueryPerformanceCounter(&mCurCounter);
	mDS = (float)(mCurCounter.QuadPart - mPrevCounter.QuadPart) / (float)mFrequency.QuadPart;

	ds += mDS;
	++mFPS;

	if (ds >= 1.f)
	{
		ds = ds - 1.f;
		mSecond += 1;

		enum { LENGTH = 128 };
		wchar_t text[LENGTH] = {};
		swprintf(text, LENGTH, L"FPS: %d DS: %f Second: %d√ ", mFPS, mDS, mSecond);
		SetWindowTextW(hWnd, text);

		mFPS = 0;
	}
	mPrevCounter = mCurCounter;
}
