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


	//����&&��ü �κ�

	bool GetImGhost() { return mPlayer->GetImGhost(); };

	D3DXVECTOR2 GetDieBodyTrans() { return mMyDieBody->GetTrans(); };
	bool GetDieBodyLook() { return mMyDieBody->GetLookingRight(); };
	UINT GetDieBodyFrame() { return mMyDieBody->GetFrame(); };
	string GetDieBodyAniName() { return mMyDieBody->GetAniName(); };


private:

	//�⺻ ������ �迭�� ������ ���´�
	void defineColor();

	void anotherUpdate();
	void anotherUpdate_inGame_crew();
	void anotherUpdate_inGame_imposter(int nearIndex);

	void anotherRender();
	void anotherRender_inGame();

	//Y���� �������� �������� ���ش�
	void renderToOrder_loby();
	void renderToOrder_inGame();

	
private:
	PlayerManager();
	~PlayerManager();

	void init();


	//�÷��̾��ǵ����͸� �޾ƿͼ� �÷��̾���� �������� ��ü�� ���� ������  
	AnotherPlayer * mAnotherPlayerMesh [4];
	
	//���� ���° �÷��̾�����
	int mMyPlayerNum; 

	//�÷��̾���� ���� ���ð����� �������ִ�
	PlayerColors mPlayerColors[9];
	//ó�� �����Ҷ��� �� �÷��̾� �ѹ������� �ʱ� ��ġ�� �������ִ�
	D3DXVECTOR2 mPlayerStartPos[4];


	//�÷��̾� (�ڱ��ڽ�)
	AnimationRect * mPlayer;
	AnimationPlayerMesh * mPlayerSpawn; //���� �ִϸ��̼�, ������ �ٷ� player�� ����
	int mSpawnEndCnt; //�����ִϸ��̼� �������� �ϳ����������� ++


	 //��ü�Ӥ���
	AnimationPlayerMesh * mMyDieBody;
	bool mIsDieBodyFrameLast; //�������̸���������?  �������� ���߱����� ���� true�� ���߰� flas�� ��� ������Ʈ
	bool mIsDieBodyRender; //��ü �������ؾ��ϴ°�?
	D3DXVECTOR2 mDieBodyTrans; //��ü ��ġ �����ؾ���
	bool mDieBodyLooking; // true�� ������ (������)
};
