#include "../stdafx.h"
#include "../Manager/PlayerManager.h"
#include "../Geometry/ColorMesh.h"
#include "../Manager/EndAniManager.h"
#include "../Manager/TaskManager.h"
#include "../Manager/ImposterManager.h"
#include "../Manager/CrewManager.h"
#include "MatchingClient.h"

MatchingClient::MatchingClient()
{
	
}

MatchingClient::~MatchingClient()
{
}

void MatchingClient::StartTCP()
{
	init();
}

void MatchingClient::Connect()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	3.	������ ����(connect)
	//	a.	Ŭ���̾�Ʈ���� ������ ������� �������� �����û�� �ϴ� �Լ�
	/*	1 -���� �����ڵ� 	2 -�����Ϸ��� ������ �ּ� ����ü ����	3 -�ι�° �Ű������� ũ��	*/
	if (connect(socketValue, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		//���� ���� ��
		printf("connect() ����\n");
		closesocket(socketValue);
		WSACleanup();
		return;
	}
	else {
		//��Ŷ�� �������İ���
		//���� �������� ��
		printf("������ ������ �Ǿ���.\n");

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//������ ó�� ���ӽ� ���� ������ �޴´�
		char buff[1024] = { 0 };
		char resetBuff[1024] = { 0 };

		//[��ü�ο�], [��������], [���°�÷��̾���]
		Loby_Accept temp;

		recv(socketValue, buff, 1024, 0);
		memcpy(&temp, buff, sizeof(Loby_Accept));
		
		ClientData::instance->mTotalPlayer = temp.mTotalPlayer;
		ClientData::instance->mIsAdmin = temp.mIsAdmin;
		ClientData::instance->mPlayerNum = temp.mPlayerNum;
		ClientData::instance->mPlayerFirstPos = temp.mFirstPos;
		ClientData::instance->mPlayerFirstColorBody = temp.mColorBody;
		ClientData::instance->mPlayerFirstColorShadow = temp.mColorShadow;
		
		mIsConnect = true;
		int a = 0;
	}
}


void MatchingClient::Setting()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_LOBY: StartRecving();	break;

	case SCENE_INGAME_PLAY:	StartRecving_inGame(); break;

	case SCENE_INGAME_END:	StartRecving_end(); break;
		

	default: break;
	}

}


