#pragma once
#include "../../Manager/TaskActtiveManager.h"
#include "../../Manager/TaskManager.h"
#include "../InGame/Ui_inGameRect.h"
#include "Mesh_player.h"




//인게임에 사용되는 Ui
class Ui_inGame
{
public:

	Ui_inGame();
	~Ui_inGame();

	void Update(bool isImposter);


	void Render(bool isImposter);

	//클릭을 했는지 확인한다
	bool GetIsSlot2Click() {return mIsSlot2Click;};

	//2번 예외하고 0, 1번은 활성화가 되고나서야 클릭을 처리하기때문에 클릭이 된다면 활성화도 됬다ㅓ는거다
	bool GetIsSlot1Click() {return mIsSlot1Click;};

private:

	//다른 이미지로 교체 ( uv값 변경 )
	void changeImage(Ui_inGameRect * slot, UINT uvNum);

private:

	//애니메이션이지만 사실 그냥 내가 쪼개서 정적인 이미지 출력을 안만들어서 쓰는거다
	Animation mAnimation;


	//Ui 버튼 슬롯 세개를 가지고있음
	//  - 번호위치 - 
	//		[ 0 ]
	//[ 1 ]	[ 2 ]
	Ui_inGameRect * mUiSlot[3];

	bool mCompleteList[3];


	//ps로 보낼 상수버퍼 투명인지 반투명인지 보내는함수
	//마우스 와의 상호작용
	string mTaskName;


	//각 슬롯을 눌렀는지
	bool mIsSlot0Click = false;
	bool mIsSlot1Click = false;
	bool mIsSlot2Click = false;


	//각슬롯이 활성화 됐는지
	bool mPossibleSlot0 = false;
	bool mPossibleSlot1 = false;
	//bool mPossibleSlot2 = false; ->이건 TaskManager에서 대신해준다

	//킬이쿨타임인가 true면 쿨타임중인거고 false면 활성화 된거다 
	bool mIsKillCoolTime = false;
	float mCoolTime = 0.0f; //쿨타임 재는 시간
	float mMaxCoolTime = 10.0f; //맥스 쿨타임

};


class Ui_miniMap {

public:

	Ui_miniMap();
	~Ui_miniMap();

	void Update();
	void Render();

	void SetColorToIcon(D3DXVECTOR4 body, D3DXVECTOR4 shadow);


private:

	void init();

	//미니맵에서의 공간좌표를 반환해줌
	D3DXVECTOR2 getMiniMapPos();

private:

	Mesh * mMiniMapBtn;
	//미니맵의 Trans값
	D3DXVECTOR2 mMiniMapTrans = { 179.0f, 38.0f };
	D3DXVECTOR2 mMiniMapSize = { 922.0f, 647.0f };


	//플레이어의 아이콘
	Mesh_player * mPlayerIcon;
	//여백공간 뺴고 구역의 전체적인 사각형 사이즈
	D3DXVECTOR2 mOnlyAreaSize = {3540, 2468};
	//저 areaSize에서의 좌표를 구하기위한 빼야할 값
	D3DXVECTOR2 mToDoMinValue = { 642, 494 };


	//하단 맵이 어딘지 알려주는 텍스트

};