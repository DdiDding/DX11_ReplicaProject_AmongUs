#pragma once
#include "../stdafx.h"

////////////////////////////////////////////////////////////////////////////////
//ī�޶� Ŭ����
////////////////////////////////////////////////////////////////////////////////
class Camera
{

public:

	Camera();
	~Camera();

	void Update();
	void Update(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize);

	void Update_loby(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize);
	void Update_inGame_start();
	void Update_inGame_end();

	void Setting();


	void RandShake(D3DXVECTOR3 playerPos);
	void FollowPlayer(D3DXVECTOR3 playerPos);

	//ī�޶��� ���߾���ǥ�� ��ȯ��
	//D3DXVECTOR3 GetCameraPos() { return mPosition; }; //���������̿��µ����������� ���� �츮�� �ϳ� ������
	D3DXVECTOR3 GetCameraPos() { return mPosition + mVirtualCameraPos; };
	D3DXVECTOR3 GetCameraPos_onlyCam() { return mPosition; };
	//ī�޶��� �����ϴ� ��ǥ�� ��ȯ��
	D3DXVECTOR2 GetCameraLdPos() { return mLdCamPos; };

	void SetCamera(D3DXVECTOR3 position);

	void PlusCameraPosition(D3DXVECTOR3 moveValue);

	D3DXMATRIX  GetCameraMatrix();

private:

	void camShake(D3DXVECTOR3 playerPos);

private:

	//ī�޶��� �����
	D3DXMATRIX m_viewMatrix;

	//ī�޶��� ���� ��ġ
	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mLookAt;
	D3DXVECTOR3 mUp;

	//�i�ư��� �繰���� �ִ� �Ÿ�
	UINT mMaxInterval;

	//ī�޶��� �����ϴ� ��ǥ - ���� ���̽Ἥ �� ������ ����
	D3DXVECTOR2 mLdCamPos;

	
	//�÷��̾��� ������ �������� ���ƴٴϴ� �ϳ��� ����
	//���� �׷��� ( 0, 0 ) ���� mVirtualMax ������ ���ƴٴϴ°��̤�
	//�̰� ��������mPosition�� �����ָ�ɵ��ϴ�
	//�� ������ �÷��̾���� �Ÿ� (mVirtualMax) ���� ���ƴٴѴ�
	//Worldview�� �����ؾ��ҵ�
	D3DXVECTOR3 mVirtualPlayer; //�������÷��̾�
	D3DXVECTOR3 mVirtualCameraPos; //������ ī�޶�
	D3DXVECTOR3 mVirtualMove; //������ī�޶� ���������ϴ� ��

	float mMoveVirtualPlayerTime = 10.0f;
	float mMaxMoveTime = 1.25f;

	float mVirtualMax = 15.0f;

	float mShakeMax = 30.0f;
};


////////////////////////////////////////////////////////////////////////////////
//���� ī�޶� (�̱���)
////////////////////////////////////////////////////////////////////////////////

class PublicCamera :public SingletonBase<PublicCamera>
{
public:
	friend class SingletonBase<PublicCamera>;

	PublicCamera();
	~PublicCamera();

	Camera * GetCamera() { return mCamera; };
	
private:
	Camera * mCamera;
};