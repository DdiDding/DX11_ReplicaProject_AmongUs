#pragma once
#define WIN32_LEAN_AND_MEAN
#include "../stdafx.h"
#include "../Render.h"

struct DXDesc
{
	wstring AppName;
	HINSTANCE instance;
	HWND handle;
	UINT width; //������ â�� ���� ���� ũ��
	UINT height;
};

class Window
{
public:

	Window(DXDesc desc);
	~Window();

	WPARAM Run(); //���ӷ��� �Լ�

private:
	//�Լ�ȣ�� �Ծ�
	//stdcall
	//cdecl
	static LRESULT CALLBACK WndProc //�޼��� ó���Լ�
	(
		HWND handle,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	DXDesc desc;
};