void MatchingClient::init()
{
	// ���ý� ����
	hMutex = CreateMutex(NULL, FALSE, NULL);	// ���� ���н� ����
	if (!hMutex)
	{
		printf("Mutex ����\n");
		CloseHandle(hMutex);
	}


	// ���� �ʱ�ȭ
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(1, 1), &wsd) != 0)	// ��� ���� ������ 1.1
	{
		printf("Winsock ����\n");
		WSACleanup();
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	1.	������ �����ϱ� ���� ������ ����ϱ����� �ڵ��� �޾ƿ���

	socketValue = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


	//	a.	�ڵ��� ���������� �޾ƿԴ��� Ȯ��
	if (socketValue == SOCKET_ERROR)
	{
		printf("socket() ����\n");
		closesocket(socketValue);
		WSACleanup();
		return;
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	2.	������ ��Ż�븦 �����ϱ� ���� �ּҸ� ����Ѵ�
	//		�׷��Ƿ� �ϴ� ���⼭�� ������ '����'�� �ּ� ������ ������ �ֱ� ���� ����ü(sockaddr_in) ����
	//	a.	����ü ä�� �ֱ�
	server.sin_family = AF_INET; // �ּ��� ü�谡 �������� AF_INET - IPV4
	server.sin_addr.s_addr = inet_addr(IP); // IP�ּҸ� ��Ʈ��ũ ����Ʈ ������ �޾ƿ���(�򿣵��) char���� int������ ��ȯ�Ѵ�
	server.sin_port = htons(PORT); // short�� ��Ʈ��ȣ�� ��Ʈ��ũ ����Ʈ ������ �޾ƿ´�

	mIsConnect = false;
}


void MatchingClient::recving()
{
	int ret_thread = 65535;


	// ������� ���� ���� ���ϴ� ���� �ƴϸ� �޴� �߿� ������ ����� ����ٰ� ���� ����
	while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
	{
		char buff[1024] = { 0 }; //������ ����
		char buff2[1024] = { 0 }; //�޴� ����

		Sleep(30);	// CPU ������ 100% ������


		//////////////////////////////////////////////////////////////////////////////////////////
		//�κ� ���¿� ��� ���� ��
		//////////////////////////////////////////////////////////////////////////////////////////
		if (ClientData::instance->mRequestGameStart == false) { //�� mIsGameStart �� EndManager���� �ٲ������

			int pNum = ClientData::instance->mPlayerNum;

			Loby_Player * tempData = nullptr;
			if (tempData == NULL) {

				tempData = new Loby_Player();
			}

			if (tempData != nullptr) {

				//�������� �����͸� ������!
				tempData->mSignal = 2;
				tempData->mPlayerNum = pNum;
				tempData->mPlayerArray[pNum].mExist = true;
				tempData->mPlayerArray[pNum].mIsAdmin = ClientData::instance->mIsAdmin;
				tempData->mPlayerArray[pNum].mIsRight = PlayerManager::Get()->GetMyIsRight();
				tempData->mPlayerArray[pNum].mAniName = PlayerManager::Get()->GetMyAniName();
				tempData->mPlayerArray[pNum].mPos = PlayerManager::Get()->GetMyTrans();
				tempData->mPlayerArray[pNum].mFrame = PlayerManager::Get()->GetMyFrame();
				


				//TODO �����ߴ��� ���ߴ��� �߰��ؾ���

				//���� �����͸� ������
				memcpy(buff, tempData, sizeof(Loby_Player));
				send(socketValue, buff, sizeof(Loby_Player), 0);


				// �������� �����͸� ����
				ret_thread = recv(socketValue, buff2, sizeof(Loby_Player), 0);
				// �������� �޴� �۾��� �� ��� �������� �� Ż�� //TODO���⿡ �� �б�;������
				if (ret_thread == INVALID_SOCKET || ret_thread == SOCKET_ERROR || SceneManager::Get()->GetScene() != SCENE_LOBY)	break;


				//�޾ƿ� ������ ó��
				memcpy(tempData, buff2, sizeof(Loby_Player));


				//��� �κ������ �ְ������
				if (tempData->mSignal == 22) {

					ClientData::instance->mIsAdmin = tempData->mPlayerArray[pNum].mIsAdmin;
					ClientData::instance->mTotalPlayer = tempData->mTotalPlayer;

					for (int index = 0; index < 4; index++) {

						if (tempData->mPlayerArray[index].mExist == true && tempData->mPlayerArray[index].mFrame < 1000) {

							ClientData::instance->mAnotherPlayer_Data[index] = tempData->mPlayerArray[index];
						}
					}
				}
				else if (tempData->mSignal == 222) {

					//������ ���۵Ǿ��ٰ� �����ؾ��ϰ�, ������������ �ƴ��� �޾ƿ;��Ѵ�!
					ClientData::instance->mIsGameStart = true;

					EndAniManager::Get()->SetIsStartChangeAni(true);
					SceneManager::Get()->SetNextScene(SCENE_INGAME_START);

					//���� ������������ �����ϰ� �������� ����Ʈ �޾ƿ���
					for (int index = 0; index < 4; index++) {

						ClientData::instance->mImposterList[index] = tempData->mImposterList[index];
					}
					ClientData::instance->mImImposter = ClientData::instance->mImposterList[pNum];

					int  a = 0;
				}
			}///if (tempData != nullptr) 
		}///if (ClientData::instance->mIsGameStart == false)
		//EndManager���� ���ۿ�û�� ������ �� ! [���� ���� ������]
		else {

			//���� ���� ��û�� �޾����� �ٽ� �⺻�� false�� �����!
			ClientData::instance->mRequestGameStart = false;


			//�ñ׳θ�  ������! - 3�� [ �������� ���ӽ��� ���������� true�� �϶�� ��]
			int tempSignal = 3; // �ñ׳��� 3 = ������ �����ߴ�
			memcpy(buff, &tempSignal, sizeof(int));
			send(socketValue, buff, sizeof(int), 0);
			

		}
		
	}

	// �۾��� ���� ������ ��ȿȭ��Ŵ
	WaitForSingleObject(hMutex, 100L);
	ret_thread = INVALID_SOCKET;
	ReleaseMutex(hMutex);

	return;

}



void MatchingClient::recving_inGame()
{


	int ret_thread = 65535;


	// ������� ���� ���� ���ϴ� ���� �ƴϸ� �޴� �߿� ������ ����� ����ٰ� ���� ����
	while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
	{
		char buff[1024] = { 0 }; //������ ����
		char buff2[1024] = { 0 }; //�޴� ����

		Sleep(30);	// CPU ������ 100% ������


			int pNum = ClientData::instance->mPlayerNum;

			sInGame_Play * tempData = nullptr;
			if (tempData == NULL) {

				tempData = new (std::nothrow) sInGame_Play();
			}

			if (tempData != nullptr) {


				////////////////////////////////////////////////////////////////////////////////////////////////
				//������ �����͸� ���� ������ �غ�
				tempData->mSignal = 4;
				tempData->mIsKill = ImposterManager::Get()->GetIsKill(); //�׿����� �޾ƿ�
				tempData->mPlayerArray[pNum].mKillNum_imposter = ImposterManager::Get()->GetPossibleKill(); //���� ���� �׿����� �����������н��Ǵ°Ű��� ����
				tempData->mPlayerArray[pNum].mExist = true;
				tempData->mPlayerArray[pNum].mCompleteTask = TaskManager::Get()->GetTotalCompleteTask();

				//���⼭ �⺻�������� ��ü���� �Ǻ�
				//�⺻ �����̸� [ ������ ���� ]
				if (PlayerManager::Get()->GetImGhost() == false) {
					tempData->mPlayerArray[pNum].mIsRight = PlayerManager::Get()->GetMyIsRight();
					tempData->mPlayerArray[pNum].mAniName = PlayerManager::Get()->GetMyAniName();
					tempData->mPlayerArray[pNum].mPos = PlayerManager::Get()->GetMyTrans();
					tempData->mPlayerArray[pNum].mFrame = PlayerManager::Get()->GetMyFrame();
					tempData->mPlayerArray[pNum].mPlayerWhere = PlayerManager::Get()->GetMyArea();


					tempData->mPlayerArray[pNum].mIsDieSecond = false;
				}
				//���ɻ����̸� ��뿡�� ��ü �����͸� �����ش�
				else {
					tempData->mPlayerArray[pNum].mIsRight = PlayerManager::Get()->GetDieBodyLook();
					tempData->mPlayerArray[pNum].mAniName = PlayerManager::Get()->GetDieBodyAniName();
					tempData->mPlayerArray[pNum].mPos = PlayerManager::Get()->GetDieBodyTrans();
					tempData->mPlayerArray[pNum].mFrame = PlayerManager::Get()->GetDieBodyFrame();
					tempData->mPlayerArray[pNum].mIsDieSecond = true;
				}

				
				////////////////////////////////////////////////////////////////////////////////////////////////
				//������ ������ ����
				memcpy(buff, tempData, sizeof(sInGame_Play));
				send(socketValue, buff, sizeof(sInGame_Play), 0);


				////////////////////////////////////////////////////////////////////////////////////////////////
				// �������� �����͸� ����
				ret_thread = recv(socketValue, buff2, sizeof(sInGame_Play), 0);
				// �������� �޴� �۾��� �� ��� �������� �� Ż�� //TODO���⿡ �� �б�;������
				if (ret_thread == INVALID_SOCKET || ret_thread == SOCKET_ERROR || SceneManager::Get()->GetScene() != SCENE_INGAME_PLAY)	break;


				

				////////////////////////////////////////////////////////////////////////////////////////////////
				//�޾ƿ� ������ ó��
				memcpy(tempData, buff2, sizeof(sInGame_Play));
				ClientData::instance->mIsGameEnd = tempData->mIsGameEnd; //���ӳ������� Ȯ��
				ClientData::instance->mTotalTaskPercent = tempData->mTotalComplete; //��� �÷��̾� �׽�ũ �Ϸ��� ����
				ImposterManager::Get()->SetIsKill(false); // ų �ʱ�ȭ TODO ų ���� �ٲܶ� �ð��� �ϱ�
				if (tempData->mIsDieFirst == true) {

					ClientData::instance->mImDie = true;
					CrewManager::Get()->SetWhoIsKill(tempData->mPlayerArray[pNum].mKillNum_crew);
					int a = 0;
				}
				
				if (tempData->mSignal == 44) {

					ClientData::instance->mAnotherPlayer_inGame[0] = tempData->mPlayerArray[0];
					ClientData::instance->mAnotherPlayer_inGame[1] = tempData->mPlayerArray[1];
					ClientData::instance->mAnotherPlayer_inGame[2] = tempData->mPlayerArray[2];
					ClientData::instance->mAnotherPlayer_inGame[3] = tempData->mPlayerArray[3];
				}

				//TODO �ñ׳� 55������ ������ �������°� ����
			}///if (tempData != nullptr) 

	}

	// �۾��� ���� ������ ��ȿȭ��Ŵ
	WaitForSingleObject(hMutex, 100L);
	ret_thread = INVALID_SOCKET;
	ReleaseMutex(hMutex);

	return;
}

void MatchingClient::recving_end()
{

	int ret_thread = 65535;


	// ������� ���� ���� ���ϴ� ���� �ƴϸ� �޴� �߿� ������ ����� ����ٰ� ���� ����
	while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
	{
		char buff[1024] = { 0 }; //������ ����
		char buff2[1024] = { 0 }; //�޴� ����

		Sleep(30);	// CPU ������ 100% ������

		////////////////////////////////////////////////////////////////////////////////////////////////
		//������ ������ ����
		//�ñ׳��� 5�̴� 
		int tempSignal = 5;
		memcpy(buff, &tempSignal, sizeof(int));
		send(socketValue, buff, sizeof(sInGame_Play), 0);


		//////////////////////////////////////////////////////////////////////////////////////////////////
		//// �������� �����͸� ����
		//ret_thread = recv(socketValue, buff2, sizeof(bool), 0);

		//// �������� �޴� �۾��� �� ��� �������� �� Ż�� //TODO���⿡ �� �б�;������
		//if (ret_thread == INVALID_SOCKET || ret_thread == SOCKET_ERROR)	break;


		//////////////////////////////////////////////////////////////////////////////////////////////////
		////�޾ƿ� ������ ó�� [���� �����ʹ� �ʱ�ȭ�϶�� bool ���̴�
		//bool tempResult = false;
		//memcpy(&tempResult, buff2, sizeof(bool));


		//�̰� �ѹ��� ������ �ȴ�!
		break;
	}

	// �۾��� ���� ������ ��ȿȭ��Ŵ
	WaitForSingleObject(hMutex, 100L);
	ret_thread = INVALID_SOCKET;
	ReleaseMutex(hMutex);

	return;
}
