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
	//	3.	서버와 연결(connect)
	//	a.	클라이언트에서 소켓을 기반으로 서버에게 연결요청을 하는 함수
	/*	1 -나의 소켓핸들 	2 -연결하려는 서버의 주소 구조체 정보	3 -두번째 매개변수의 크기	*/
	if (connect(socketValue, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		//실패 했을 때
		printf("connect() 오류\n");
		closesocket(socketValue);
		WSACleanup();
		return;
	}
	else {
		//패킷은 스텍형식같다
		//연결 성공했을 때
		printf("서버와 연결이 되었음.\n");

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//서버에 처음 접속시 받을 데이터 받는당
		char buff[1024] = { 0 };
		char resetBuff[1024] = { 0 };

		//[전체인원], [방장인지], [몇번째플레이언지]
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
	// 뮤택스 생성
	hMutex = CreateMutex(NULL, FALSE, NULL);	// 생성 실패시 오류
	if (!hMutex)
	{
		printf("Mutex 오류\n");
		CloseHandle(hMutex);
	}


	// 윈속 초기화
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(1, 1), &wsd) != 0)	// 사용 소켓 버전은 1.1
	{
		printf("Winsock 오류\n");
		WSACleanup();
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	1.	서버로 접속하기 위한 소켓을 사용하기위해 핸들을 받아오기

	socketValue = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


	//	a.	핸들을 성공적으로 받아왔는지 확인
	if (socketValue == SOCKET_ERROR)
	{
		printf("socket() 오류\n");
		closesocket(socketValue);
		WSACleanup();
		return;
	}



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	2.	소켓은 통신상대를 지정하기 위해 주소를 사용한다
	//		그러므로 일단 여기서는 연결할 '서버'의 주소 정보를 가지고 있기 위한 구조체(sockaddr_in) 세팅
	//	a.	구조체 채워 넣기
	server.sin_family = AF_INET; // 주소의 체계가 무엇인지 AF_INET - IPV4
	server.sin_addr.s_addr = inet_addr(IP); // IP주소를 네트워크 바이트 순서로 받아오고(빅엔디안) char형을 int형으로 변환한다
	server.sin_port = htons(PORT); // short형 포트번호를 네트워크 바이트 순서로 받아온다

	mIsConnect = false;
}


