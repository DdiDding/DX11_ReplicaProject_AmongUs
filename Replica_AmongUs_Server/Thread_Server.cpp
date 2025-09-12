#include <stdio.h>
#include <process.h>
#include <winsock.h>
#include <windows.h>

#include "stdafx.h"
#include "Structs.h"

#pragma comment(lib, "wsock32.lib")	
#define PORT 1313			// �����Ʈ�� 5000
#define MAX_CLIENT 4	// �ִ� ��� �ο� �� 5��
#define ALLOW 65535			// �ִ� ���� ���� ���� ��ȣ 65535

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��� ������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recv_client(void *ns);	// ������ �Լ� ������ Ÿ��

int client_num = 0;			// ���� Ƚ�� (Ŭ���̾�Ʈ ����)
int seat = 0;				// Ŭ���Ʈ ��ȣ

int client_sock[ALLOW];		// client_sock (Ŭ���̾�Ʈ Welcome Socket)
HANDLE hMutex = 0;			// ���ý�

char resetBuff[1024] = { 0 };


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//���� ������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isPlayerExist[4] = { 0,0,0,0 }; //�� �ε����� �÷��̾ �ִ��� ������ true ������ false
int player_num = 0; //�÷��̾��� �ѹ�(���� ������� 0 ������ ����)
int totalPlayer = 0;
bool isAdmin = true; //�÷��̾ �������� �ƴ���
bool isGameStart = false; //������ �����ϴ� �ƴ��� [LOBY���� GAME START��]
bool isImposter[4] = { 
	false,false,false,false
}; //�� �÷��̾������������ �ƴ���
int whoIsDie = -1; //���� ��"��"����, 0�̻��̸� ���� �����Ŵ� ����
int whoIsKill = -1; //���� ��"��"����

int imposterNum = 0; //�������ʹ� �������
int crewNum = 0; //ũ����� �������

int totalTaskNum;// �׽�ũ�� �� ����

//�κ� ���� position �� �ε����� �� �÷��̾��ȣ��
D3DXVECTOR2 firstPos[4] = {
	D3DXVECTOR2(950,1135),
	D3DXVECTOR2(1000,1150),
	D3DXVECTOR2(1050,1165),
	D3DXVECTOR2(1100,1180)
};
//�÷��̾� ������ ����������
PlayerColors firstColor[9] = {
	PlayerColors(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.6f, 0.0f, 0.0f, 1.0f)),
	PlayerColors(D3DXVECTOR4(0.0f, 0.5f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.35f, 0.0f, 1.0f)),
	PlayerColors(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.6f, 1.0f)),
	PlayerColors(D3DXVECTOR4(0.34f, 0.34f, 0.34f, 1.0f), D3DXVECTOR4(0.101f, 0.101f, 0.101f, 1.0f)),
	PlayerColors(D3DXVECTOR4(0.466f, 0.0f, 0.931f, 1.0f), D3DXVECTOR4(0.196f, 0.0f, 0.354f, 1.0f)),
	PlayerColors(D3DXVECTOR4(0.647f, 0.376f, 0, 1.0f), D3DXVECTOR4(0.337f, 0.196f, 0, 1.0f)),
	PlayerColors(D3DXVECTOR4(1, 0.294f, 0.811f, 1.0f), D3DXVECTOR4(0.674f, 0.227f, 0.552f, 1.0f)),
	PlayerColors(D3DXVECTOR4(1, 0.517f, 0, 1.0f), D3DXVECTOR4(0.631f, 0.294f, 0, 1.0f)),
	PlayerColors(D3DXVECTOR4(1, 1, 0, 1.0f), D3DXVECTOR4(0.803f, 0.643f, 0, 1.0f))
};
//�κ񿡼��� ��� �÷��̾��� �����͸� ����������
Loby_Player * mPlayerData = new Loby_Player();


sInGame_Play * mPlayerData_inGame = new sInGame_Play();

