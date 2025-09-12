#pragma once

//////////////////////////////////////////////////////////////////////
//통신 보조 용
//////////////////////////////////////////////////////////////////////

//모든 플레이어의 데이터를 이 배열형식으로 관리할거임
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

	bool mExist; //플레이어가 존재하는지
	bool mIsAdmin;
	bool mIsRight; //플레이어가 오른쪽을 보고있는지 [시발ㄴ진짜 개빢치네 오른족이 정방향이다]
	D3DXVECTOR2 mPos; //플레이어의 위치
	string mAniName; //플레이어의 애니메이션 이름
	UINT mFrame; //플레이어의 현재프레임

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


	bool mExist; //플레이어가 존재하는지
	bool mIsRender; //렌더링을 해야하는지
	int mPlayerWhere;//플레이어가 어느 구역에 있는지 //admin맵에 사용됨
	bool mIsImposter;//임포스터인지
	bool mIsDieSecond; //이미죽어있는지
	int mCompleteTask; // 미션 완성한 개수 서버에 넘겨야함
	int mKillNum_crew; //날 죽인 플레이어 번호 -  crew일때
	int mKillNum_imposter; //내가 죽인 플레이어 번호
	bool mIsRight; //플레이어가 오른쪽을 보고있는지 [시발ㄴ진짜 개빢치네 오른족이 정방향이다]
	D3DXVECTOR2 mPos; //플레이어의 위치
	string mAniName; //플레이어의 애니메이션 이름
	UINT mFrame; //플레이어의 현재프레임
};

//////////////////////////////////////////////////////////////////////
//통신용
//////////////////////////////////////////////////////////////////////

//로비 처음들어갈때 받는 구조체
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

//로비에서 계속 데이터 주고받는 구조체
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

	int mSignal; //시그널 번호 - 제일 앞이어야함!
	int mTotalPlayer;
	bool mIsStart; //게임이 시작되는지
	int mPlayerNum; //플레이어의 번호
	bool mImposterList[4];
	LobyPlayerSub mPlayerArray[4];
};


struct sInGame_Play {

	sInGame_Play() {

		mSignal = -1; //신호
		mIsGameEnd = false; //
		mTotalComplete = 0;
		mIsDieFirst = false;
		mIsKill = false;

		mPlayerArray[0] = IngamePlayerSub();
		mPlayerArray[1] = IngamePlayerSub();
		mPlayerArray[2] = IngamePlayerSub();
		mPlayerArray[3] = IngamePlayerSub();
	}

	//게임 진행에있어 필요한 변수
	int mSignal; //신호 
	int mIsGameEnd; // -1은 임포승리 0 은 게임진행 1은 크루 승리
	int mTotalComplete; //미션 완성률을 서버에서 받아야함

	bool mIsDieFirst; //내가 방금! 죽었는지
	bool mIsKill; //내가 누군가를 죽였는지
	
	//플레이어마다 있어야하는것
	IngamePlayerSub mPlayerArray[4];
};