void MatchingClient::recving()
{
	int ret_thread = 65535;


	// 스레드용 리턴 값이 원하는 값이 아니면 받는 중에 서버와 통신이 끊겼다고 보고 나감
	while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
	{
		char buff[1024] = { 0 }; //보내는 버퍼
		char buff2[1024] = { 0 }; //받는 버퍼

		Sleep(30);	// CPU 점유률 100% 방지용


		//////////////////////////////////////////////////////////////////////////////////////////
		//로비 상태에 계속 있을 때
		//////////////////////////////////////////////////////////////////////////////////////////
		if (ClientData::instance->mRequestGameStart == false) { //이 mIsGameStart 은 EndManager에서 바뀌어진다

			int pNum = ClientData::instance->mPlayerNum;

			Loby_Player * tempData = nullptr;
			if (tempData == NULL) {

				tempData = new Loby_Player();
			}

			if (tempData != nullptr) {

				//서버에게 데이터를 보낸다!
				tempData->mSignal = 2;
				tempData->mPlayerNum = pNum;
				tempData->mPlayerArray[pNum].mExist = true;
				tempData->mPlayerArray[pNum].mIsAdmin = ClientData::instance->mIsAdmin;
				tempData->mPlayerArray[pNum].mIsRight = PlayerManager::Get()->GetMyIsRight();
				tempData->mPlayerArray[pNum].mAniName = PlayerManager::Get()->GetMyAniName();
				tempData->mPlayerArray[pNum].mPos = PlayerManager::Get()->GetMyTrans();
				tempData->mPlayerArray[pNum].mFrame = PlayerManager::Get()->GetMyFrame();
				


				//TODO 시작했는지 안했는지 추가해야함

				//나의 데이터를 보내고
				memcpy(buff, tempData, sizeof(Loby_Player));
				send(socketValue, buff, sizeof(Loby_Player), 0);


				// 서버에서 데이터를 받음
				ret_thread = recv(socketValue, buff2, sizeof(Loby_Player), 0);
				// 서버에서 받는 작업을 한 결과 비정상일 때 탈출 //TODO여기에 씬 분기;나누기
				if (ret_thread == INVALID_SOCKET || ret_thread == SOCKET_ERROR || SceneManager::Get()->GetScene() != SCENE_LOBY)	break;


				//받아온 데이터 처리
				memcpy(tempData, buff2, sizeof(Loby_Player));


				//계속 로비씬에서 주고받을때
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

					//게임이 시작되었다고 설정해야하고, 임포스터인지 아닌지 받아와야한다!
					ClientData::instance->mIsGameStart = true;

					EndAniManager::Get()->SetIsStartChangeAni(true);
					SceneManager::Get()->SetNextScene(SCENE_INGAME_START);

					//내가 임포스터인지 세팅하고 임포스터 리스트 받아오기
					for (int index = 0; index < 4; index++) {

						ClientData::instance->mImposterList[index] = tempData->mImposterList[index];
					}
					ClientData::instance->mImImposter = ClientData::instance->mImposterList[pNum];

					int  a = 0;
				}
			}///if (tempData != nullptr) 
		}///if (ClientData::instance->mIsGameStart == false)
		//EndManager에서 시작요청이 생겼을 때 ! [게임 시작 됬을때]
		else {

			//게임 시작 요청을 받았으니 다시 기본값 false로 만든다!
			ClientData::instance->mRequestGameStart = false;


			//시그널만  보낸다! - 3번 [ 서버에서 게임시작 전역변수를 true로 하라는 뜻]
			int tempSignal = 3; // 시그널이 3 = 게임을 시작했다
			memcpy(buff, &tempSignal, sizeof(int));
			send(socketValue, buff, sizeof(int), 0);
			

		}
		
	}

	// 작업이 끝난 소켓을 무효화시킴
	WaitForSingleObject(hMutex, 100L);
	ret_thread = INVALID_SOCKET;
	ReleaseMutex(hMutex);

	return;

}



