#pragma once

#include "../PipeLine/BufferResource/BufferResource.h"
#include "../PipeLine/Shader/Shader.h"
#include "../PipeLine/BufferResource/VertexDatas.h"
#include "../PipeLine/BufferResource/ConstantStruct.h" //ConstantStruct ���� ��������� SubResource�� ������Ʈ


class AnimationMesh
{
public:

	AnimationMesh(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY);
	~AnimationMesh();

	void Update();
	void Update_progress();
	void UpdateFromCam(bool isReverse, bool isStop);
	void Update_ps_int(int value); //1�����Կ� �ֽ�

	void Render();

	//���� �������� �ִ�ġ����
	bool IsFrameMax();
	//������������ 0 ����
	bool IsFrameZero();


	//���̴� ����
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

	//Buffer�������� �Լ� ���� Ŭ����
	BufferResource mBufferInterface;
	//Shader����� InputLayout���� ��� Ŭ����
	Shader * mShader;


	//�� ���� ���ҽ�
	ID3D11Buffer * mVertexBuffer;
	ID3D11Buffer * mIndexBuffer;
	ID3D11Buffer * mConstantBuffer;
	ID3D11Buffer * mConstantBuffer_ps;


	//������ ���긮�ҽ�
	VertexDatas_texture mVertexData;
	ConstantStruct_matrix mConstantData;
	//�� �޽��� �������� hlsl���̴� ���
	LPCWSTR mHlslName;


	//State �κ�ds
	ID3D11SamplerState * mSamplerState;
	ID3D11BlendState * mBlendState;


	//Rect�� World��Ŀ� ���Ǵ� T, R ( S�� animation �������� �����´� ) 
	//ȭ��ũ���� trans�� �����ϰ� camera�� ���ؼ� ����ϴ��� �Ѵ�
	//������� ���� mTempSize������
	float mTransX;
	float mTransY;
	float mRotation = 0;


	//�ִϸ��̼� �κ�
	Animation mAnimation; //���� �������� �ִϸ��̼�
	string mAniName; //�������ξִϸ��̼� �̸�
	float mFps; // �� Ŭ������ ������ �ִ� �ð�
	UINT mFrame; // Ŭ������ ������ �ִ� �ִϸ��̼� ������
	bool mIsLookingRight;// ��� ������ �ٶ󺸰� �ִ���
	//�ִϸ��̼Ǹ��� ����� �ٸ��� ������ �ϰ��� �ְ� ���̷��� Transration�� ���� ���ִ� �ӽ� ����
	D3DXVECTOR2 mTempSize;
};

