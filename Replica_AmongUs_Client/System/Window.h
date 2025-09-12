#pragma once
#define WIN32_LEAN_AND_MEAN
#include "../stdafx.h"
#include "../Render.h"

struct DXDesc
{
	wstring AppName;
	HINSTANCE instance;
	HWND handle;
	UINT width; //윈도우 창의 가로 세로 크기
	UINT height;
};

class Window
{
public:

	Window(DXDesc desc);
	~Window();

	WPARAM Run(); //게임루프 함수

private:
	//함수호출 규약
	//stdcall
	//cdecl
	static LRESULT CALLBACK WndProc //메세지 처리함수
	(
		HWND handle,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	DXDesc desc;
};

