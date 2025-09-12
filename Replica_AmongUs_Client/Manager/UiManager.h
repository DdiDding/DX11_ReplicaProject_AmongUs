#pragma once
#include "../Geometry/InGame/Ui.h"


class UiManager : public SingletonBase<UiManager>
{
public:

	friend class SingletonBase<UiManager>;

	void Update();
	void Update_mainMenu();
	void Update_loby();
	//void Update_inGame_start()
	void Update_inGame();

	void Render();
	void Render_mainMenu();
	void Render_loby();
	//void Render_inGame_start()
	void Render_inGame();


	void Setting();

	void SaveMyColor(D3DXVECTOR4 body, D3DXVECTOR4 shadow);

	/*****************************InGame*****************************/

	bool GetIsSlot1Click() { return mUiInGame->GetIsSlot1Click(); };
	bool GetIsSlot2Click() { return mUiInGame->GetIsSlot2Click(); };


	/*****************************MiniMap*****************************/
	bool GetIsOpenMiniMap() { return mIsOpenMiniMap; };

private:

	//문자열에서 "Loby" 라는걸 찾는다 -하단 맵 텍스트 띄울거 구분하기 위함
	bool findTextLoby(string str);

	//고무줄 애니메이션 각 위치 세팅
	void setGomujul();
	//고무줄애니메이션 업데이트
	void updateGomujul();
private:
	UiManager();
	~UiManager();

	Ui_inGame * mUiInGame;
	Ui_miniMap * mUiMiniMap;

	bool mIsImposter; //여기서 저장해놓고 사용할거임

	//Main menu---
	Mesh * mStart;
	Mesh * mExit;
	Mesh * mSetting;
	Mesh * mNaver;
	

	//Loby----
	Mesh * mGameStart;
	Mesh * mTotalIcon; //총 플레이어 옆에있는 아이콘

	bool mIsPossibleStart; // 시작이 가능한지

	float mIconOriginPos;
	float mTextOriginPos;

	float mGomujulPosX[7]; //고무줄 애니메이션 각 위치
	float mGoumujulTotal; //총 움직인 양
	float mGomujulFast; //빠르기
	int mGomujulIndex;//애니메이션 인덱스
	bool mGomujulActtive; //고무줄 진행중인지

	//inGame --
	//플레이어 색상 - 아이콘에 사용됨
	D3DXVECTOR4 mColor_body;
	D3DXVECTOR4 mColor_body_shadow;

	Mesh * mMiniMapBtn;
	Mesh * mMiniMapCloseBtn;

	//미니맵이 열려있는가?
	bool mIsOpenMiniMap;


	//로비에 있는가??
	bool mIsBeInLoby;

	//하단 맵 텍스트 부분
	string mPlayerArea;
	//텍스트중앙정렬해놨다~ 텍스트 위치값~
	float mAreaTransX;
	float mAreaTransY;

	//텍스트 이동 속도
	float mAreaTextFast;

	//텍스트 올라가고 내려가는 최대,최소값
	float mAreaTextYMax; //최대 올라가는 값
	float mAreaTextYMin;//최대 내려가는 값




};

