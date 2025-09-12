#pragma once

#include "../PipeLine/BufferResource/BufferResource.h"
#include "../PipeLine/Shader/Shader.h"
#include "../PipeLine/BufferResource/VertexDatas.h"
#include "../PipeLine/BufferResource/ConstantStruct.h" //ConstantStruct 에서 상수버퍼의 SubResource를 업데이트


class AnimationMesh
{
public:

	AnimationMesh(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY);
	~AnimationMesh();

	void Update();
	void Update_progress();
	void UpdateFromCam(bool isReverse, bool isStop);
	void Update_ps_int(int value); //1번슬롯에 넣슴

	void Render();

	//현재 프레임이 최대치인지
	bool IsFrameMax();
	//현재프레임이 0 인지
	bool IsFrameZero();


	//셰이더 변경
	void ChangeShader(LPCWSTR hlslPath);


	D3DXVECTOR2 GetTrans() { return D3DXVECTOR2(mTransX, mTransY); };
	void SetTrans(float transX, float transY) { mTransX = transX; mTransY = transY; };
	void SetTrans(D3DXVECTOR2 trans) { mTransX = trans.x; mTransY = trans.y; };

	string GetAniName() { return mAniName; };
	void SetAnimation(string aniName);

	UINT GetFrame() { return mFrame; };
	void SetFrame(UINT frame) { mFrame = frame; };


	bool GetLookingRight() { return mIsLookingRight; };
	void SetIsLookingRight(bool value) { mIsLookingRight = value; };

protected:

	void init(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY);

	void createSamplerState();

	void createBlendState();

protected:

	//Buffer생성관련 함수 가진 클래스
	BufferResource mBufferInterface;
	//Shader연결과 InputLayout연결 담당 클래스
	Shader * mShader;


	//각 버퍼 리소스
	ID3D11Buffer * mVertexBuffer;
	ID3D11Buffer * mIndexBuffer;
	ID3D11Buffer * mConstantBuffer;
	ID3D11Buffer * mConstantBuffer_ps;


	//버퍼의 서브리소스
	VertexDatas_texture mVertexData;
	ConstantStruct_matrix mConstantData;
	//이 메쉬를 컴파일할 hlsl셰이더 경로
	LPCWSTR mHlslName;


	//State 부분ds
	ID3D11SamplerState * mSamplerState;
	ID3D11BlendState * mBlendState;


	//Rect의 World행렬에 사용되는 T, R ( S는 animation 변수에서 가져온다 ) 
	//화면크기의 trans를 저장하고 camera를 더해서 사용하던가 한다
	//사이즈는 밑의 mTempSize에있음
	float mTransX;
	float mTransY;
	float mRotation = 0;


	//애니메이션 부분
	Animation mAnimation; //현재 장착중인 애니메이션
	string mAniName; //장착중인애니메이션 이름
	float mFps; // 이 클래스가 가지고 있는 시간
	UINT mFrame; // 클래스가 가지고 있는 애니메이션 프레임
	bool mIsLookingRight;// 어느 방향을 바라보고 있는지
	//애니메이션마다 사이즈가 다르기 떄문에 일관성 있게 보이려고 Transration을 조절 해주는 임시 변수
	D3DXVECTOR2 mTempSize;
};

