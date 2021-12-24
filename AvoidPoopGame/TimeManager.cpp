#include "TimeManager.h"

TimeManager* TimeManager::mTimeManager = nullptr;

TimeManager::TimeManager()
	: mFrequency{}
	, mPrevCounter{}
	, mCurCounter{}
	, mDS(0.f)
	, mFPS(0)
	, mSecond(0)
{
}

TimeManager* TimeManager::getInstance()
{
	if (nullptr == mTimeManager)
	{
		mTimeManager = new TimeManager;
	}
	return mTimeManager;
}

void TimeManager::deleteInstance()
{
	if (nullptr != mTimeManager)
	{
		delete mTimeManager;
		mTimeManager = nullptr;
	}
}

void TimeManager::init()
{
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mPrevCounter);
}

void TimeManager::update(HWND hWnd)
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
		swprintf(text, LENGTH, L"FPS: %d DS: %f Second: %d��", mFPS, mDS, mSecond);
		SetWindowTextW(hWnd, text);

		mFPS = 0;
	}
	mPrevCounter = mCurCounter;
}