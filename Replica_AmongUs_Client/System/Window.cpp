#include "Window.h"
#include "../System/Camera.h"
#include "../Manager/UiManager.h"
#include "../Manager/TaskManager.h"



//상대경로 : ./ 현재폴더, ../ 상위폴더
//절대경로 : 

HINSTANCE instance;

Window::Window(DXDesc desc)
{
	WNDCLASSEX wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = desc.instance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

	desc.handle = CreateWindowEx
	(
		WS_EX_APPWINDOW,
		desc.AppName.c_str(),
		desc.AppName.c_str(),
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		(HMENU)NULL,
		desc.instance,
		NULL
	);

	RECT rect = { 0, 0, (LONG)desc.width, (LONG)desc.height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	//x, y, width, height
	MoveWindow
	(
		desc.handle
		, centerX, centerY
		, rect.right - rect.left, rect.bottom - rect.top
		, true
	);

	ShowWindow(desc.handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.handle);
	SetFocus(desc.handle);

	ShowCursor(true);//
	Window::desc = desc;

	::instance = desc.instance;
}

Window::~Window()
{
	DestroyWindow(desc.handle);
	desc.handle = NULL;

	UnregisterClass(desc.AppName.c_str(), desc.instance);
	desc.instance = NULL;

	return;
}

WPARAM Window::Run()
{
	MSG msg = { 0 }; //스니핑


	//////////////////////////////////////////
	//Singleton Create
	//////////////////////////////////////////

	Keyboard::Create();
	Mouse::Create();
	Time::Create();
	Time::Get()->Start();
	PublicCamera::Create();
	Collision::Create();

	Graphic::Create();
	Graphic::Get()->Init(desc.handle);

	ImageManager::Create();
	AnimationManager::Create();
	MapManager::Create();
	SceneManager::Create();
	FontManager::Create();
	


	Render::Create();

	

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//게임 종료 확인문
			if (Render::Get()->GetGameEnd() == true) break;

			//////////////////////////////////////////
			//Update
			//////////////////////////////////////////
			Keyboard::Get()->Update();
			Mouse::Get()->Update();
			Time::Get()->Update();

			Render::Get()->Update();



			//////////////////////////////////////////
			//Render
			//////////////////////////////////////////
			Graphic::Get()->Begin();

			Render::Get()->Rendering();

			Graphic::Get()->End();
		}
	}


	//////////////////////////////////////////
	//Singleton Delete
	//////////////////////////////////////////

	Render::Delete();


	FontManager::Delete();
	UiManager::Delete();
	TaskManager::Delete();
	SceneManager::Delete();
	MapManager::Delete();
	AnimationManager::Delete();
	ImageManager::Delete();

	Graphic::Delete();


	Collision::Delete();
	PublicCamera::Delete();
	Time::Delete();
	Mouse::Delete();
	Keyboard::Delete();

	return msg.wParam;
}


LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	Mouse::Get()->InputProc(message, wParam, lParam);

	switch (message) {

		case WM_CREATE: {
			break;
		}


		case WM_CLOSE: {

			PostQuitMessage(0);
			return 0;

		}

		case WM_DESTROY: {

			PostQuitMessage(0);
			return 0;

		}


		default: {
			return DefWindowProc(handle, message, wParam, lParam);

		}
	}
	
	return 0;
}
