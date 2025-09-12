#pragma warning(disable : 4996)

#include "stdafx.h"
#include "System/Window.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	////AllocConsole();
	//freopen("CONOUT$", "wb", stdout);

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Window* window = new Window(desc);
	WPARAM wParam = window->Run();
	SAFE_DELETE(window);

	return wParam;
}