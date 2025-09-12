#pragma once

class Mesh;

class Admin_SwipeCard
{
public:

	Admin_SwipeCard();
	~Admin_SwipeCard();

	void Update();
	void Render();

	void SetIsClickEnd(bool value) { mIsClickEnd = value; };
	bool GetIsClickEnd() { return mIsClickEnd; };
	bool GetComplete() { return mIsComplete; };

private:

	void init();

	
	//카드 긁은 시간을 체크해 시간은 성공인지 확인 | -1 = 너무 느림 , 0 = 성공 , 1 = 너무 빠름
	int CheckSwipeTime(float swipeTime);

private:

	bool mIsComplete; //미션을 완료했는지 - 100%가 되면 true가 됩니다
	bool mIsClickEnd; // X버튼 눌렀는가??


	Mesh * mBackGround;
	Mesh * mCard;
	Mesh * mSliderTop;
	Mesh * mWalletFront;
	Mesh * mClosseBtn;

	// 같이 움직이기 위한 변수---------

	bool mIsUp;//위로 올라가는중인가?
	float mAllMeshMove; 
	float mAllMeshMoveMin; //최소값 [ 최대값은 0이다 ]
	float mAllMeshMoveFast; //속도

	//내려갈때----------
	float mDownMaxTime;//몇초 지나야 자동으로 내려갈건지
	float mDownTime; //시간재는 변수

	//카드 부분--------
	//오리지널 값 [ 작을때 ]
	D3DXVECTOR2 mCardOriginSize;
	D3DXVECTOR2 mCardOriginTrans;

	//변경 값 [ 커질때 ]
	D3DXVECTOR2 mCardChangeSize;
	D3DXVECTOR2 mCardChangeTrans;

	// 큰거에서 작은거 뺀 값
	D3DXVECTOR2 mCardDisSize;
	D3DXVECTOR2 mCardDisTrans;

	//카드가 오른쪽으로 움직이는 최대 거리
	float mCardMaxX;

	//0.01초 기준으로 몇번 랜더링 할건지
	int mCardMaxCnt;

	//0.01초동안 더해지는 값
	D3DXVECTOR2 mCardUnitSize;
	D3DXVECTOR2 mCardUnitTrans;

	bool mIsCardBiger; //카드가 커지고 있는가?
	
	float mCardTime; //커지는 시간 재는 변수
	bool mCardActtive; //카드가 활성화 되었는지 [ 커지는게 마쳤는지 ]

	
	//카드 활성화 후------

	int mSilderStatus; //어떤불이 켜져야하는지 상태 0 - 모두꺼짐, 1 - 빨간불 꺼짐 2- 초록불 꺼짐
	int mTaskStatus; //미션의 상태, 텍스트와 연관된다

	bool mIsCardRespon; //카드가 되돌아 가고 있는가? 
	float mCardResponFast = 0.1f; //되돌아가는 단위 속도

	bool mIsCardMove; //카드 누른상태에서 움직이고있는가? true면 마우스 눌러서 움직이는중
	

	float mSwipeTime;//플레이어가 카드긁는 동안의 시간

	float mSwipeUnitTime; //기준 시간
	float mSwipeDisTime; //각 플러스 마이너스 몇할건지
	float mSwipeMinTime; //기준시간 + 값 [ 최대값 ] 
	float mSwipeMaxTime;//기준시간 - 값 [ 최소값 ]


	//텍스트-------

	int mTextStatus; //텍스트 종류 인덱스 
					//0.처음
					//1.카드가 커지는게 완료 되면
					//2.끝까지 안긁으면
					//3.빨리 긁으면
					//4.느리게 긁으면

	WCHAR * mTextList[6] = {
		{L"PLEASE INSERT CARD"},
		{L"PLEASE SWIPE CARD"},
		{L"BAD READ. TRY AGAIN."},
		{L"TOO FAST. TRY AGAIN."},
		{L"TOO SLOW. TRY AGAIN."},
		{L"ACCEPTED. THANK YOU."}
	};

	float mTextTime; 

	float mTextMaxTime;

	bool mTextMoveSwitch;//true면 오른방향랜더링 , false면 왼방향렌더링이당

	//
};

