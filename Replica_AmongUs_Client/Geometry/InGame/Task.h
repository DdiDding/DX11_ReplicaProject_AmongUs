#pragma once
#include "../Mesh.h"

//�׽�ũ�� �÷��̾� ���� �Ÿ� ����
enum {

	NEAR_VERY = 1, //����� - �� �׽�ũ�� �����ؾ��Ѵ� �̰Ŵ� taskManager���� �������� �÷��̾�� ���尡��� �׽�ũ�� �� ���°������ϰ�
	NEAR_MIDDLE = 2, //�߰�
	NEAR_LITTLE = 3 //�ִ� or �̼��� �ƴ�
};


class Task : public Mesh
{
public:

	Task(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute, int area, int icon, string taskName, bool isYellow);
	~Task();

	void Update() override final;
	void Render() override final;


	void SetNear(UINT state) { mNearToPlayer = state; };
	void SetIsRender(bool value) { mIsRender = value; };
	void SetThisBlack(bool value) { mThisBlack = value; };

	UINT GetNear() { return mNearToPlayer; };
	D3DXVECTOR2 GetCenterPos() { return D3DXVECTOR2(mCenterPosX, mCenterPosY); };
	bool GetIsRender() { return mIsRender; };
	RECT GetRect() { return mRect; };
	int GetArea() { return mArea; };
	int GetIcon() { return mIcon; };
	string GetTaskName() { return mTaskName; };
	bool GetIsYellow() { return mIsYellow; };
	bool GetThisBlack() { return mThisBlack; };

private:

	//�������� �Ǿ��ϴ��� [ ī�޶� �ȿ� �ִ��� ]
	bool mIsRender;

	//�� �׽�ũ�� �������� �������ص� �ɱ��? ��� ��
	//�߰��� �Ϸ�� �׽�ũ�� �ǹ��ϱ⵵ �Ѵ�! true�� ������ �������̰� false�� ��ĥ�Ҽ��ֳ�
	bool mThisBlack;

	//�׽�ũ�� �÷��̾�� �Ÿ����� ��
	UINT mNearToPlayer = 1;

	//�߾� ��ǥ
	float mCenterPosX;
	float mCenterPosY;

	//ī�޶� ������ �浹�˻��ϱ����� RECT
	RECT mRect;

	//�׽�ũ�� ��ġ�� ��� , �÷��̾�� �������� ������ �Ÿ��� ���� �ְ� �����ȴ�
	int mArea;

	//�� �׽�ũ�� ��ȣ�ۿ��� �������� ��ȣ�� ��������
	int mIcon;

	//����� �׽�ũ�� �̸�
	string mTaskName;

	//����׽�ũ���� �Ͼ��׽�ũ����.. true�� ������̴�..
	bool mIsYellow;

};