void MatchingClient::recving_inGame()
{


	int ret_thread = 65535;


	// 스레드용 리턴 값이 원하는 값이 아니면 받는 중에 서버와 통신이 끊겼다고 보고 나감
	while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
	{
		char buff[1024] = { 0 }; //보내는 버퍼
		char buff2[1024] = { 0 }; //받는 버퍼

		Sleep(30);	// CPU 점유률 100% 방지용


			int pNum = ClientData::instance->mPlayerNum;

			sInGame_Play * tempData = nullptr;
			if (tempData == NULL) {

				tempData = new (std::nothrow) sInGame_Play();
			}

			if (tempData != nullptr) {


				////////////////////////////////////////////////////////////////////////////////////////////////
				//서버에 데이터를 보낼 데이터 준비
				tempData->mSignal = 4;
				tempData->mIsKill = ImposterManager::Get()->GetIsKill(); //죽였는지 받아옴
				tempData->mPlayerArray[pNum].mKillNum_imposter = ImposterManager::Get()->GetPossibleKill(); //내가 누굴 죽였는지 ㅋㅋ싸이콥패스되는거같다 ㅅㅂ
				tempData->mPlayerArray[pNum].mExist = true;
				tempData->mPlayerArray[pNum].mCompleteTask = TaskManager::Get()->GetTotalCompleteTask();

				//여기서 기본상태인지 시체인지 판별
				//기본 상태이면 [ 안죽은 상태 ]
				if (PlayerManager::Get()->GetImGhost() == false) {
					tempData->mPlayerArray[pNum].mIsRight = PlayerManager::Get()->GetMyIsRight();
					tempData->mPlayerArray[pNum].mAniName = PlayerManager::Get()->GetMyAniName();
					tempData->mPlayerArray[pNum].mPos = PlayerManager::Get()->GetMyTrans();
					tempData->mPlayerArray[pNum].mFrame = PlayerManager::Get()->GetMyFrame();
					tempData->mPlayerArray[pNum].mPlayerWhere = PlayerManager::Get()->GetMyArea();


					tempData->mPlayerArray[pNum].mIsDieSecond = false;
				}
				//유령상태이면 상대에겐 시체 데이터를 보내준다
				else {
					tempData->mPlayerArray[pNum].mIsRight = PlayerManager::Get()->GetDieBodyLook();
					tempData->mPlayerArray[pNum].mAniName = PlayerManager::Get()->GetDieBodyAniName();
					tempData->mPlayerArray[pNum].mPos = PlayerManager::Get()->GetDieBodyTrans();
					tempData->mPlayerArray[pNum].mFrame = PlayerManager::Get()->GetDieBodyFrame();
					tempData->mPlayerArray[pNum].mIsDieSecond = true;
				}

				
				////////////////////////////////////////////////////////////////////////////////////////////////
				//서버에 데이터 전송
				memcpy(buff, tempData, sizeof(sInGame_Play));
				send(socketValue, buff, sizeof(sInGame_Play), 0);


				////////////////////////////////////////////////////////////////////////////////////////////////
				// 서버에서 데이터를 받음
				ret_thread = recv(socketValue, buff2, sizeof(sInGame_Play), 0);
				// 서버에서 받는 작업을 한 결과 비정상일 때 탈출 //TODO여기에 씬 분기;나누기
				if (ret_thread == INVALID_SOCKET || ret_thread == SOCKET_ERROR || SceneManager::Get()->GetScene() != SCENE_INGAME_PLAY)	break;


				

				////////////////////////////////////////////////////////////////////////////////////////////////
				//받아온 데이터 처리
				memcpy(tempData, buff2, sizeof(sInGame_Play));
				ClientData::instance->mIsGameEnd = tempData->mIsGameEnd; //게임끝났는지 확인
				ClientData::instance->mTotalTaskPercent = tempData->mTotalComplete; //모든 플레이어 테스크 완료율 세팅
				ImposterManager::Get()->SetIsKill(false); // 킬 초기화 TODO 킬 변수 바꿀때 시간초 하기
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

				//TODO 시그널 55정도로 게임이 끝낫따는걸 받음
			}///if (tempData != nullptr) 

	}

	// 작업이 끝난 소켓을 무효화시킴
	WaitForSingleObject(hMutex, 100L);
	ret_thread = INVALID_SOCKET;
	ReleaseMutex(hMutex);

	return;
}

void MatchingClient::recving_end()
{

	int ret_thread = 65535;


	// 스레드용 리턴 값이 원하는 값이 아니면 받는 중에 서버와 통신이 끊겼다고 보고 나감
	while (ret_thread != INVALID_SOCKET || ret_thread != SOCKET_ERROR)
	{
		char buff[1024] = { 0 }; //보내는 버퍼
		char buff2[1024] = { 0 }; //받는 버퍼

		Sleep(30);	// CPU 점유률 100% 방지용

		////////////////////////////////////////////////////////////////////////////////////////////////
		//서버에 데이터 전송
		//시그널이 5이다 
		int tempSignal = 5;
		memcpy(buff, &tempSignal, sizeof(int));
		send(socketValue, buff, sizeof(sInGame_Play), 0);


		//////////////////////////////////////////////////////////////////////////////////////////////////
		//// 서버에서 데이터를 받음
		//ret_thread = recv(socketValue, buff2, sizeof(bool), 0);

		//// 서버에서 받는 작업을 한 결과 비정상일 때 탈출 //TODO여기에 씬 분기;나누기
		//if (ret_thread == INVALID_SOCKET || ret_thread == SOCKET_ERROR)	break;


		//////////////////////////////////////////////////////////////////////////////////////////////////
		////받아온 데이터 처리 [받은 데이터는 초기화하라는 bool 형이다
		//bool tempResult = false;
		//memcpy(&tempResult, buff2, sizeof(bool));


		//이건 한번만 받으면 된다!
		break;
	}

	// 작업이 끝난 소켓을 무효화시킴
	WaitForSingleObject(hMutex, 100L);
	ret_thread = INVALID_SOCKET;
	ReleaseMutex(hMutex);

	return;
}
