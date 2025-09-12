#pragma once


class ClientData : public SingletonBase<ClientData>
{
public:

	friend class SingletonBase<ClientData>;


	void Setting();


public:



	int mTotalPlayer; //총 플레이어 수
	bool mIsAdmin; //방장인지 아닌지
	int mPlayerNum; //몇번째 플레이어인지

	bool mImImposter;//자신이 임포스터인지 아닌지
	bool mImposterList[4];

	D3DXVECTOR2 mPlayerFirstPos;//플레이어 자기자신의 로비 처음들어갔을 때의 위치
	D3DXVECTOR4 mPlayerFirstColorBody;//
	D3DXVECTOR4 mPlayerFirstColorShadow;//

	LobyPlayerSub mAnotherPlayer_Data[4];

	//1. EndManager에서 요청 bool을 킨다.
	//2. 통신부분에서 mRequestGameStart을듣고 서버에 Start를 요청하고 mRequestGameStart를다시 false로하고 원래 통신으로 통신한다
	//3. 서버에서 게임시작 전역변수를 On한다
	//4. 이제 서버에서 주는 Start를 받아서 시작을한다
	bool mRequestGameStart;// 게임 시작요청! 스위치 형식임

	bool mIsGameStart;//게임이 시작하는지


	//inGame_Play

	int mTotalTaskPercent; //모든 플레이어 합산한 테스크 완료율
	IngamePlayerSub mAnotherPlayer_inGame[4]; //모든 플레이어의 정보들

	bool mImDie; //내가 죽었는지..?
	int mWhoIsKill; //누가 나를 죽였는지 인덱스 저장

	int mWhoIKilled; //내가 누구를 죽였는지 인덱스 저장 

	int mIsGameEnd; //게임이 끝났는지

private:

	ClientData();
	~ClientData();

	void init();

};

