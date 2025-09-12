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

	
	//ī�� ���� �ð��� üũ�� �ð��� �������� Ȯ�� | -1 = �ʹ� ���� , 0 = ���� , 1 = �ʹ� ����
	int CheckSwipeTime(float swipeTime);

private:

	bool mIsComplete; //�̼��� �Ϸ��ߴ��� - 100%�� �Ǹ� true�� �˴ϴ�
	bool mIsClickEnd; // X��ư �����°�??


	Mesh * mBackGround;
	Mesh * mCard;
	Mesh * mSliderTop;
	Mesh * mWalletFront;
	Mesh * mClosseBtn;

	// ���� �����̱� ���� ����---------

	bool mIsUp;//���� �ö󰡴����ΰ�?
	float mAllMeshMove; 
	float mAllMeshMoveMin; //�ּҰ� [ �ִ밪�� 0�̴� ]
	float mAllMeshMoveFast; //�ӵ�

	//��������----------
	float mDownMaxTime;//���� ������ �ڵ����� ����������
	float mDownTime; //�ð���� ����

	//ī�� �κ�--------
	//�������� �� [ ������ ]
	D3DXVECTOR2 mCardOriginSize;
	D3DXVECTOR2 mCardOriginTrans;

	//���� �� [ Ŀ���� ]
	D3DXVECTOR2 mCardChangeSize;
	D3DXVECTOR2 mCardChangeTrans;

	// ū�ſ��� ������ �� ��
	D3DXVECTOR2 mCardDisSize;
	D3DXVECTOR2 mCardDisTrans;

	//ī�尡 ���������� �����̴� �ִ� �Ÿ�
	float mCardMaxX;

	//0.01�� �������� ��� ������ �Ұ���
	int mCardMaxCnt;

	//0.01�ʵ��� �������� ��
	D3DXVECTOR2 mCardUnitSize;
	D3DXVECTOR2 mCardUnitTrans;

	bool mIsCardBiger; //ī�尡 Ŀ���� �ִ°�?
	
	float mCardTime; //Ŀ���� �ð� ��� ����
	bool mCardActtive; //ī�尡 Ȱ��ȭ �Ǿ����� [ Ŀ���°� ���ƴ��� ]

	
	//ī�� Ȱ��ȭ ��------

	int mSilderStatus; //����� �������ϴ��� ���� 0 - ��β���, 1 - ������ ���� 2- �ʷϺ� ����
	int mTaskStatus; //�̼��� ����, �ؽ�Ʈ�� �����ȴ�

	bool mIsCardRespon; //ī�尡 �ǵ��� ���� �ִ°�? 
	float mCardResponFast = 0.1f; //�ǵ��ư��� ���� �ӵ�

	bool mIsCardMove; //ī�� �������¿��� �����̰��ִ°�? true�� ���콺 ������ �����̴���
	

	float mSwipeTime;//�÷��̾ ī��ܴ� ������ �ð�

	float mSwipeUnitTime; //���� �ð�
	float mSwipeDisTime; //�� �÷��� ���̳ʽ� ���Ұ���
	float mSwipeMinTime; //���ؽð� + �� [ �ִ밪 ] 
	float mSwipeMaxTime;//���ؽð� - �� [ �ּҰ� ]


	//�ؽ�Ʈ-------

	int mTextStatus; //�ؽ�Ʈ ���� �ε��� 
					//0.ó��
					//1.ī�尡 Ŀ���°� �Ϸ� �Ǹ�
					//2.������ �ȱ�����
					//3.���� ������
					//4.������ ������

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

	bool mTextMoveSwitch;//true�� �������ⷣ���� , false�� �޹��ⷻ�����̴�

	//
};

