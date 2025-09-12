#include <stdio.h>
#include <process.h>
#include <winsock.h>
#include <windows.h>

#include "stdafx.h"
#include "Structs.h"

#pragma comment(lib, "wsock32.lib")	
#define PORT 1313			// 사용포트는 5000
#define MAX_CLIENT 4	// 최대 허용 인원 수 5개
#define ALLOW 65535			// 최대 생성 가능 소켓 번호 65535

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//통신 데이터
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void recv_client(void *ns);	// 스레드 함수 프로토 타입

int client_num = 0;			// 점유 횟수 (클라이언트 갯수)
int seat = 0;				// 클라언트 번호

int client_sock[ALLOW];		// client_sock (클라이언트 Welcome Socket)
HANDLE hMutex = 0;			// 뮤택스

char resetBuff[1024] = { 0 };


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//게임 데이터
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isPlayerExist[4] = { 0,0,0,0 }; //각 인덱스의 플레이어가 있는지 있으면 true 없으면 false
int player_num = 0; //플레이어의 넘버(들어온 순서대로 0 번부터 시작)
int totalPlayer = 0;
bool isAdmin = true; //플레이어가 방장인지 아닌지
bool isGameStart = false; //게임이 시작하는 아닌지 [LOBY에서 GAME START로]
bool isImposter[4] = { 
	false,false,false,false
}; //각 플레이어가임포스터인지 아닌지
int whoIsDie = -1; //누가 죽"엇"는지, 0이상이면 누가 죽은거다 ㅋㅋ
int whoIsKill = -1; //누가 죽"였"는지

int imposterNum = 0; //임포스터는 몇명인지
int crewNum = 0; //크루원은 몇명인지

int totalTaskNum;// 테스크의 총 개수

//로비에 최초 position 각 인덱스가 각 플레이어번호다
D3DXVECTOR2 firstPos[4] = {
	D3DXVECTOR2(950,1135),
	D3DXVECTOR2(1000,1150),
	D3DXVECTOR2(1050,1165),
	D3DXVECTOR2(1100,1180)
};
//플레이어 색상을 가지고있음
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
//로비에서의 모든 플레이어의 데이터를 가지고있음
Loby_Player * mPlayerData = new Loby_Player();


sInGame_Play * mPlayerData_inGame = new sInGame_Play();

int isGameEnd = 0; //게임이 끝낫는지! -1이면 임포승 0이면 정상 1이면 크루승

