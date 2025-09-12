#pragma once

#include "../Geometry/AnimationRect.h"
#include "../Geometry/InGame/AnimationPlayerMesh.h"
#include "../Geometry/InGame/AnotherPlayer.h"

struct sRenderToOrder
{
	sRenderToOrder() {};
	sRenderToOrder(bool isMe, int index, float transY) {
		mIsMe = isMe;
		mIndex = index;
		mTransY = transY;
	};

	bool operator < (sRenderToOrder hr) {
		return  this->mTransY < hr.mTransY;
	}

	bool mIsMe;
	int mIndex;
	float mTransY;
};


static bool compare(sRenderToOrder lr, sRenderToOrder rr) {

	return rr.mTransY < lr.mTransY;
}


class PlayerManager : public SingletonBase<PlayerManager>
{
public:
	friend class SingletonBase<PlayerManager>;

	void Update();
	void Update_noMove();

	void Render();

	void Setting();

	void ChangeMyAni(string aniName) { mPlayer->ChangeAni(aniName); };

	void SetMyPlayerTrans(D3DXVECTOR2 newTrans) { mPlayer->SetPlayerPos(newTrans); };

	void SetColorToPlayer(int index, D3DXVECTOR4 * playerBody, D3DXVECTOR4 * playerBodyShadow);

	void SetIsMoveOK(bool value) { mPlayer->SetIsMoveOK(value); };

	void SetIsGhost(bool value) { mPlayer->SetIsGhost(value); };

	void SettingMyDieBody();

	void SetMyIsKilling(bool value) { mPlayer->SetIsKilling(value); };

	void ChangeMyShader(LPCWSTR hlslPath) { mPlayer->ChangeShader(hlslPath); };

	//ani->GetSize()ani->GetSize()ani->GetPlayerArea()
	D3DXVECTOR2 GetMyTrans(){return mPlayer->GetTrans();};
	D3DXVECTOR2 GetMySize() {return mPlayer->GetSize();};
	int GetMyArea() {return mPlayer->GetPlayerArea();};
	string GetMyArea_string() { return mPlayer->GetPlayerArea_string(); };
	string GetMyAniName() { return mPlayer->GetAniName(); };
	UINT GetMyFrame() { return mPlayer->GetFrame(); };
	bool GetMyIsRight() { return mPlayer->GetIsRight(); };

	D3DXVECTOR4 GetMyColor_body() { return *(mPlayer->GetColorBodyP()); };
	D3DXVECTOR4 GetMyColor_shadow() { return *(mPlayer->GetColorBodyShadowP()); };

	float GetMyFast() { return mPlayer->GetFast(); };
	D3DXVECTOR3 GetPlayerVector() { return mPlayer->GetPlayerVector(); };
	PlayerColors GetPlayerColor(int index) { return mPlayerColors[index]; };


	//유령&&시체 부분

	bool GetImGhost() { return mPlayer->GetImGhost(); };

	D3DXVECTOR2 GetDieBodyTrans() { return mMyDieBody->GetTrans(); };
	bool GetDieBodyLook() { return mMyDieBody->GetLookingRight(); };
	UINT GetDieBodyFrame() { return mMyDieBody->GetFrame(); };
	string GetDieBodyAniName() { return mMyDieBody->GetAniName(); };


private:

	//기본 색상값을 배열에 세팅해 놓는다
	void defineColor();

	void anotherUpdate();
	void anotherUpdate_inGame_crew();
	void anotherUpdate_inGame_imposter(int nearIndex);

	void anotherRender();
	void anotherRender_inGame();

	//Y축을 기준으로 랜더링을 해준다
	void renderToOrder_loby();
	void renderToOrder_inGame();

	
private:
	PlayerManager();
	~PlayerManager();

	void init();


	//플레이어의데이터를 받아와서 플레이어들을 렌더링할 객체들 담을 포인터  
	AnotherPlayer * mAnotherPlayerMesh [4];
	
	//내가 몇번째 플레이어인지
	int mMyPlayerNum; 

	//플레이어들의 색상 세팅값들을 가지고있다
	PlayerColors mPlayerColors[9];
	//처음 시작할때의 각 플레이어 넘버에따라 초기 위치를 가지고있다
	D3DXVECTOR2 mPlayerStartPos[4];


	//플레이어 (자기자신)
	AnimationRect * mPlayer;
	AnimationPlayerMesh * mPlayerSpawn; //스폰 애니메이션, 끝나면 바로 player로 변경
	int mSpawnEndCnt; //스폰애니메이션 끝났는지 하나끝날때마다 ++


	 //시체임ㅋㅋ
	AnimationPlayerMesh * mMyDieBody;
	bool mIsDieBodyFrameLast; //프레임이마지막인지?  마지막에 멈추기위한 변수 true면 멈추고 flas면 계속 업데이트
	bool mIsDieBodyRender; //시체 랜더링해야하는가?
	D3DXVECTOR2 mDieBodyTrans; //시체 위치 고정해야함
	bool mDieBodyLooking; // true면 오른쪽 (정방향)
};
