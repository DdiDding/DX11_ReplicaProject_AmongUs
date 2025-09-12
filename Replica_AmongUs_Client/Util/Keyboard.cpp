#include "../stdafx.h"
#include "Keyboard.h"

#include <Windows.h>

Keyboard* Keyboard::instance = NULL;

Keyboard * Keyboard::Get()
{
	return instance;
}

void Keyboard::Create()
{
	if (instance == nullptr)
		instance = new Keyboard();
}

void Keyboard::Delete()
{
	SAFE_DELETE(instance);
}

void Keyboard::Update()
{

	//처음키를 누를때는 의미가 없지만
	//키를 누른후 2번째 반복부터 효력이있는 부분

	//1.처음 누를 때		-아무것도 없는걸 복사했으니 아무것도 없음
	//2.누르고 있을 때	-밑에서 누른 값이 담긴 배열을 복사 -> 후에 이것으로 같은 키를 눌렀는지 비교를하는 부분
	memcpy(keyOldState, keyState, sizeof(keyOldState));//이거 왜하는거징

	//void ZeroMemory -   메모리를 0으로 채움
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));


	//256 개의 가상 키 상태를 지정된 버퍼에 복사하는 함수. -> 그래서 256크기의 배열을 생성 [근데 크기가 달라도 에러가 안남]
	//https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes 키코드 표 256개가 맞다
	GetKeyboardState(keyState);

	//DWORD - unsignd long
	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{



		//이 And연산의 값은 두가지가 나온다 
		//1. 0b 0000 0000 [값이 128 미만일 때] - 0
		//2. 0b 1000 0000 [값이 128 이상일 때] - 128

		//왜 128이 기준일까?  -  GetKeyboardState에서는 누른 키값의 배열에 값을 128이상의 값으로 두고, 누르지않은 배열의 값은 0으로 두기때문
		//						그래서 밑에서 128이면 1로 변환하여 true로 놓고 0을 false로 놓은듯하다
		byte key = keyState[i] & 0x80;
		// ★ 0x80 -> 0b 1000 0000 -> 128
		// ★ byte는 WinDef.h 에 typedef로 정의 된 unsigned char


		//0이 아닌 수는 true이니  128일 경우 1로 바꾸는 과정
		keyState[i] = key ? 1 : 0;


		int oldState = keyOldState[i]; //이전 누른 키 토글(on, off)값
		int state = keyState[i]; //현재 누른 키 토글(on, off)값

		//이전에 누르지 않았고 , 현재 눌렀음
		if (oldState == 0 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_DOWN;
		//이전에 눌렀고		 , 현재 누르지 않았음
		else if (oldState == 1 && state == 0)
			keyMap[i] = KEY_INPUT_STATUS_UP;
		//이전에 눌렀고		 , 현재도 눌렀음
		else if (oldState == 1 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_PRESS;
		//아무것도 입력 되지 않음
		else
			keyMap[i] = KEY_INPUT_STATUS_NONE;
	}

	//이 함수는 키가 눌려졌을 때(down)나 떨어졌을 때(up) 호출된다.

	//키가 눌렸을 때 실행되는 함수로서, 
	//간단히 매개변수의 해당하는 키의 버튼(눌렀는지 안눌렀는지)을 On off하여 위의 GetKeyboardState에서 이에 맞게 배열을 대입해준다, 

	//4가지 상태에 맞는 반환값을 반환한다 , 여기서는 사용하지 않았다

	short a = GetKeyState(65);

	if (a < 0) {
		int a = 0;
	}

}

Keyboard::Keyboard()
{
	//쓰레기값 처리
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}

Keyboard::~Keyboard()
{

}
