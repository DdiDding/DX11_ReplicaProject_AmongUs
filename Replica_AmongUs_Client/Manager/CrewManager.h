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

	bool mStartDieAni; //지금 죽는 애니메이션 하고있는지
	bool mEndDieAni; //죽는애니메이션 끝났다 

	ColorMesh * mAllRed; //전체빨강
	Mesh * mFire; //그 불같은거 있짢슴 그거임 ㅋㅋ

	D3DXVECTOR2 mFireSize[3] = { {1500,150}, {1500, 200},{784, 360} };
	D3DXVECTOR2 mFireTrans[3] = { {640, 360}, {640, 360},{640,360} };
	float mFireRotations[3] = { 20.0f, -23.0f, 0.0f };

	float mFireTime = 0.0f;
	float mMaxTime_0 = 0.1f; // 빨간색끝나고 불 등장
	float mMaxTime_1 = 0.1f; //불 2번째 컷
	float mMaxTime_2 = 0.1f; //불 3번째 컷
	int mAniCnt = 0; // 0 -빨간색, 1- 불1,  2- 불2 , 3- 불3

	//죽이는 애니메이션
	AnimationPlayerMesh * mKillAniImposter;
	AnimationPlayerMesh * mKillAniCrew;

	int mWhoIsKill = -1; //누가 죽였는지
};

