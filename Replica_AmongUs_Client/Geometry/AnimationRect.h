#pragma once

#include "../PipeLine/BufferResource/BufferResource.h"
#include "../PipeLine/Shader/Shader.h"
#include "../PipeLine/BufferResource/VertexDatas.h"
#include "../PipeLine/BufferResource/ConstantStruct.h" //ConstantStruct ���� ��������� SubResource�� ������Ʈ
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

	//�ִϸ��̼��� �����Ѵ�
	void ChangeAni(string aniName);
	void ChangeShader(LPCWSTR hlslPath);

	void SetIsMoveOK(bool value) { mIsMoveOK = value; };

	void SetIsGhost(bool value) { mIsGhost = value; };

	void SetIsKilling(bool value) { mIsKilling = value; };

	//����� ���ο� ���������� ������ ����
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

	//Buffer�������� �Լ� ���� Ŭ����
	BufferResource mBufferInterface;
	//Shader����� InputLayout���� ��� Ŭ����
	Shader * mShader;


	//�� ���� ���ҽ�
	ID3D11Buffer * mVertexBuffer;
	ID3D11Buffer * mIndexBuffer;
	ID3D11Buffer * mConstantBuffer;


	//������ ���긮�ҽ�
	VertexDatas_texture mVertexData;
	ConstantStruct_player mConstantData;

	//�� �޽��� �������� hlsl���̴� ���
	LPCWSTR mHlslName;


	//State �κ�
	ID3D11SamplerState * mSamplerState;
	ID3D11BlendState * mBlendState;


	//Rect�� World��Ŀ� ���Ǵ� T, R ( S�� animation �������� �����´� ) 
	float mTransX;
	float mTransY;
	float mRotation = 0;

	
	//�ִϸ��̼� �κ�
	Animation mAnimation; //���� �������� �ִϸ��̼�
	string mAniName;
	float mFps; // �� Ŭ������ ������ �ִ� �ð�
	UINT mFrame; // Ŭ������ ������ �ִ� �ִϸ��̼� ������
	bool mIsLookingRight;// ��� ������ �ٶ󺸰� �ִ���

	//�ִϸ��̼Ǹ��� ����� �ٸ��� ������ �ϰ��� �ְ� ���̷��� Transration�� ���� ���ִ� �ӽ� ����
	//���� Scale�� ũ�Ⱑ �������
	D3DXVECTOR2 mTempSize;
	//�� Ŭ�������� ����� �ִϸ��̼��� ���� ������ [AniamtionManager���� �޾ƿ�]
	D3DXVECTOR2 mOriginSize;


	//�浹�˻� Ŭ����
	PlayerMove mInteract;
	float mGuideSize = 25;//�浹�˻� ���� ũ��

	//����׿� ����
	DebugPlayer mDebug;

	bool mIsSpawn;//���� �����ִϸ��̼��� ����������?
	int mSpwanAniCnt; //�����ִϸ��̼� ī����, 1�̸� 1��° �ִ�, 2�� 2��°�ִ� 3�̸� �ִ� �ٲٰ� ���� ������

	//�÷��̾�� ����--------------
	int mMyArea; //���� ��ġ
	string mMyArea_string;
	bool mIsImposter;// ������������ �ƴ��� true�� �������� fasle�� �ù�

	//�׽�ũ �Ϸ����� ���ۼ�Ʈ����  [ 0 ~ 100 ���� ] [ �ù� ��ü�� �Ϸ����� �ƴ϶� �ڽŸ��� �Ϸ�����! ]
	int mTaskCompleted;

	//�÷��̾� ����
	D3DXVECTOR4 mColor_body;
	D3DXVECTOR4 mColor_body_shadow;

	bool mIsMoveOK;//�����ϼ��ִ��� �ƴ��� �����ϼ� ������ true, �������̸� false

	float mFast;//�÷��̾��� �ӵ�

	//�÷��̾��� �����Ӻ��Ͱ�
	D3DXVECTOR3 mPlayerVector;

	//���ɺκ�------------
	bool mIsGhost = false; //���ɻ������� 
	bool mIsDeadBody = false; //��ü�� �ִ��� ������ true, ������ false

	
	//ų�� �κ�------------
	bool mIsKilling = false; //���̴� �������� 1������������..
	float mKillTime = 0.0f;
	float mKillMaxTime = 0.1f;
	
};

