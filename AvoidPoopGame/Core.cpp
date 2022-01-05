#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "StageManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"

Core* Core::mCore = nullptr;
bool Core::mFlag = true;

bool gameStart = false;

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
	
	CollisionManager::deleteInstance();
	TimeManager::deleteInstance();
	InputManager::deleteInstance();
	ResourceManager::deleteInstance();
	EventManager::deleteInstance();
	StageManager::deleteInstance();
}

bool Core::init(HINSTANCE hInstance)
{
	srand((UINT)time(nullptr));

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

	// Timer 초기화는 게임 시작시부터 실행시키기 위해
	// introStage 내부에서 게임 시작 시 init() 실행

	// Collision 같은 경우 객체만 한 번 생성되면 된다. 
	// 따로 init, update 등의 작업이 필요 없다.

	EventManager::getInstance()->init();
	ResourceManager::getInstance()->init();
	InputManager::getInstance()->init();
	StageManager::getInstance()->init();

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
			update();
			render();
		}
	}
	return (int)msg.wParam;
}

void Core::update()
{
	// 기본값은 false, 게임 시작시에 true 로 변경
	// 게임 시작은 IntroStage 에서 시작 버튼 눌렀을 때
	if (gameStart)
	{
		TimeManager::getInstance()->update(mHwnd);
	}
	InputManager::getInstance()->update();
	StageManager::getInstance()->update();
}

void Core::render()
{
	// mBackDC 를 전달 하면서 렌더링을 진행 하고,
	// 최종적으로 BitBlt() 를 통해 화면에 나타낸다.
	FillRect(mBackDC, &mWindow, (HBRUSH)(COLOR_WINDOW + 1));

	StageManager::getInstance()->render(mBackDC);

	BitBlt(mHdc, 0, 0, mWindow.right, mWindow.bottom, mBackDC, 0, 0, SRCCOPY);
	
	// 이벤트매니저는 모든 작업이 종료된 뒤 
	// 업데이트를 진행한다. 프레임이 종료된 후 
	// 진행되야 하는 작업들을 처리하기 때문
	EventManager::getInstance()->update();
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
	wcex.lpszClassName = L"Shotting Game";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

bool Core::Create()
{
	mHwnd = CreateWindowW(L"Shotting Game", L"Shotting Game", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mHinstance, nullptr);

	if (nullptr == mHwnd)
	{
		return false;
	}

	mHdc = GetDC(mHwnd);

	mWindow = { 0, 0, 750, 768 };
	AdjustWindowRect(&mWindow, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(mHwnd, HWND_TOP, mWindow.left, 0, mWindow.right - mWindow.left, mWindow.bottom - mWindow.top, SWP_SHOWWINDOW);
	ShowWindow(mHwnd, SW_SHOW);

	GetClientRect(mHwnd, &mWindow); // 크기 확인용 코드

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
