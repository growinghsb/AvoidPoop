#pragma once

#include "Game.h"

class Core
{
public:
	static Core* getInstance();
	static void  deleteInstance();

	bool		 init(HINSTANCE hInstance);
	void		 update();
	int			 run();

private:
	Core();
	~Core();

	ATOM					   MyRegisterClass();
	bool					   Create();
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

	static Core* mCore;
	static bool  mFlag;

	HINSTANCE mHinstance;
	HWND	  mHwnd;
	HDC		  mHdc;
	HBITMAP	  mHbitmap;
};

