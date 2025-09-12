#pragma once


class ColorMesh
{
public:

	ColorMesh() {};
	ColorMesh(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName);

	~ColorMesh();

	virtual void Update();
	virtual void Render();

	void Update_ps_float(float value); //���� 1����

	void Update_withCam();


	void SetShader(LPCWSTR hlslName) { LPCWSTR mHlslName = hlslName; };
	void SetTrans(float transX, float transY) { mTransX = transX;  mTransY = transY; };
	void SetRotation(float value) { mRotation = value; };

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
	ID3D11Buffer * mConstantBuffer_vs;
	ID3D11Buffer * mConstantBuffer_ps;


	//������ ���긮�ҽ�
	VertexDatas_color mVertexData;
	ConstantStruct_matrix mConstantData;

	//�� �޽��� �������� hlsl���̴� ���
	LPCWSTR mHlslName;


	//Rect�� World��Ŀ� ���Ǵ� S, R, T
	float mSizeX;
	float mSizeY;
	float mTransX;
	float mTransY;
	float mRotation = 0;

};

