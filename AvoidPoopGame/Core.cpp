#include "Core.h"

Core* Core::mCore = nullptr;
bool Core::mFlag = true;

Core::Core()
	: mHinstance(nullptr)
	, mHwnd(nullptr)
	, mHdc(nullptr)
	, mHbitmap(nullptr)
{
}

Core::~Core()
{
	ReleaseDC(mHwnd, mHdc);
	mHdc = nullptr;

	if (nullptr != mHbitmap)
	{
		DeleteObject(mHbitmap);
		mHbitmap = nullptr;
	}
}

Core* Core::getInstance()
{
	if (nullptr == mCore)
	{
		mCore = new Core;
	}
	return mCore;
}

void Core::deleteInstance()
{
	if (nullptr != mCore)
	{
		delete mCore;
		mCore = nullptr;
	}
}

bool Core::init(HINSTANCE hInstance)
{
	mHinstance = hInstance;

	MyRegisterClass();

	if (false == Create())
	{
		return false;
	}

	return true;
}

int Core::run()
{
	MSG msg = {};

	while (mFlag)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 실제 게임 로직 실행
		}
	}
	return (int)msg.wParam;
}

ATOM Core::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = mHinstance;
	wcex.hIcon = LoadIcon(mHinstance, MAKEINTRESOURCE(IDI_AVOIDPOOPGAME));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr; // MAKEINTRESOURCEW(IDC_AVOIDPOOPGAME);
	wcex.lpszClassName = TEXT("AvoidPoopGame");
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

bool Core::Create()
{
	mHwnd = CreateWindowW(TEXT("AvoidPoopGame"), TEXT("AvoidPoopGame"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mHinstance, nullptr);

	if (nullptr == mHwnd)
	{
		return false;
	}

	mHdc = GetDC(mHwnd);

	RECT window = { 0, 0, 1200, 600 };
	AdjustWindowRect(&window, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(mHwnd, HWND_TOP, window.left, 0, window.right - window.left, window.bottom - window.top, SWP_SHOWWINDOW);
	ShowWindow(mHwnd, SW_SHOW);

	GetClientRect(mHwnd, &window); // 크기 확인용 코드

	return true;
}

LRESULT Core::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		mFlag = false;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
