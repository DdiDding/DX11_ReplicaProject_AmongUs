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

	//���ڿ����� "Loby" ��°� ã�´� -�ϴ� �� �ؽ�Ʈ ���� �����ϱ� ����
	bool findTextLoby(string str);

	//���� �ִϸ��̼� �� ��ġ ����
	void setGomujul();
	//���پִϸ��̼� ������Ʈ
	void updateGomujul();
private:
	UiManager();
	~UiManager();

	Ui_inGame * mUiInGame;
	Ui_miniMap * mUiMiniMap;

	bool mIsImposter; //���⼭ �����س��� ����Ұ���

	//Main menu---
	Mesh * mStart;
	Mesh * mExit;
	Mesh * mSetting;
	Mesh * mNaver;
	

	//Loby----
	Mesh * mGameStart;
	Mesh * mTotalIcon; //�� �÷��̾� �����ִ� ������

	bool mIsPossibleStart; // ������ ��������

	float mIconOriginPos;
	float mTextOriginPos;

	float mGomujulPosX[7]; //���� �ִϸ��̼� �� ��ġ
	float mGoumujulTotal; //�� ������ ��
	float mGomujulFast; //������
	int mGomujulIndex;//�ִϸ��̼� �ε���
	bool mGomujulActtive; //���� ����������

	//inGame --
	//�÷��̾� ���� - �����ܿ� ����
	D3DXVECTOR4 mColor_body;
	D3DXVECTOR4 mColor_body_shadow;

	Mesh * mMiniMapBtn;
	Mesh * mMiniMapCloseBtn;

	//�̴ϸ��� �����ִ°�?
	bool mIsOpenMiniMap;


	//�κ� �ִ°�??
	bool mIsBeInLoby;

	//�ϴ� �� �ؽ�Ʈ �κ�
	string mPlayerArea;
	//�ؽ�Ʈ�߾������س���~ �ؽ�Ʈ ��ġ��~
	float mAreaTransX;
	float mAreaTransY;

	//�ؽ�Ʈ �̵� �ӵ�
	float mAreaTextFast;

	//�ؽ�Ʈ �ö󰡰� �������� �ִ�,�ּҰ�
	float mAreaTextYMax; //�ִ� �ö󰡴� ��
	float mAreaTextYMin;//�ִ� �������� ��




};

