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
		D3DXVECTOR2 mSize; //눈의 크기
		D3DXVECTOR3 mTrans; //눈의 trans
		float mFast; //눈의 빠르기

	};

	struct Crew
	{
		Crew() {};
		Crew(D3DXVECTOR2 crewFast, float rotation) {

			mCrewFast = crewFast;
			mRotation = rotation;
		}

		D3DXVECTOR2 mCrewFast; //크루 움직이는 속도 값 (단위벡터 x 랜덤)
		float mRotation; //크루 회적하는 속도

		D3DXVECTOR2 mOriginSize; //크루의 원래 사이즈

		PlayerColors mColor; //크루원 색상
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

	bool mIAmImposter; //임포스터인지 여기서 저장해놓고 사용하려는 변수

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

	//inGame_start의애니메이션은 2가지다, "shh" 와 등장씬 
	//false면 shh상태이며 true면 등장씬이다
	bool mInGameWhatAni = false;
	float mAniTime = 0.0f;
	float mAniNextTime_1 = 2.5f; //언제 등장씬으로 넘어갈것인가 
	float mAniNextTime_2 = 6.0f; //언제 게임 시잔 씬으로 넘어갈것인가 

	//shh부분
	Mesh * mShh_main;
	Mesh * mShh_pan;
	Mesh * mShh_son;
	Mesh * mShh_text;
	Mesh * mShh_front;

	float mPanRotation = -60;
	float mPanMaxRotation = 6;
	float mPanFast = 1.6f;
	int mPanState = 0; // 0이면 올라가는것, 1이면 내려가는것, 2면 스탑

	D3DXVECTOR2 mMainOriginSize = D3DXVECTOR2(345, 372);
	D3DXVECTOR2 mMainOriginTrans = D3DXVECTOR2(468, 175);

	D3DXVECTOR2 mMainMaxSize = D3DXVECTOR2(399, 430);
	D3DXVECTOR2 mMainMaxTrans = D3DXVECTOR2(441, 146);
	
	float mMainChangeTime = 0.15f; //기준 값
	float mMainTime = 0.0f;//업데이트되는 값

	bool mIsShowText;//텍스트가 보이는지


	//등장씬부분
	Mesh * mShow_imposter;
	Mesh * mShow_crew;

	Mesh * mFadeOut_left;
	Mesh * mFadeOut_right;

	float mFadeOutLength = 5.3f; //페이드아웃 움직이는 거리

	float mTextMove = 0.0f; //글자 움직이는 거리
	float mTextFast = 0.1f; //글자 움직이는 거리
	float mTextMaxMove = 20.0f; //글자 최대내려오는 거리

	float mAllBlackAlpha = 1.0f; //전체 검은 화면

	//등잘할 플레이어들
	Mesh * mMainPlayer;
	vector<Mesh*> mComPlayer;

	PlayerColors mComPlayerColor[3];

	//inGame-----
	//ColorMesh * mInGame_Space;
	Mesh * mInGame_Map;


	//끝날때

	//메인자리
	PlayerColors mEndMainColor; //색
	int mMainIndex; //인덱스,

	//게임끝나고 로비가는 그 시간
	float mEndGameTime = 0.0f;
	float mEndGameMaxTime = 5.0f;
};

