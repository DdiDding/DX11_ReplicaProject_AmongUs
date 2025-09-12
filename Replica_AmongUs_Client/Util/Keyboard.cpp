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

	//ó��Ű�� �������� �ǹ̰� ������
	//Ű�� ������ 2��° �ݺ����� ȿ�����ִ� �κ�

	//1.ó�� ���� ��		-�ƹ��͵� ���°� ���������� �ƹ��͵� ����
	//2.������ ���� ��	-�ؿ��� ���� ���� ��� �迭�� ���� -> �Ŀ� �̰����� ���� Ű�� �������� �񱳸��ϴ� �κ�
	memcpy(keyOldState, keyState, sizeof(keyOldState));//�̰� ���ϴ°�¡

	//void ZeroMemory -   �޸𸮸� 0���� ä��
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));


	//256 ���� ���� Ű ���¸� ������ ���ۿ� �����ϴ� �Լ�. -> �׷��� 256ũ���� �迭�� ���� [�ٵ� ũ�Ⱑ �޶� ������ �ȳ�]
	//https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes Ű�ڵ� ǥ 256���� �´�
	GetKeyboardState(keyState);

	//DWORD - unsignd long
	for (DWORD i = 0; i < MAX_INPUT_KEY; i++)
	{



		//�� And������ ���� �ΰ����� ���´� 
		//1. 0b 0000 0000 [���� 128 �̸��� ��] - 0
		//2. 0b 1000 0000 [���� 128 �̻��� ��] - 128

		//�� 128�� �����ϱ�?  -  GetKeyboardState������ ���� Ű���� �迭�� ���� 128�̻��� ������ �ΰ�, ���������� �迭�� ���� 0���� �α⶧��
		//						�׷��� �ؿ��� 128�̸� 1�� ��ȯ�Ͽ� true�� ���� 0�� false�� �������ϴ�
		byte key = keyState[i] & 0x80;
		// �� 0x80 -> 0b 1000 0000 -> 128
		// �� byte�� WinDef.h �� typedef�� ���� �� unsigned char


		//0�� �ƴ� ���� true�̴�  128�� ��� 1�� �ٲٴ� ����
		keyState[i] = key ? 1 : 0;


		int oldState = keyOldState[i]; //���� ���� Ű ���(on, off)��
		int state = keyState[i]; //���� ���� Ű ���(on, off)��

		//������ ������ �ʾҰ� , ���� ������
		if (oldState == 0 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_DOWN;
		//������ ������		 , ���� ������ �ʾ���
		else if (oldState == 1 && state == 0)
			keyMap[i] = KEY_INPUT_STATUS_UP;
		//������ ������		 , ���絵 ������
		else if (oldState == 1 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_PRESS;
		//�ƹ��͵� �Է� ���� ����
		else
			keyMap[i] = KEY_INPUT_STATUS_NONE;
	}

	//�� �Լ��� Ű�� �������� ��(down)�� �������� ��(up) ȣ��ȴ�.

	//Ű�� ������ �� ����Ǵ� �Լ��μ�, 
	//������ �Ű������� �ش��ϴ� Ű�� ��ư(�������� �ȴ�������)�� On off�Ͽ� ���� GetKeyboardState���� �̿� �°� �迭�� �������ش�, 

	//4���� ���¿� �´� ��ȯ���� ��ȯ�Ѵ� , ���⼭�� ������� �ʾҴ�

	short a = GetKeyState(65);

	if (a < 0) {
		int a = 0;
	}

}

Keyboard::Keyboard()
{
	//�����Ⱚ ó��
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}

Keyboard::~Keyboard()
{

}
