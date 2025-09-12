#pragma once

#include "../PipeLine/BufferResource/BufferResource.h"
#include "../PipeLine/Shader/Shader.h"
#include "../PipeLine/BufferResource/VertexDatas.h"
#include "../PipeLine/BufferResource/ConstantStruct.h" //ConstantStruct ���� ��������� SubResource�� ������Ʈ



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
	void Update_ps_int(int value); //1�����Կ� �ֽ�
	void Update_player(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow); //�÷��̾� ���̴� ���� �� �Ӱ�����̶� ������ �߰��� contantBuffer���ؼ� VS�� �ѱ�

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

	void SetVertexDataCenter();//������ġ�� �߽��� ����� ���� ����

	D3DXVECTOR2 GetTrans() { return D3DXVECTOR2(mTransX, mTransY); };
	D3DXVECTOR2 GetHalfSize() { return D3DXVECTOR2(mHalfSizeX, mHalfSizeY); };

protected:
	
	void init();

	void createSamplerState();

	void createBlendState();

protected:

	//Buffer�������� �Լ� ���� Ŭ����
	BufferResource mBufferInterface;
	//Shader����� InputLayout���� ��� Ŭ����
	Shader * mShader;


	//�� ���� ���ҽ�
	ID3D11Buffer * mVertexBuffer;
	ID3D11Buffer * mIndexBuffer;
	ID3D11Buffer * mConstantBuffer_vs;
	ID3D11Buffer * mConstantBuffer_ps;
	ID3D11Buffer * mConstantBuffer_player;



	//������ ���긮�ҽ�
	VertexDatas_texture mVertexData;
	ConstantStruct_matrix mConstantData;
	ConstantStruct_player mConstantData_player;
	//�� �޽��� �������� hlsl���̴� ���
	LPCWSTR mHlslName;
	//srv�� ������ �̹��� ���
	WCHAR* mImageRoute;

	//Shader������ ����, �ϴ��� ������� ����������(�и��ؾ���)
	ID3D11ShaderResourceView * mSrv;
	ID3D11SamplerState * mSamplerState;
	ID3D11BlendState * mBlendState;
	

	//Rect�� World��Ŀ� ���Ǵ� S, R, T
	float mSizeX;
	float mSizeY;
	float mTransX;
	float mTransY;
	float mRotation = 0;

	//�̰� ����Ҷ��� ���Ƽ� �̸� �����ص�
	float mHalfSizeX;
	float mHalfSizeY;
};

