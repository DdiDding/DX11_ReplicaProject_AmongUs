#pragma once

#include <winsock.h>
#include <process.h>

#pragma comment(lib,"wsock32.lib")

//���ؽ�
static HANDLE hMutex;
static int socketValue; //���� ��

class MatchingClient
{
public:
	MatchingClient();
	~MatchingClient();

	void StartTCP();


	void Connect(); //������ ����


	//����� mainMenu ����  gameLoby���� �þƼ� ���ش�
	void recving();
	static void recvingThread(LPVOID p ) {	((MatchingClient*)p)->recving();	};
	void StartRecving() { _beginthread(recvingThread, 0, NULL);	}


	//����� InGame�κ��� �þ��ش�
	void recving_inGame();
	static void recvingThread_inGame(LPVOID p) { ((MatchingClient*)p)->recving_inGame(); };
	void StartRecving_inGame() { _beginthread(recvingThread_inGame, 0, NULL); }


	void recving_end();
	static void recvingThread_end(LPVOID p) { ((MatchingClient*)p)->recving_end(); };
	void StartRecving_end() { _beginthread(recvingThread_end, 0, NULL); }


	//�� �������� ���ú��� �ٸ�����
	void Setting();

	bool GetIsConnect() { return mIsConnect; };

private:

	void init();

	void newHandler() {

		cout << "This memory allocation code cant excute" << endl;
		throw bad_alloc();
		return;
	}
	//������ �ޱ�
	
private:

	sockaddr_in server; //������ �ּ����� ����ü

	bool mIsConnect;
};