#pragma once

#include "../PipeLine/BufferResource/BufferResource.h"
#include "../PipeLine/Shader/Shader.h"
#include "../PipeLine/BufferResource/VertexDatas.h"
#include "../PipeLine/BufferResource/ConstantStruct.h" //ConstantStruct 에서 상수버퍼의 SubResource를 업데이트



class Mesh
{
public:

	Mesh() {};
	Mesh(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute);
	Mesh(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName);

	~Mesh();

	virtual void Update();
	void Update_withCam();
	void Update_Uv(D3DXVECTOR2 uv0, D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3);
	void Update_ps_int(int value); //1번슬롯에 넣슴
	void Update_player(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow); //플레이어 셰이더 전용 임 머갈통색이랑 몸색을 추가로 contantBuffer통해서 VS로 넘김

	virtual void Render();

	bool IsClik();
	bool IsClik_Center();


	D3DXVECTOR2 GetSize() { return D3DXVECTOR2(mSizeX, mSizeY); };

	void SetShader(LPCWSTR hlslName) { LPCWSTR mHlslName = hlslName; };

	void SetTrans(float transX, float transY) { mTransX = transX;  mTransY = transY; };
	void SetTrans(D3DXVECTOR2 trans) { mTransX = trans.x;  mTransY = trans.y; };
	void SetTrans(D3DXVECTOR3 trans) { mTransX = trans.x;  mTransY = trans.y; };
	void SetTransX(float transX) { mTransX = transX; };
	void SetTransY(float transY) { mTransY = transY; };
	void SetPlusTransX(float value) { mTransX += value; };
	void SetPlusTransY(float value) { 
		mTransY += value; 
		int a = 0;
	};
	void SetMinTransX(float value) { mTransX -= value; };
	void SetPlusTrans(D3DXVECTOR2 plusValue) { mTransX += plusValue.x;  mTransY += plusValue.y; };
	void SetMinTrans(D3DXVECTOR2 plusValue) { mTransX -= plusValue.x;  mTransY -= plusValue.y; };

	void SetRotation(float value) { mRotation = value; };
	void SetPlusRotation(float value) { mRotation += value; };

	void SetSize(D3DXVECTOR2 size) { mSizeX = size.x;  mSizeY = size.y; };
	void SetMulSize(float mulValue) { mSizeX *= mulValue;  mSizeY *= mulValue; };
	void SetPlusSize(D3DXVECTOR2 size) { mSizeX += size.x; mSizeY += size.y; };

	void SetSrv(ID3D11ShaderResourceView * srv) { mSrv = srv; };

	void SetVertexDataCenter();//정점위치를 중심이 가운데로 오게 변경

	D3DXVECTOR2 GetTrans() { return D3DXVECTOR2(mTransX, mTransY); };
	D3DXVECTOR2 GetHalfSize() { return D3DXVECTOR2(mHalfSizeX, mHalfSizeY); };

protected:
	
	void init();

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
	ID3D11Buffer * mConstantBuffer_vs;
	ID3D11Buffer * mConstantBuffer_ps;
	ID3D11Buffer * mConstantBuffer_player;



	//버퍼의 서브리소스
	VertexDatas_texture mVertexData;
	ConstantStruct_matrix mConstantData;
	ConstantStruct_player mConstantData_player;
	//이 메쉬를 컴파일할 hlsl셰이더 경로
	LPCWSTR mHlslName;
	//srv와 결합할 이미지 경로
	WCHAR* mImageRoute;

	//Shader컴파일 파일, 일단은 상수버퍼 가지고있음(분리해야함)
	ID3D11ShaderResourceView * mSrv;
	ID3D11SamplerState * mSamplerState;
	ID3D11BlendState * mBlendState;
	

	//Rect의 World행렬에 사용되는 S, R, T
	float mSizeX;
	float mSizeY;
	float mTransX;
	float mTransY;
	float mRotation = 0;

	//이건 사용할때가 많아서 미리 저장해둠
	float mHalfSizeX;
	float mHalfSizeY;
};

