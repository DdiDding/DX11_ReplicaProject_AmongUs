#pragma once


class ColorMesh
{
public:

	ColorMesh() {};
	ColorMesh(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName);

	~ColorMesh();

	virtual void Update();
	virtual void Render();

	void Update_ps_float(float value); //슬롯 1번임

	void Update_withCam();


	void SetShader(LPCWSTR hlslName) { LPCWSTR mHlslName = hlslName; };
	void SetTrans(float transX, float transY) { mTransX = transX;  mTransY = transY; };
	void SetRotation(float value) { mRotation = value; };

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
	ID3D11Buffer * mConstantBuffer_vs;
	ID3D11Buffer * mConstantBuffer_ps;


	//버퍼의 서브리소스
	VertexDatas_color mVertexData;
	ConstantStruct_matrix mConstantData;

	//이 메쉬를 컴파일할 hlsl셰이더 경로
	LPCWSTR mHlslName;


	//Rect의 World행렬에 사용되는 S, R, T
	float mSizeX;
	float mSizeY;
	float mTransX;
	float mTransY;
	float mRotation = 0;

};

