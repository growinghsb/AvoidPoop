#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Stage.h"

Core* Core::mCore = nullptr;
bool Core::mFlag = true;

Core::Core()
	: mHinstance(nullptr)
	, mHwnd(nullptr)
	, mHdc(nullptr)
	, mBackBuffer(nullptr)
	, mBackDC(nullptr)
	, mWindow{}
{
}

Core::~Core()
{
	ReleaseDC(mHwnd, mHdc);
	DeleteObject(mBackBuffer);
	DeleteDC(mBackDC);
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

	TimeManager::deleteInstance();
	InputManager::deleteInstance();
	Stage::deleteInstance();
}

bool Core::init(HINSTANCE hInstance)
{
	mHinstance = hInstance;

	MyRegisterClass();

	if (false == Create())
	{
		return false;
	}

	mBackDC = CreateCompatibleDC(mHdc);
	mBackBuffer = CreateCompatibleBitmap(mHdc, mWindow.right, mWindow.bottom);

	HBITMAP prevBitmap = (HBITMAP)SelectObject(mBackDC, mBackBuffer);
	DeleteObject(prevBitmap);

	TimeManager::getInstance()->init();
	InputManager::getInstance()->init();
	Stage::getInstance()->init();

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
			// ���� ���� ���� ����
			update();
			render();
		}
	}
	return (int)msg.wParam;
}


void Core::update()
{
	TimeManager::getInstance()->update(mHwnd);
	InputManager::getInstance()->update();
	Stage::getInstance()->update();
}

void Core::render()
{
	// mBackDC �� ���� �ϸ鼭 �������� ���� �ϰ�,
	// ���������� BitBlt() �� ���� ȭ�鿡 ��Ÿ����.
	Stage::getInstance()->render(mBackDC);

	BitBlt(mHdc, 0, 0, mWindow.right, mWindow.bottom, mBackDC, 0, 0, SRCCOPY);
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

	mWindow = { 0, 0, 1200, 600 };
	AdjustWindowRect(&mWindow, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(mHwnd, HWND_TOP, mWindow.left, 0, mWindow.right - mWindow.left, mWindow.bottom - mWindow.top, SWP_SHOWWINDOW);
	ShowWindow(mHwnd, SW_SHOW);

	GetClientRect(mHwnd, &mWindow); // ũ�� Ȯ�ο� �ڵ�

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
