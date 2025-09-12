#pragma once

#include "../PipeLine/BufferResource/BufferResource.h"
#include "../PipeLine/Shader/Shader.h"
#include "../PipeLine/BufferResource/VertexDatas.h"
#include "../PipeLine/BufferResource/ConstantStruct.h" //ConstantStruct 에서 상수버퍼의 SubResource를 업데이트


class Line
{
public:

	Line();
	~Line();

	virtual void Update();

	virtual void Render();

	
protected:

	void init();

protected:

	//Buffer생성관련 함수 가진 클래스
	BufferResource mBufferInterface;
	//Shader연결과 InputLayout연결 담당 클래스
	Shader * mShader;


	//각 버퍼 리소스
	ID3D11Buffer * mVertexBuffer;
	ID3D11Buffer * mIndexBuffer;
	ID3D11Buffer * mConstantBuffer;


	//버퍼의 서브리소스
	VertexDatas_line mVertexData;
	ConstantStruct_matrix mConstantData;
	LPCWSTR mHlslName = L"./Hlsl/ColorShader.hlsl";


	//Rect의 World행렬에 사용되는 S, T
	float mSizeX;
	float mSizeY;
	float mTransX;
	float mTransY;

};

