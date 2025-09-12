#pragma once


class ClientData : public SingletonBase<ClientData>
{
public:

	friend class SingletonBase<ClientData>;


	void Setting();


public:



	int mTotalPlayer; //�� �÷��̾� ��
	bool mIsAdmin; //�������� �ƴ���
	int mPlayerNum; //���° �÷��̾�����

	bool mImImposter;//�ڽ��� ������������ �ƴ���
	bool mImposterList[4];

	D3DXVECTOR2 mPlayerFirstPos;//�÷��̾� �ڱ��ڽ��� �κ� ó������ ���� ��ġ
	D3DXVECTOR4 mPlayerFirstColorBody;//
	D3DXVECTOR4 mPlayerFirstColorShadow;//

	LobyPlayerSub mAnotherPlayer_Data[4];

	//1. EndManager���� ��û bool�� Ų��.
	//2. ��źκп��� mRequestGameStart����� ������ Start�� ��û�ϰ� mRequestGameStart���ٽ� false���ϰ� ���� ������� ����Ѵ�
	//3. �������� ���ӽ��� ���������� On�Ѵ�
	//4. ���� �������� �ִ� Start�� �޾Ƽ� �������Ѵ�
	bool mRequestGameStart;// ���� ���ۿ�û! ����ġ ������

	bool mIsGameStart;//������ �����ϴ���


	//inGame_Play

	int mTotalTaskPercent; //��� �÷��̾� �ջ��� �׽�ũ �Ϸ���
	IngamePlayerSub mAnotherPlayer_inGame[4]; //��� �÷��̾��� ������

	bool mImDie; //���� �׾�����..?
	int mWhoIsKill; //���� ���� �׿����� �ε��� ����

	int mWhoIKilled; //���� ������ �׿����� �ε��� ���� 

	int mIsGameEnd; //������ ��������

private:

	ClientData();
	~ClientData();

	void init();

};

