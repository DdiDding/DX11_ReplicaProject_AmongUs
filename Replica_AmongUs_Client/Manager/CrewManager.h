#pragma once

class Mesh;
class ColorMesh;
class AnimationPlayerMesh;

class CrewManager : public SingletonBase< CrewManager>
{
public:
	friend class SingletonBase< CrewManager>;

	void Update_Last();

	void Render();

	void SetWhoIsKill(int value) { mWhoIsKill = value; };

	bool GetStartDieAni() { return mStartDieAni; };

	void Setting();

private:
	CrewManager();
	~CrewManager();

	void init();

private:

	bool mStartDieAni; //���� �״� �ִϸ��̼� �ϰ��ִ���
	bool mEndDieAni; //�״¾ִϸ��̼� ������ 

	ColorMesh * mAllRed; //��ü����
	Mesh * mFire; //�� �Ұ����� ��¨�� �װ��� ����

	D3DXVECTOR2 mFireSize[3] = { {1500,150}, {1500, 200},{784, 360} };
	D3DXVECTOR2 mFireTrans[3] = { {640, 360}, {640, 360},{640,360} };
	float mFireRotations[3] = { 20.0f, -23.0f, 0.0f };

	float mFireTime = 0.0f;
	float mMaxTime_0 = 0.1f; // ������������ �� ����
	float mMaxTime_1 = 0.1f; //�� 2��° ��
	float mMaxTime_2 = 0.1f; //�� 3��° ��
	int mAniCnt = 0; // 0 -������, 1- ��1,  2- ��2 , 3- ��3

	//���̴� �ִϸ��̼�
	AnimationPlayerMesh * mKillAniImposter;
	AnimationPlayerMesh * mKillAniCrew;

	int mWhoIsKill = -1; //���� �׿�����
};

