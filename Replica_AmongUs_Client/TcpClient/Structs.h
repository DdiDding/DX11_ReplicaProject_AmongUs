#pragma once

//////////////////////////////////////////////////////////////////////
//��� ���� ��
//////////////////////////////////////////////////////////////////////

//��� �÷��̾��� �����͸� �� �迭�������� �����Ұ���
struct LobyPlayerSub {
	LobyPlayerSub() {

		mExist = false;
		mPos = { 0,0 };
		mAniName = "";
		mFrame = 0;
		mIsAdmin = false;
		mIsRight = true;
	};

	LobyPlayerSub(D3DXVECTOR2 pos, string aniName, UINT frame) {
		mExist = true;
		mPos = pos;
		mAniName = aniName;
		mFrame = frame;
	};

	bool mExist; //�÷��̾ �����ϴ���
	bool mIsAdmin;
	bool mIsRight; //�÷��̾ �������� �����ִ��� [�ùߤ���¥ ����ġ�� �������� �������̴�]
	D3DXVECTOR2 mPos; //�÷��̾��� ��ġ
	string mAniName; //�÷��̾��� �ִϸ��̼� �̸�
	UINT mFrame; //�÷��̾��� ����������

};



struct PlayerColors {
	PlayerColors() {};
	PlayerColors(D3DXVECTOR4 color_body, D3DXVECTOR4 color_body_shadow) {
		mColor_body = color_body;
		mColor_body_shadow = color_body_shadow;
	}

	D3DXVECTOR4 mColor_body;
	D3DXVECTOR4 mColor_body_shadow;
};


struct IngamePlayerSub {

	IngamePlayerSub() {

		mExist = false;
		mIsRender = false;
		mPlayerWhere = -1;
		mCompleteTask = 0;
		mIsDieSecond = false;
		mKillNum_crew = -1;
		mKillNum_imposter = -1;
		mIsRight = true;
		mPos = { 0,0 };
		mAniName = "";
		mFrame = 0;
	};


	bool mExist; //�÷��̾ �����ϴ���
	bool mIsRender; //�������� �ؾ��ϴ���
	int mPlayerWhere;//�÷��̾ ��� ������ �ִ��� //admin�ʿ� ����
	bool mIsImposter;//������������
	bool mIsDieSecond; //�̹��׾��ִ���
	int mCompleteTask; // �̼� �ϼ��� ���� ������ �Ѱܾ���
	int mKillNum_crew; //�� ���� �÷��̾� ��ȣ -  crew�϶�
	int mKillNum_imposter; //���� ���� �÷��̾� ��ȣ
	bool mIsRight; //�÷��̾ �������� �����ִ��� [�ùߤ���¥ ����ġ�� �������� �������̴�]
	D3DXVECTOR2 mPos; //�÷��̾��� ��ġ
	string mAniName; //�÷��̾��� �ִϸ��̼� �̸�
	UINT mFrame; //�÷��̾��� ����������
};

//////////////////////////////////////////////////////////////////////
//��ſ�
//////////////////////////////////////////////////////////////////////

//�κ� ó������ �޴� ����ü
struct Loby_Accept
{
	Loby_Accept() {};
	Loby_Accept(int totalPlayer, bool isAdmin, int playerNum, D3DXVECTOR2 firstPos, D3DXVECTOR4 colorBody, D3DXVECTOR4 colorShadow) {

		mTotalPlayer = totalPlayer;
		mIsAdmin = isAdmin;
		mPlayerNum = playerNum;
		mFirstPos = firstPos;
		mColorBody = colorBody;
		mColorShadow = colorShadow;
	}

	int mTotalPlayer;
	bool mIsAdmin;
	int mPlayerNum;
	D3DXVECTOR2 mFirstPos;
	D3DXVECTOR4 mColorBody;
	D3DXVECTOR4 mColorShadow;
};

//�κ񿡼� ��� ������ �ְ�޴� ����ü
struct Loby_Player {

	Loby_Player() {
		mSignal = -1;
		mTotalPlayer = 0;
		mPlayerNum =- 1;
		mIsStart = false;
		mPlayerArray[0] = LobyPlayerSub();
		mPlayerArray[1] = LobyPlayerSub();
		mPlayerArray[2] = LobyPlayerSub();
		mPlayerArray[3] = LobyPlayerSub();

		mImposterList[0] = false;
		mImposterList[1] = false;
		mImposterList[2] = false;
		mImposterList[3] = false;
	};

	int mSignal; //�ñ׳� ��ȣ - ���� ���̾����!
	int mTotalPlayer;
	bool mIsStart; //������ ���۵Ǵ���
	int mPlayerNum; //�÷��̾��� ��ȣ
	bool mImposterList[4];
	LobyPlayerSub mPlayerArray[4];
};


struct sInGame_Play {

	sInGame_Play() {

		mSignal = -1; //��ȣ
		mIsGameEnd = false; //
		mTotalComplete = 0;
		mIsDieFirst = false;
		mIsKill = false;

		mPlayerArray[0] = IngamePlayerSub();
		mPlayerArray[1] = IngamePlayerSub();
		mPlayerArray[2] = IngamePlayerSub();
		mPlayerArray[3] = IngamePlayerSub();
	}

	//���� ���࿡�־� �ʿ��� ����
	int mSignal; //��ȣ 
	int mIsGameEnd; // -1�� �����¸� 0 �� �������� 1�� ũ�� �¸�
	int mTotalComplete; //�̼� �ϼ����� �������� �޾ƾ���

	bool mIsDieFirst; //���� ���! �׾�����
	bool mIsKill; //���� �������� �׿�����
	
	//�÷��̾�� �־���ϴ°�
	IngamePlayerSub mPlayerArray[4];
};