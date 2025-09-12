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

		Mesh * mLeafMesh;//메쉬
		bool mIsMove; //마우스를 클릭해서 이동중인지
		bool mIsOuting;//빨려들어가는 중인지
		bool mIsComplete; //안에 넣어졌는지

		D3DXVECTOR2 mUintTrans;//이동하는 단위벡터
		D3DXVECTOR2 mLeafMinFast; //줄어드는 속도벡터 단위벡터의 한 ㄴ5분의1?

		D3DXVECTOR2 mLeafTrans;//올라가고 내려가는거떔에 원 y값저장할 변수
	};

	void init();

	void initLeaf();
	void updateLeaf();
	void renderLeaf();

	//화면 위  오른쪽  아래 부분중 어느부분이 맞았는지 알수있다
	//0이면 정상이고 [안부딛힘] 1이면 위쪽/ 2면 오른쪽 / 3이면 아래쪽이다
	int isOut(D3DXVECTOR2 leafTrans, D3DXVECTOR2 leafSize);

	//나뭇잎중 하나라도 클릭했는가?
	bool isLeafClick();

private:

	//공용 ------------------
	bool mIsComplete; //미션을 완료했는지 - 100%가 되면 true가 됩니다
	bool mClickEnd; // X버튼 눌렀는가??



	// 같이 움직이기 위한 변수---------

	bool mIsUp = true;//위로 올라가는중인가?
	float mAllMeshMove = -576.0f;
	float mAllMeshMoveMin = -576.0f; //최소값 [ 최대값은 0이다 ]
	float mAllMeshMoveFast = 60; //속도

	//내려갈때----------
	float mDownMaxTime = 1.2f;//몇초 지나야 자동으로 내려갈건지
	float mDownTime = 0.0f; //시간재는 변수


	// 매쉬들 -------------------
	Mesh * mClosseBtn;

	Mesh * mBackGround; //뒷배경
	Mesh * mFront; //앞 뚜껑 부분

	Mesh * mRightCompleteArrow; // 완료된 초록 호ㅏ살표
	Mesh * mLeftCompleteArrow; // 완료된 초록 호ㅏ살표
	
	
	bool mActtiveArrow; //true면 화살표 애니 켠다
	AnimationMesh * mRightArrow; //마우스 누르면 진행되는애니메이션
	AnimationMesh * mLeftArrow; //마우스 누르면 진행되는애니메이션

	sLeaf mLeaf[7]; //나뭇잎들
	float mLeafFast; //나뭇잎 속도들
	D3DXVECTOR2 mLeatOutPoint = { 65, 360 }; //나뭇잎이 빨려들게하는 원점
	float mLeafOutX = 520.0f; //나뭇잎이 빨려들어가는 기준 x위치

	int mLeatOutCnt = 0; //나뭇잎이 들어간 카운터
};

