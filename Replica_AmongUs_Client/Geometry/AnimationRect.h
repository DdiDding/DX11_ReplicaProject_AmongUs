#pragma once

#include "../PipeLine/BufferResource/BufferResource.h"
#include "../PipeLine/Shader/Shader.h"
#include "../PipeLine/BufferResource/VertexDatas.h"
#include "../PipeLine/BufferResource/ConstantStruct.h" //ConstantStruct 에서 상수버퍼의 SubResource를 업데이트
#include "../Interact/PlayerMove.h"
#include "Debug/DebugPlayer.h"	


class AnimationRect
{
public:

	AnimationRect();
	~AnimationRect();

	void Update();
	void Update_NoMove();

	void Render();

	void SetPlayerPos(D3DXVECTOR2 newTrans) { 
		mTransX = newTrans.x; mTransY = newTrans.y; 
	};

	//애니메이션을 변경한다
	void ChangeAni(string aniName);
	void ChangeShader(LPCWSTR hlslPath);

	void SetIsMoveOK(bool value) { mIsMoveOK = value; };

	void SetIsGhost(bool value) { mIsGhost = value; };

	void SetIsKilling(bool value) { mIsKilling = value; };

	//디버그 라인에 보내기위해 데이터 전송
	D3DXVECTOR2 GetTrans() { return D3DXVECTOR2(mTransX, mTransY); };
	D3DXVECTOR2 GetSize() { return mTempSize; };
	int GetPlayerArea() { return mMyArea; };
	string GetPlayerArea_string() { return mMyArea_string; };

	D3DXVECTOR4 * GetColorBodyP() { return &mColor_body; };
	D3DXVECTOR4 * GetColorBodyShadowP() { return &mColor_body_shadow; };
	float GetFast() { return mFast; };
	D3DXVECTOR3 GetPlayerVector() { return mPlayerVector; };

	string GetAniName() { return mAniName; };
	UINT GetFrame() { return mFrame; };

	bool GetIsRight() { return mIsLookingRight; };
	
	bool GetImGhost() { return mIsGhost; };

private:

	void init();

	void createSamplerState();

	void createBlendState();

private:

	//Buffer생성관련 함수 가진 클래스
	BufferResource mBufferInterface;
	//Shader연결과 InputLayout연결 담당 클래스
	Shader * mShader;


	//각 버퍼 리소스
	ID3D11Buffer * mVertexBuffer;
	ID3D11Buffer * mIndexBuffer;
	ID3D11Buffer * mConstantBuffer;


	//버퍼의 서브리소스
	VertexDatas_texture mVertexData;
	ConstantStruct_player mConstantData;

	//이 메쉬를 컴파일할 hlsl셰이더 경로
	LPCWSTR mHlslName;


	//State 부분
	ID3D11SamplerState * mSamplerState;
	ID3D11BlendState * mBlendState;


	//Rect의 World행렬에 사용되는 T, R ( S는 animation 변수에서 가져온다 ) 
	float mTransX;
	float mTransY;
	float mRotation = 0;

	
	//애니메이션 부분
	Animation mAnimation; //현재 장착중인 애니메이션
	string mAniName;
	float mFps; // 이 클래스가 가지고 있는 시간
	UINT mFrame; // 클래스가 가지고 있는 애니메이션 프레임
	bool mIsLookingRight;// 어느 방향을 바라보고 있는지

	//애니메이션마다 사이즈가 다르기 떄문에 일관성 있게 보이려고 Transration을 조절 해주는 임시 변수
	//현재 Scale의 크기가 들어있음
	D3DXVECTOR2 mTempSize;
	//이 클래스에서 사용할 애니메이션의 기준 사이즈 [AniamtionManager에서 받아옴]
	D3DXVECTOR2 mOriginSize;


	//충돌검사 클래스
	PlayerMove mInteract;
	float mGuideSize = 25;//충돌검사 높이 크기

	//디버그용 라인
	DebugPlayer mDebug;

	bool mIsSpawn;//지금 스폰애니메이션이 실행중인지?
	int mSpwanAniCnt; //스폰애니메이션 카운터, 1이면 1번째 애니, 2면 2번째애니 3이면 애니 바꾸고 스폰 끝내기

	//플레이어용 변수--------------
	int mMyArea; //현재 위치
	string mMyArea_string;
	bool mIsImposter;// 임포스터인지 아닌지 true면 임포스터 fasle면 시민

	//테스크 완료율이 몇퍼센트인지  [ 0 ~ 100 까지 ] [ 시민 전체의 완료율이 아니라 자신만의 완료율임! ]
	int mTaskCompleted;

	//플레이어 색상
	D3DXVECTOR4 mColor_body;
	D3DXVECTOR4 mColor_body_shadow;

	bool mIsMoveOK;//움직일수있는지 아닌지 움직일수 있으면 true, 못움직이면 false

	float mFast;//플레이어의 속도

	//플레이어의 움직임벡터값
	D3DXVECTOR3 mPlayerVector;

	//유령부분------------
	bool mIsGhost = false; //유령상태인지 
	bool mIsDeadBody = false; //시체가 있는지 있으면 true, 없으면 false

	
	//킬러 부분------------
	bool mIsKilling = false; //죽이는 상태인지 1프레임이지만..
	float mKillTime = 0.0f;
	float mKillMaxTime = 0.1f;
	
};

