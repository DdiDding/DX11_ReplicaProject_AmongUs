#pragma once

class Mesh;
class AniamtionMesh;

class O2_ClienFilter
{
public:
	O2_ClienFilter();
	~O2_ClienFilter();

	void Update();
	void Render();

	void SetIsClickEnd(bool value) { mClickEnd = value; };
	bool GetIsClickEnd() { return mClickEnd; };
	bool GetComplete() { return mIsComplete; };

private:

	struct  sLeaf
	{
		sLeaf() {};

		Mesh * mLeafMesh;//�޽�
		bool mIsMove; //���콺�� Ŭ���ؼ� �̵�������
		bool mIsOuting;//�������� ������
		bool mIsComplete; //�ȿ� �־�������

		D3DXVECTOR2 mUintTrans;//�̵��ϴ� ��������
		D3DXVECTOR2 mLeafMinFast; //�پ��� �ӵ����� ���������� �� ��5����1?

		D3DXVECTOR2 mLeafTrans;//�ö󰡰� �������°ŋ��� �� y�������� ����
	};

	void init();

	void initLeaf();
	void updateLeaf();
	void renderLeaf();

	//ȭ�� ��  ������  �Ʒ� �κ��� ����κ��� �¾Ҵ��� �˼��ִ�
	//0�̸� �����̰� [�Ⱥε���] 1�̸� ����/ 2�� ������ / 3�̸� �Ʒ����̴�
	int isOut(D3DXVECTOR2 leafTrans, D3DXVECTOR2 leafSize);

	//�������� �ϳ��� Ŭ���ߴ°�?
	bool isLeafClick();

private:

	//���� ------------------
	bool mIsComplete; //�̼��� �Ϸ��ߴ��� - 100%�� �Ǹ� true�� �˴ϴ�
	bool mClickEnd; // X��ư �����°�??



	// ���� �����̱� ���� ����---------

	bool mIsUp = true;//���� �ö󰡴����ΰ�?
	float mAllMeshMove = -576.0f;
	float mAllMeshMoveMin = -576.0f; //�ּҰ� [ �ִ밪�� 0�̴� ]
	float mAllMeshMoveFast = 60; //�ӵ�

	//��������----------
	float mDownMaxTime = 1.2f;//���� ������ �ڵ����� ����������
	float mDownTime = 0.0f; //�ð���� ����


	// �Ž��� -------------------
	Mesh * mClosseBtn;

	Mesh * mBackGround; //�޹��
	Mesh * mFront; //�� �Ѳ� �κ�

	Mesh * mRightCompleteArrow; // �Ϸ�� �ʷ� ȣ����ǥ
	Mesh * mLeftCompleteArrow; // �Ϸ�� �ʷ� ȣ����ǥ
	
	
	bool mActtiveArrow; //true�� ȭ��ǥ �ִ� �Ҵ�
	AnimationMesh * mRightArrow; //���콺 ������ ����Ǵ¾ִϸ��̼�
	AnimationMesh * mLeftArrow; //���콺 ������ ����Ǵ¾ִϸ��̼�

	sLeaf mLeaf[7]; //�����ٵ�
	float mLeafFast; //������ �ӵ���
	D3DXVECTOR2 mLeatOutPoint = { 65, 360 }; //�������� ��������ϴ� ����
	float mLeafOutX = 520.0f; //�������� �������� ���� x��ġ

	int mLeatOutCnt = 0; //�������� �� ī����
};

