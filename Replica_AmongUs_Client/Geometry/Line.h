#pragma once

#include "../PipeLine/BufferResource/BufferResource.h"
#include "../PipeLine/Shader/Shader.h"
#include "../PipeLine/BufferResource/VertexDatas.h"
#include "../PipeLine/BufferResource/ConstantStruct.h" //ConstantStruct ���� ��������� SubResource�� ������Ʈ


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

	//Buffer�������� �Լ� ���� Ŭ����
	BufferResource mBufferInterface;
	//Shader����� InputLayout���� ��� Ŭ����
	Shader * mShader;


	//�� ���� ���ҽ�
	ID3D11Buffer * mVertexBuffer;
	ID3D11Buffer * mIndexBuffer;
	ID3D11Buffer * mConstantBuffer;


	//������ ���긮�ҽ�
	VertexDatas_line mVertexData;
	ConstantStruct_matrix mConstantData;
	LPCWSTR mHlslName = L"./Hlsl/ColorShader.hlsl";


	//Rect�� World��Ŀ� ���Ǵ� S, T
	float mSizeX;
	float mSizeY;
	float mTransX;
	float mTransY;

};

