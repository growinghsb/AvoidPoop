#pragma once

#include "Game.h"

class Core
{
public:
	ATOM					   MyRegisterClass();
	bool					   Create();
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	int run();

	static Core* getInstance();
	static void  deleteInstance();
	bool		 init(HINSTANCE hInstance);

private:
	Core();
	~Core();

	static Core* mCore;
	static bool  mFlag;

	HINSTANCE mHinstance;
	HWND	  mHwnd;
	HDC		  mHdc;
	HBITMAP	  mHbitmap;
};