int isGameEnd = 0; //������ ��������! -1�̸� ������ 0�̸� ���� 1�̸� ũ���

int main()
{


	mPlayerData->mPlayerArray[0].mExist = false;
	mPlayerData->mPlayerArray[1].mExist = false;
	mPlayerData->mPlayerArray[2].mExist = false;
	mPlayerData->mPlayerArray[3].mExist = false;



	printf("+---------------------------+\n");
	printf("+ ���� �غ�                  +\n");
	printf("+---------------------------+\n");

	// Listen ���� ����
	int s, addrsize, ret;
	sockaddr_in server, client;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//winsock �ʱ�ȭ
	///////////////////////////////////////////////////////////////////////////////////////////////
	{
		// ���ý� ����
		hMutex = CreateMutex(NULL, FALSE, NULL);	// ���� ���н� ����
		if (!hMutex)
		{
			printf("Mutex ����\n");
			CloseHandle(hMutex);
			return 1;
		}

		// ���� �ʱ�ȭ
		WSADATA wsd;
		if (WSAStartup(MAKEWORD(1, 1), &wsd) != 0)	// ��� ���� ������ 1.1
		{
			printf("Winsock ����\n");
			WSACleanup();
			return 1;

		}

		

		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == SOCKET_ERROR)
		{
			printf("socket() ����\n");
			closesocket(s);
			WSACleanup();
			return 1;
		}

		server.sin_addr.s_addr = htonl(INADDR_ANY);
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);

		// Bind �ϱ�
		if (bind(s, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
		{
			printf("bind() ����\n");
			closesocket(s);
			WSACleanup();
			return 1;

		}

	}


	printf("+---------------------------+\n");
	printf("+ ���� ����                  +\n");
	printf("+---------------------------+\n");


	///////////////////////////////////////////////////////////////////////////////////////////////
	//���� ��⿭�� �����Ѵ� - listen
	///////////////////////////////////////////////////////////////////////////////////////////////
	//�Ű����� 1 - �ڽ��� ���ϰ�ü	//�Ű����� 2 - �����⿭�� ũ��?
	listen(s,10);
	addrsize = sizeof(client);

	// ������� ������ ��ٸ��ϴ�.
	while(1)
	{
		// Blocking ������� Client �� ��ٸ��ϴ�.
		client_sock[seat] = accept(s, (sockaddr*)&client, &addrsize);

		// accept ��(�߿�, client_num �� accept() �Լ� ������ �� ���Ҽ� �����Ƿ�
		// MAX_CLIENT ���޽ö� ���� accept() �� ���� �߻� ���ɼ� ����
		if(client_num < MAX_CLIENT)		// ���� ���� �ϱ�
		{

			if(client_sock[seat] != INVALID_SOCKET || client_sock[seat] != SOCKET_ERROR){}
				_beginthread(recv_client, 0, &client_sock[seat]);
				Sleep(10);
				printf("%d�� �÷��̾� %s:%d ���� �����Ͽ����ϴ�.\n\n", seat, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
				
		}

		else	// ���� ����.
		{
			addrsize = sizeof(client);
			if (client_sock[seat] == INVALID_SOCKET)
			{
				printf("accept() ����\n");
				closesocket(client_sock[seat]);
				closesocket(s);
				WSACleanup();
				return 1;
			}

			char welcome_full[] = "����á���ϴ�.\n";
			ret = send(client_sock[seat], welcome_full, sizeof(welcome_full), 0);
			closesocket(client_sock[seat]);

			// �޽��� ������ �ٷ� ���´�.

		}
	}
	
	return 0;

}

void recv_client(void *ns)
{

	client_num++;				// Ŭ���̾�Ʈ ���� ����
	seat++;						// Ŭ���̾�Ʈ ��ȣ ����
	printf("���� %d�� ����\n", MAX_CLIENT - client_num);		// ������ �Ǵ�


	int ret;
	char buff[1024] = {0};
	char resetBuff[1024] = {0};
	int tempPlayerNum = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//1. ó�� ���ӽÿ� Ŭ���̾�Ʈ���� �÷��̾��� �ѹ��� ����
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WaitForSingleObject(hMutex, INFINITE);

	//������ �� ���� �κ�
	totalPlayer++; //��ü�ο� ����

	for (int index = 0; index < 4; index++) {

		if (isPlayerExist[index] == false) {

			tempPlayerNum = index;
			isPlayerExist[index] = true;
			break;
		}
	}

	Loby_Accept tempLoby_accept = Loby_Accept(totalPlayer, isAdmin, tempPlayerNum, firstPos[tempPlayerNum],firstColor[tempPlayerNum].mColor_body, firstColor[tempPlayerNum].mColor_body_shadow);


	//1. ������ ����
	memcpy(buff, &tempLoby_accept, sizeof(Loby_Accept));
	ret = send(*(SOCKET*)ns, buff, sizeof(Loby_Accept), 0);		// ����
	memcpy(buff, resetBuff, sizeof(buff));


	//������ �� ���� �κ�
	isAdmin = false; //������ ������ ����

	ReleaseMutex(hMutex);

	//printf("%d�� �÷��̾� �����Ͽ����ϴ�. \n", tempPlayerNum);		// ������ �Ǵ�
	printf("���� �� �÷��̾� ���� %d�� �Դϴ�.\n", totalPlayer);		// ������ �Ǵ�


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//2. ��� �����͸� �ְ�޴� �κ�
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while(ret != SOCKET_ERROR || ret != INVALID_SOCKET)
	{
		char buff2[1024] = { 0 };

		//*******************************************
		// Ŭ���̾�Ʈ�� �޽����� buff2�� �޾Ƽ� � �б����� Ȯ��
		ret = recv(*(SOCKET*)ns, buff2, 1024, 0);
		int result = -1; //� Scene�ΰ�
		memcpy(&result, buff2, sizeof(int));
	
		//*******************************************
		//�κ���¿��� �����޾��� ��
		if (result == 2) {

			//printf("+ �κ�������");
			//Ŭ���̾�Ʈ���Թ޾ƿ� ������ = tempData
			Loby_Player * tempData = new Loby_Player();
			memcpy(tempData, buff2, sizeof(Loby_Player));

			//���� ó��
			WaitForSingleObject(hMutex, INFINITE);

			//���� �޾ƿ� �÷��̾��� �ѹ�
			int tempIndex = tempData->mPlayerNum;

			//���� ���� ����
			bool tempAdmin = false;
			//�̹� �������� Ȯ���Ѵ�
			{
				if (tempData->mPlayerArray[tempIndex].mIsAdmin == true) {
					tempAdmin = true;
				}
				else {

					//���� �����̾ƴϿ��µ� �ٲ� ���� �ִ��� Ȯ��
					if (mPlayerData->mPlayerArray[tempIndex].mIsAdmin == true) {
						tempAdmin = true;
					}
				}
			}


			//todo���⼭ ��ŸƮ �����ؼ� �ñ׳δٸ����ϰ� �����϶�� �˸��e����~
			//������ ������Ʈ
			if (isGameStart == false) {
				mPlayerData->mSignal = 22;
			}
			else {
				mPlayerData->mSignal = 222;
			}

			for (int i = 0; i < 4; i++) {

				if (mPlayerData->mPlayerArray[i].mExist == false) {

					mPlayerData->mPlayerArray[i] = LobyPlayerSub();
				}
			}

			mPlayerData->mIsStart = isGameStart;
			mPlayerData->mPlayerArray[tempIndex] = tempData->mPlayerArray[tempIndex];
			mPlayerData->mPlayerArray[tempIndex].mIsAdmin = tempAdmin;
			mPlayerData->mPlayerArray[tempIndex].mExist = true;
			mPlayerData->mTotalPlayer = totalPlayer;

			//�������� ����Ʈ ���
			for (int index = 0;index < 4; index++)
			{
				mPlayerData->mImposterList[index] = isImposter[index];
			}

			memcpy(buff2, mPlayerData, sizeof(Loby_Player));

			send(*(SOCKET*)ns, buff2, sizeof(Loby_Player), 0);

			ReleaseMutex(hMutex);


		}
		//������ ���۹�ư�� ��������
		//�̰��� �ѹ��� ���ü��ִ°���[���常]
		else if (result == 3) {
			
			//���µ����Ϳ��� �����������ʹ� �߿����������Ƿ� �ٷ� ������ �����ؼ� �����Ѵ�
			
			WaitForSingleObject(hMutex, INFINITE);

			//���ӽ����ߴٴ� �������� ����
			isGameStart = true; 

			//�������ͷ������� �����ϴ� ���� - ���»�� ����ó���ؾ���
			int imposterIndex = 0;
			srand((UINT)time(NULL));

			//�������� ����Ұ��� [3�����ϸ� 1��, 4���̸� 2��]
			int tempImPosterNum = 0;


			if (totalPlayer < 4) tempImPosterNum = 1;
			else if (totalPlayer == 4)tempImPosterNum = 2;
			printf("������ �����մϴ�.\n");
			printf("���ο� %d������ �������ʹ� %d���Դϴ�", totalPlayer, tempImPosterNum);

			////�������� ����ŭ �ݺ�
			//for (int impoCnt = 0; impoCnt < tempImPosterNum; impoCnt++) {

			//	do {
			//		imposterIndex = rand() % 4;
			//	} 
			//	//�÷��̾ �����ؾ��ϰ�, �̹� �������Ͱ� �ƴϾ���Ѵ�
			//	while (isPlayerExist[imposterIndex] == false && isImposter[imposterIndex] == false);

			//	isImposter[imposterIndex] = true;
			//}

			isImposter[0] = true;
			isImposter[1] = true;

			crewNum = totalPlayer - tempImPosterNum;

			//task�� ����� ����
			totalTaskNum = 3 * crewNum;

			ReleaseMutex(hMutex);
		}
		else if (result == 4) {

			//Ŭ���̾�Ʈ���Թ޾ƿ� ������ = tempData
			//���� �޾ƿ� �÷��̾��� �ѹ� -> tempPlayerNum

			sInGame_Play * tempData = new sInGame_Play();
			memcpy(tempData, buff2, sizeof(sInGame_Play));

			//���� ó��
			WaitForSingleObject(hMutex, INFINITE);

			//////////////////////////////////////////////////////////////////////////////////////////
			//1. �ϴ� �÷��̾���� �Ű�~
			mPlayerData_inGame->mPlayerArray[tempPlayerNum] = tempData->mPlayerArray[tempPlayerNum];


			//////////////////////////////////////////////////////////////////////////////////////////
			//���� �׾����� ���׾����� ���
			if (whoIsDie == tempPlayerNum) {

				mPlayerData_inGame->mIsDieFirst = true;
				mPlayerData_inGame->mPlayerArray[tempPlayerNum].mKillNum_crew = whoIsKill;
				whoIsDie = -1; //�� �ʱ�ȭ
				whoIsKill = -1;
			}
			else {
				mPlayerData_inGame->mIsDieFirst = false;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//2. ��ü���� �׽�ũ ������ ���
			int tempTaskPercent = 0;
			{
				int tempTaskCnt = 0; //�� �׽�ũ �� ����
				int tempAlive = 0; //����� ��� ��

				for (int index = 0; index < 4; index++) {

					//�ϴ� �����ؾ��ϰ� && �������Ͱ� �ƴϸ� ����Ѵ�
					if (mPlayerData_inGame->mPlayerArray[index].mExist == true  && isImposter[index] == false) {

						tempAlive++;
						tempTaskCnt += mPlayerData_inGame->mPlayerArray[index].mCompleteTask;
					}
				}
				//float tempResult = (float)tempTaskCnt / (3 * tempAlive);
				float tempResult = (float)tempTaskCnt / totalTaskNum;
				tempTaskPercent = (int)(tempResult * 100);
			}
			if (tempTaskPercent < 0) tempTaskPercent = 0;

			if (tempTaskPercent == 100) {

				isGameEnd = 1;
				int a = 0;
			}
			mPlayerData_inGame->mTotalComplete = tempTaskPercent;
			mPlayerData_inGame->mSignal = 44;


			//////////////////////////////////////////////////////////////////////////////////////////
			//3. Kill ���� ��� - tempData�� �´�
			//�������� �׿�������.
			if (tempData->mIsKill == true) {

				whoIsDie = mPlayerData_inGame->mPlayerArray[tempPlayerNum].mKillNum_imposter;
				whoIsKill = tempPlayerNum;

				crewNum--;
			}

			if (crewNum == 0) {
				isGameEnd = -1;
			}

			//���⼭ ���ӳ����°� Ȯ�� �׷��� ���� ũ�� �Ѵ� Ȯ�ΰ��� 
			mPlayerData_inGame->mIsGameEnd = isGameEnd;


			//Ŭ���̾�Ʈ���� ������ ����
			memcpy(buff2, mPlayerData_inGame, sizeof(sInGame_Play));
			send(*(SOCKET*)ns, buff2, sizeof(sInGame_Play), 0);


			ReleaseMutex(hMutex);

			int a = 0;
		}
		////////////////////////////////////////////////////
		//�ʱ�ȭ �κ�
		else if (result == 5) {

		isGameStart = false;

		whoIsDie = -1;
		whoIsKill = -1;

		mPlayerData = new Loby_Player();
		mPlayerData_inGame = new sInGame_Play();

		isGameEnd = 0;

		isImposter[0] = false;
		isImposter[1] = false;
		isImposter[2] = false;
		isImposter[3] = false;

		//�ʱ�ȭ ����
		int a = 0;
		}

	}///while
	////////////////////////////////////////////////////////////////////
	// ���ӵ� ������ ������ ���� ��������
	WaitForSingleObject(hMutex,INFINITE);

	isPlayerExist[tempPlayerNum] = false;
	totalPlayer--;

	if (mPlayerData->mPlayerArray[tempPlayerNum].mIsAdmin == true) {

		bool isGiveAdmin = false; //��������� ������������� true�� �ٸ��÷��̾�� �Ѿ���̰� false�� �ƹ������ �ʱ�ȭ�Ȱ�

		//�ٸ� �÷��̾ �˻��ؼ� ��������� �Ѱ��ش�
		for (int index = 0; index < 4; index++) {

			if (isPlayerExist[index] == true) {
				mPlayerData->mPlayerArray[index].mIsAdmin = true;
				printf("\n%d�� �÷��̾�� ��������� �Ѿ���ϴ�. \n", index + 1);
				isGiveAdmin = true;
				break;
			}
		}
		
		if (isGiveAdmin == false) {
			isAdmin = true;
			isGameStart = false; //���ӽ��� �ʱ�ȭ


			printf("\nó�� ������ �÷��̾ �����Դϴ�.\n");
		}
	}

	//���� �÷��̾� �ڸ� �ʱ�ȭ
	mPlayerData->mPlayerArray[tempPlayerNum] = LobyPlayerSub();
	mPlayerData_inGame->mPlayerArray[tempPlayerNum] = IngamePlayerSub();

	client_num--;
	printf("\n%d�� �÷��̾� ��������\n", tempPlayerNum + 1);
	ReleaseMutex(hMutex);


	closesocket(*(int*)ns);
	
	return;
}