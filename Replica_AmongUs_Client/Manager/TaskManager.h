#pragma once

class TaskActtiveManager;
class Task;
class Mesh;


struct stringBool {
	stringBool() {};
	stringBool(string str, bool bol) {
		mStr = str;
		mBool = bol;
	};

	string mStr; //�׽�ũ�� �̸�
	bool mBool; //�׽�ũ�� �Ϸ� �ƴ���
};

namespace TaskIcon {
	enum {
		USE = 2,
		ADMIN = 6,
		SEQURITY = 7,
		CUSTOMIZE = 0
	};
};

//��� Task�� ����(�÷��̾���� ������) , �������ϴ��� ���ϴ��� ����
class TaskManager : public SingletonBase<TaskManager>
{
public:


	friend class SingletonBase<TaskManager>;

	//ũ��� ������Ʈ
	void Update(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea);

	void Update_crew(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea);
	//�������Ϳ� ������Ʈ
	void Update_imposter(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea);

	void Render();

	void Setting();

	//�÷��̾� �׽�ũ ����Ʈ ����� �������ش�(string)
	void SetPlayerTaskList();
	//�÷��̾� ����Ʈ�� ���� �׽�ũ�� isBlack�� �������ش� /isblakc�� ��������ص��ȴٴ� bool�� ������
	void SetTaskIsBlack();

	//���� �Ϸ�� �׽�ũ�� �ۼ�Ʈ�� ��ȯ�Ѵ�
	int GetTotalTaskComplete();

	int GetActtiveIndex() { return mActtiveIndex; };
	bool GetIsActtiveTask() { return mIsActtiveTask; };
	int GetWhatIcon() { return mWhatIcon; };
	string GetActtiveTaskName() { return mActtiveTaskName; };
	string * GetActtiveTaskNameP() { return &mActtiveTaskName; };
	bool GetIsOpenTask() { return mIsOpenTask; };
	int GetTotalCompleteTask() { return mTotalCompleteTask; };


	//�÷��̾�� �ؿ� �������Ǵµ� �׽�ũ ����Ʈ ������Ʈ ���⼭�ϰ� �������� �������� �ϸ�Ǵ°žƴ�??
	//�װ����� �Լ�
	void RenderPlayerTaskList();


private:

	//�Ⱦ��µ� Ȥ�ɷζ� �ϴ� ���״� ���� ���߿��Ƿ������� ����~~~~~
	//�Ű������� string�� playerTakeList�� �ִ��� Ȯ���Ѵ�
	//����Ʈ�� ���� ������ true ��ȯ, ������ false!
	bool checkIsInPlayerTaskList(string value);

	//�÷��̾��� ����Ʈ�� �ʷϻ����� ĥ���ش�
	//�Ű������� ���� �׽�ũ�� �׽�ũ�̸�[���� - �̼��̸�]
	void setCompletePlayerList(string value);

private:

	const UINT MAX_NEAR_VERY = 150; // NEAR_VERY������ �ִ� ��
	const UINT MAX_NEAR_MIDDLE = 450; //NEAR_MIDDLE�� �ִ� ��

	TaskManager();
	~TaskManager();

	void init();

	vector<Task*> mVacTask; //�׽�ũ ������Ʈ�� ����ִ�
	
	int mActtiveIndex; //���� Ȱ��ȭ���� �׽�ũ�� �ε�����ȣ
	

	//Ui_inGame���� ����Ұ͵�
	bool mIsActtiveTask; //���� Ȱ��ȭ���� �׽�ũ�� �ֽ��ϱ�? ������ true ������ false
	bool mIsOpenTask; // Ȱ��ȭ ���� �׽�ũ�� �����ϴ�������?
	int mWhatIcon; //� �������� ����ϴ���
					/*
					2 - use
					7 - sequrity
					6 - admin
					*/

	string mActtiveTaskName; //� �׽�ũ�� �����Ұ��� ��Ʈ������ ����
							//�׷����� �׽�ũ���� �������ִ� ��Ʈ������ �־�߰ڳ�
							//������ �����̸�_�׽�ũ�̸� �̷������� ����


	//�̼ǵ��� �׽�ũ��� �� �����ص� [ �Ͼ�� ���� ]
	string mTaskList[5] = {
		"Cafeteria: Upload Data",
		"Cafeteria: Empty Chute",
		"Admin: Swipe Card",
		"O2: Divert Power",
		"O2: Clean O2"
	};


	//������ �������� �̾ƴ� �÷��̾� ����Ʈ�� �ִ´�
	stringBool mPlayerTaskList[3];

	int mTotalTask = 3;// �÷��̾��� �� �̼� ����

	int mTotalCompleteTask = 0; //�÷��̾ �Ϸ��� �̼� ����

	bool mListBackMove = false; //����Ʈ�� �����̴�������
	bool mListMoveRight = true; //���� �����̸� ���������ο����̴°�?

	Mesh * mListBackGround;
	float mListBackTransX = 10.0f;
	float mListBackTransY = 520.0f;

	float mListBackMin = -385.0f; //�پ��� �ּҰ�
	float mListBackMax = 10.0f; //Ŀ���� �ִ밪

	float mListMoveFast = 10.0f;// ����Ʈ �̵��ϴ� �ӵ�


};