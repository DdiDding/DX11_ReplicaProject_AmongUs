#pragma once

#include <winsock.h>
#include <process.h>

#pragma comment(lib,"wsock32.lib")

//뮤텍스
static HANDLE hMutex;
static int socketValue; //소켓 값

class MatchingClient
{
public:
	MatchingClient();
	~MatchingClient();

	void StartTCP();


	void Connect(); //서버와 연결


	//통신을 mainMenu 부터  gameLoby까지 맡아서 해준다
	void recving();
	static void recvingThread(LPVOID p ) {	((MatchingClient*)p)->recving();	};
	void StartRecving() { _beginthread(recvingThread, 0, NULL);	}


	//통신을 InGame부분을 맡아준다
	void recving_inGame();
	static void recvingThread_inGame(LPVOID p) { ((MatchingClient*)p)->recving_inGame(); };
	void StartRecving_inGame() { _beginthread(recvingThread_inGame, 0, NULL); }


	void recving_end();
	static void recvingThread_end(LPVOID p) { ((MatchingClient*)p)->recving_end(); };
	void StartRecving_end() { _beginthread(recvingThread_end, 0, NULL); }


	//각 씬에대해 리시빙을 다르게함
	void Setting();

	bool GetIsConnect() { return mIsConnect; };

private:

	void init();

	void newHandler() {

		cout << "This memory allocation code cant excute" << endl;
		throw bad_alloc();
		return;
	}
	//데이터 받기
	
private:

	sockaddr_in server; //서버의 주소정보 구조체

	bool mIsConnect;
};