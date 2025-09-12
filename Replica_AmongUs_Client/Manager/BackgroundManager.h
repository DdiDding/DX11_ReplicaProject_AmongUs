#pragma once

class ColorMesh;

class BackgroundManager :public SingletonBase< BackgroundManager>
{
private:

	struct Snow
	{
		Snow() {};
		Snow(D3DXVECTOR2 size, D3DXVECTOR3 Trans, float fast) {

			mSize = size;
			mTrans = Trans;
			mFast = fast;
		}
		D3DXVECTOR2 mSize; //���� ũ��
		D3DXVECTOR3 mTrans; //���� trans
		float mFast; //���� ������

	};

	struct Crew
	{
		Crew() {};
		Crew(D3DXVECTOR2 crewFast, float rotation) {

			mCrewFast = crewFast;
			mRotation = rotation;
		}

		D3DXVECTOR2 mCrewFast; //ũ�� �����̴� �ӵ� �� (�������� x ����)
		float mRotation; //ũ�� ȸ���ϴ� �ӵ�

		D3DXVECTOR2 mOriginSize; //ũ���� ���� ������

		PlayerColors mColor; //ũ��� ����
	};
	

public:

	friend class SingletonBase< BackgroundManager>;

	void Update();
	void Update_mainMenu();
	void Update_inGame_start();
	void Update_inGame();
	void Update_inGame_end();
	void Update_loby();

	void Render();
	void Render_mainMenu();
	void Render_inGame_start();
	void Render_inGame();
	void Render_inGame_end();
	void Render_loby();

	void Setting();

private:


	void putSnowData();
	void updateSnowData();
	void updateSnowData_loby();
	void renderSnowData();

	void initCrew();
	void updateCrew();

	BackgroundManager();
	~BackgroundManager();

	void init();

private:

	bool mIAmImposter; //������������ ���⼭ �����س��� ����Ϸ��� ����

	//mainMenu---
	Mesh * mLogo;
	ColorMesh * mInGame_Space;
	Mesh * mSnow;
	Mesh * mCrew[6];
	int mSnowMany = 30;
	Snow mSnowData[30];
	
	Crew mCrewData[6];

	//loby-----
	Mesh * mLoby_map;


	//inGame_start-----

	//inGame_start�Ǿִϸ��̼��� 2������, "shh" �� ����� 
	//false�� shh�����̸� true�� ������̴�
	bool mInGameWhatAni = false;
	float mAniTime = 0.0f;
	float mAniNextTime_1 = 2.5f; //���� ��������� �Ѿ���ΰ� 
	float mAniNextTime_2 = 6.0f; //���� ���� ���� ������ �Ѿ���ΰ� 

	//shh�κ�
	Mesh * mShh_main;
	Mesh * mShh_pan;
	Mesh * mShh_son;
	Mesh * mShh_text;
	Mesh * mShh_front;

	float mPanRotation = -60;
	float mPanMaxRotation = 6;
	float mPanFast = 1.6f;
	int mPanState = 0; // 0�̸� �ö󰡴°�, 1�̸� �������°�, 2�� ��ž

	D3DXVECTOR2 mMainOriginSize = D3DXVECTOR2(345, 372);
	D3DXVECTOR2 mMainOriginTrans = D3DXVECTOR2(468, 175);

	D3DXVECTOR2 mMainMaxSize = D3DXVECTOR2(399, 430);
	D3DXVECTOR2 mMainMaxTrans = D3DXVECTOR2(441, 146);
	
	float mMainChangeTime = 0.15f; //���� ��
	float mMainTime = 0.0f;//������Ʈ�Ǵ� ��

	bool mIsShowText;//�ؽ�Ʈ�� ���̴���


	//������κ�
	Mesh * mShow_imposter;
	Mesh * mShow_crew;

	Mesh * mFadeOut_left;
	Mesh * mFadeOut_right;

	float mFadeOutLength = 5.3f; //���̵�ƿ� �����̴� �Ÿ�

	float mTextMove = 0.0f; //���� �����̴� �Ÿ�
	float mTextFast = 0.1f; //���� �����̴� �Ÿ�
	float mTextMaxMove = 20.0f; //���� �ִ볻������ �Ÿ�

	float mAllBlackAlpha = 1.0f; //��ü ���� ȭ��

	//������ �÷��̾��
	Mesh * mMainPlayer;
	vector<Mesh*> mComPlayer;

	PlayerColors mComPlayerColor[3];

	//inGame-----
	//ColorMesh * mInGame_Space;
	Mesh * mInGame_Map;


	//������

	//�����ڸ�
	PlayerColors mEndMainColor; //��
	int mMainIndex; //�ε���,

	//���ӳ����� �κ񰡴� �� �ð�
	float mEndGameTime = 0.0f;
	float mEndGameMaxTime = 5.0f;
};