int main()
{


	mPlayerData->mPlayerArray[0].mExist = false;
	mPlayerData->mPlayerArray[1].mExist = false;
	mPlayerData->mPlayerArray[2].mExist = false;
	mPlayerData->mPlayerArray[3].mExist = false;



	printf("+---------------------------+\n");
	printf("+ 서버 준비                  +\n");
	printf("+---------------------------+\n");

	// Listen 소켓 생성
	int s, addrsize, ret;
	sockaddr_in server, client;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//winsock 초기화
	///////////////////////////////////////////////////////////////////////////////////////////////
	{
		// 뮤택스 생성
		hMutex = CreateMutex(NULL, FALSE, NULL);	// 생성 실패시 오류
		if (!hMutex)
		{
			printf("Mutex 오류\n");
			CloseHandle(hMutex);
			return 1;
		}

		// 윈속 초기화
		WSADATA wsd;
		if (WSAStartup(MAKEWORD(1, 1), &wsd) != 0)	// 사용 소켓 버전은 1.1
		{
			printf("Winsock 오류\n");
			WSACleanup();
			return 1;

		}

		

		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == SOCKET_ERROR)
		{
			printf("socket() 오류\n");
			closesocket(s);
			WSACleanup();
			return 1;
		}

		server.sin_addr.s_addr = htonl(INADDR_ANY);
		server.sin_family = AF_INET;
		server.sin_port = htons(PORT);

		// Bind 하기
		if (bind(s, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
		{
			printf("bind() 오류\n");
			closesocket(s);
			WSACleanup();
			return 1;

		}

	}


	printf("+---------------------------+\n");
	printf("+ 서버 시작                  +\n");
	printf("+---------------------------+\n");


	///////////////////////////////////////////////////////////////////////////////////////////////
	//연결 대기열을 생성한다 - listen
	///////////////////////////////////////////////////////////////////////////////////////////////
	//매개변수 1 - 자신의 소켓객체	//매개변수 2 - 연결대기열의 크기?
	listen(s,10);
	addrsize = sizeof(client);

	// 사용자의 접속을 기다립니다.
	while(1)
	{
		// Blocking 방식으로 Client 를 기다립니다.
		client_sock[seat] = accept(s, (sockaddr*)&client, &addrsize);

		// accept 시(중요, client_num 가 accept() 함수 수행중 에 변할수 있으므로
		// MAX_CLIENT 도달시랑 따로 accept() 시 문제 발생 가능성 있음
		if(client_num < MAX_CLIENT)		// 정상 맞이 하기
		{

			if(client_sock[seat] != INVALID_SOCKET || client_sock[seat] != SOCKET_ERROR){}
				_beginthread(recv_client, 0, &client_sock[seat]);
				Sleep(10);
				printf("%d번 플레이어 %s:%d 에서 접속하였습니다.\n\n", seat, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
				
		}

		else	// 가득 찻다.
		{
			addrsize = sizeof(client);
			if (client_sock[seat] == INVALID_SOCKET)
			{
				printf("accept() 오류\n");
				closesocket(client_sock[seat]);
				closesocket(s);
				WSACleanup();
				return 1;
			}

			char welcome_full[] = "가득찼습니다.\n";
			ret = send(client_sock[seat], welcome_full, sizeof(welcome_full), 0);
			closesocket(client_sock[seat]);

			// 메시지 보내고 바로 끊는다.

		}
	}
	
	return 0;

}

void recv_client(void *ns)
{

	client_num++;				// 클라이언트 갯수 증가
	seat++;						// 클라이언트 번호 증가
	printf("슬롯 %d개 남음\n", MAX_CLIENT - client_num);		// 갯수로 판단


	int ret;
	char buff[1024] = {0};
	char resetBuff[1024] = {0};
	int tempPlayerNum = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//1. 처음 접속시에 클라이언트에게 플레이어의 넘버를 전송
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	WaitForSingleObject(hMutex, INFINITE);

	//보낼값 선 세팅 부분
	totalPlayer++; //전체인원 증가

	for (int index = 0; index < 4; index++) {

		if (isPlayerExist[index] == false) {

			tempPlayerNum = index;
			isPlayerExist[index] = true;
			break;
		}
	}

	Loby_Accept tempLoby_accept = Loby_Accept(totalPlayer, isAdmin, tempPlayerNum, firstPos[tempPlayerNum],firstColor[tempPlayerNum].mColor_body, firstColor[tempPlayerNum].mColor_body_shadow);


	//1. 데이터 전송
	memcpy(buff, &tempLoby_accept, sizeof(Loby_Accept));
	ret = send(*(SOCKET*)ns, buff, sizeof(Loby_Accept), 0);		// 전송
	memcpy(buff, resetBuff, sizeof(buff));


	//보낼값 후 세팅 부분
	isAdmin = false; //앞으로 방장은 없다

	ReleaseMutex(hMutex);

	//printf("%d번 플레이어 입장하였습니다. \n", tempPlayerNum);		// 갯수로 판단
	printf("현재 총 플레이어 수는 %d명 입니다.\n", totalPlayer);		// 갯수로 판단


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//2. 계속 데이터를 주고받는 부분
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while(ret != SOCKET_ERROR || ret != INVALID_SOCKET)
	{
		char buff2[1024] = { 0 };

		//*******************************************
		// 클라이언트의 메시지를 buff2에 받아서 어떤 분기인지 확인
		ret = recv(*(SOCKET*)ns, buff2, 1024, 0);
		int result = -1; //어떤 Scene인가
		memcpy(&result, buff2, sizeof(int));
	
		//*******************************************
		//로비상태에서 연락받았을 때
		if (result == 2) {

			//printf("+ 로비진행중");
			//클라이언트에게받아온 데이터 = tempData
			Loby_Player * tempData = new Loby_Player();
			memcpy(tempData, buff2, sizeof(Loby_Player));

			//로직 처리
			WaitForSingleObject(hMutex, INFINITE);

			//현재 받아온 플레이어의 넘버
			int tempIndex = tempData->mPlayerNum;

			//방장 문제 씨빨
			bool tempAdmin = false;
			//이미 방장인지 확인한다
			{
				if (tempData->mPlayerArray[tempIndex].mIsAdmin == true) {
					tempAdmin = true;
				}
				else {

					//원래 방장이아니였는데 바뀐 값이 있는지 확인
					if (mPlayerData->mPlayerArray[tempIndex].mIsAdmin == true) {
						tempAdmin = true;
					}
				}
			}


			//todo여기서 스타트 구분해서 시그널다르게하고 시작하라고 알리멷ㄴ돼~
			//데이터 업데이트
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

			//임포스터 리스트 담기
			for (int index = 0;index < 4; index++)
			{
				mPlayerData->mImposterList[index] = isImposter[index];
			}

			memcpy(buff2, mPlayerData, sizeof(Loby_Player));

			send(*(SOCKET*)ns, buff2, sizeof(Loby_Player), 0);

			ReleaseMutex(hMutex);


		}
		//방장이 시작버튼을 눌렀을때
		//이곳은 한번만 들어올수있는거지[방장만]
		else if (result == 3) {
			
			//들어온데이터에서 나머지데이터는 중요하지않으므로 바로 데이터 세팅해서 전송한다
			
			WaitForSingleObject(hMutex, INFINITE);

			//게임시작했다는 전역변수 세팅
			isGameStart = true; 

			//임포스터랜덤으로 선출하는 과정 - 없는사람 예외처리해야함
			int imposterIndex = 0;
			srand((UINT)time(NULL));

			//임포스터 몇명할건지 [3명이하면 1명, 4명이면 2명]
			int tempImPosterNum = 0;


			if (totalPlayer < 4) tempImPosterNum = 1;
			else if (totalPlayer == 4)tempImPosterNum = 2;
			printf("게임을 시작합니다.\n");
			printf("총인원 %d명으로 임포스터는 %d명입니다", totalPlayer, tempImPosterNum);

			////임포스터 수만큼 반복
			//for (int impoCnt = 0; impoCnt < tempImPosterNum; impoCnt++) {

			//	do {
			//		imposterIndex = rand() % 4;
			//	} 
			//	//플레이어가 존재해야하고, 이미 임포스터가 아니어야한다
			//	while (isPlayerExist[imposterIndex] == false && isImposter[imposterIndex] == false);

			//	isImposter[imposterIndex] = true;
			//}

			isImposter[0] = true;
			isImposter[1] = true;

			crewNum = totalPlayer - tempImPosterNum;

			//task총 몇개인지 저장
			totalTaskNum = 3 * crewNum;

			ReleaseMutex(hMutex);
		}
		else if (result == 4) {

			//클라이언트에게받아온 데이터 = tempData
			//현재 받아온 플레이어의 넘버 -> tempPlayerNum

			sInGame_Play * tempData = new sInGame_Play();
			memcpy(tempData, buff2, sizeof(sInGame_Play));

			//로직 처리
			WaitForSingleObject(hMutex, INFINITE);

			//////////////////////////////////////////////////////////////////////////////////////////
			//1. 일단 플레이어데이터 옮겨~
			mPlayerData_inGame->mPlayerArray[tempPlayerNum] = tempData->mPlayerArray[tempPlayerNum];


			//////////////////////////////////////////////////////////////////////////////////////////
			//내가 죽었는지 안죽었는지 계산
			if (whoIsDie == tempPlayerNum) {

				mPlayerData_inGame->mIsDieFirst = true;
				mPlayerData_inGame->mPlayerArray[tempPlayerNum].mKillNum_crew = whoIsKill;
				whoIsDie = -1; //값 초기화
				whoIsKill = -1;
			}
			else {
				mPlayerData_inGame->mIsDieFirst = false;
			}

			//////////////////////////////////////////////////////////////////////////////////////////
			//2. 전체적인 테스크 진행율 계산
			int tempTaskPercent = 0;
			{
				int tempTaskCnt = 0; //총 테스크 한 개수
				int tempAlive = 0; //계산한 사람 수

				for (int index = 0; index < 4; index++) {

					//일단 존재해야하고 && 임포스터가 아니면 계산한다
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
			//3. Kill 관련 계산 - tempData가 맞다
			//내가누굴 죽였습닏다.
			if (tempData->mIsKill == true) {

				whoIsDie = mPlayerData_inGame->mPlayerArray[tempPlayerNum].mKillNum_imposter;
				whoIsKill = tempPlayerNum;

				crewNum--;
			}

			if (crewNum == 0) {
				isGameEnd = -1;
			}

			//여기서 게임끝내는거 확인 그래야 임포 크루 둘다 확인가능 
			mPlayerData_inGame->mIsGameEnd = isGameEnd;


			//클라이언트에게 데이터 전송
			memcpy(buff2, mPlayerData_inGame, sizeof(sInGame_Play));
			send(*(SOCKET*)ns, buff2, sizeof(sInGame_Play), 0);


			ReleaseMutex(hMutex);

			int a = 0;
		}
		////////////////////////////////////////////////////
		//초기화 부분
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

		//초기화 하자
		int a = 0;
		}

	}///while
	////////////////////////////////////////////////////////////////////
	// 접속된 소켓이 연결을 해제 시켰을때
	WaitForSingleObject(hMutex,INFINITE);

	isPlayerExist[tempPlayerNum] = false;
	totalPlayer--;

	if (mPlayerData->mPlayerArray[tempPlayerNum].mIsAdmin == true) {

		bool isGiveAdmin = false; //방장권한을 누구에게줬는지 true면 다른플레이어에게 넘어간것이고 false면 아무도없어서 초기화된것

		//다른 플레이어를 검사해서 방장권한을 넘겨준다
		for (int index = 0; index < 4; index++) {

			if (isPlayerExist[index] == true) {
				mPlayerData->mPlayerArray[index].mIsAdmin = true;
				printf("\n%d번 플레이어에게 방장권한이 넘어갔습니다. \n", index + 1);
				isGiveAdmin = true;
				break;
			}
		}
		
		if (isGiveAdmin == false) {
			isAdmin = true;
			isGameStart = false; //게임시작 초기화


			printf("\n처음 들어오는 플레이어가 방장입니다.\n");
		}
	}

	//나간 플레이어 자리 초기화
	mPlayerData->mPlayerArray[tempPlayerNum] = LobyPlayerSub();
	mPlayerData_inGame->mPlayerArray[tempPlayerNum] = IngamePlayerSub();

	client_num--;
	printf("\n%d번 플레이어 접속해제\n", tempPlayerNum + 1);
	ReleaseMutex(hMutex);


	closesocket(*(int*)ns);
	
	return;
}