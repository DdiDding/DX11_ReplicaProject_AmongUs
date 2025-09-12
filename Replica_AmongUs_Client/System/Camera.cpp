#include "../Geometry/AnimationRect.h"
#include "../Manager/PlayerManager.h"
#include "Camera.h"

////////////////////////////////////////////////////////////////////////////////
//Camera class
////////////////////////////////////////////////////////////////////////////////

Camera::Camera()
{
	mPosition = { 0.0f, 0.0f, 0.0f };
	mLookAt = { 0.0f, 0.0f, 1.0f };
	mUp = { 0.0f, 1.0f, 0.0f };

	mMaxInterval = 50;

	mVirtualPlayer = { 0, 0, 0 };
	mVirtualCameraPos = { 0, 0, 0 };
	mVirtualMove = { 0, 0, 0 };
}

Camera::~Camera()
{
}

void Camera::Update()
{

	//�޼� ��ǥ�� ������� �����Ѵ�
	D3DXMatrixLookAtLH(&m_viewMatrix, &mPosition, &mLookAt, &mUp);

	return;
}

void Camera::Update(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize)
{
	//�ϴ� �÷��̾��� �߽� ��ǥ���� ����������
	D3DXVECTOR3 playerCenterVec;
	playerCenterVec.x = playerTrans.x + (playerSize.x / 2);
	playerCenterVec.y = playerTrans.y + (playerSize.y / 2);
	
	FollowPlayer(playerCenterVec);
	RandShake(playerCenterVec);

	//ī�޶� �߾����θ����ֱ� �ٵ� �� �����ϴ��� �������� �𸣰ڴ� ���߿� ���˾ƺ���
	//������ ���� �ٲٸ� �ȵǱ⶧���� �ӽ÷� �����Ѱ� ���� �߾����� ���缭 ����Ѵ�
	D3DXVECTOR3 tempPos = mPosition + mVirtualCameraPos;
	D3DXVECTOR3 tempLook = mLookAt + mVirtualCameraPos;
	
	tempPos.x -= WinMaxWidthHalf;
	tempLook.x -= WinMaxWidthHalf;

	tempPos.y -= WinMaxHeightHalf;
	tempLook.y -= WinMaxHeightHalf;

	//�����ϴ� ��ǥ ����
	mLdCamPos.x = tempPos.x;
	mLdCamPos.y = tempPos.y;

	//�޼� ��ǥ�� ������� �����Ѵ�
	D3DXMatrixLookAtLH(&m_viewMatrix, &tempPos, &tempLook, &mUp);
}

void Camera::Update_loby(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize)
{

	//�ϴ� �÷��̾��� �߽� ��ǥ���� ����������
	D3DXVECTOR3 playerCenterVec;
	playerCenterVec.x = playerTrans.x + (playerSize.x / 2);
	playerCenterVec.y = playerTrans.y + (playerSize.y / 2);

	FollowPlayer(playerCenterVec);
	camShake(playerCenterVec);

	D3DXVECTOR3 tempPos = mPosition + mVirtualCameraPos;
	D3DXVECTOR3 tempLook = mLookAt + mVirtualCameraPos;

	tempPos.x -= WinMaxWidthHalf;
	tempLook.x -= WinMaxWidthHalf;

	tempPos.y -= WinMaxHeightHalf;
	tempLook.y -= WinMaxHeightHalf;

	//�����ϴ� ��ǥ ����
	mLdCamPos.x = tempPos.x;
	mLdCamPos.y = tempPos.y;

	//�޼� ��ǥ�� ������� �����Ѵ�
	D3DXMatrixLookAtLH(&m_viewMatrix, &tempPos, &tempLook, &mUp);
}

void Camera::Update_inGame_start()
{
	//�޼� ��ǥ�� ������� �����Ѵ�
	D3DXMatrixLookAtLH(&m_viewMatrix, &mPosition, &mLookAt, &mUp);
}

void Camera::Update_inGame_end()
{
	//�޼� ��ǥ�� ������� �����Ѵ�
	D3DXMatrixLookAtLH(&m_viewMatrix, &mPosition, &mLookAt, &mUp);
}

void Camera::Setting()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_INGAME_START: 	GETCAMERA->SetCamera(D3DXVECTOR3(0, 0, 0));		break;

	case SCENE_INGAME_PLAY: 	GETCAMERA->SetCamera(D3DXVECTOR3(PlayerManager::Get()->GetMyTrans().x, PlayerManager::Get()->GetMyTrans().y, 0));		break;

	case SCENE_INGAME_END: 		GETCAMERA->SetCamera(D3DXVECTOR3(0, 0, 0));		break;
	}
}

void Camera::RandShake(D3DXVECTOR3 virtualPos)
{
	mMoveVirtualPlayerTime += Time::Get()->Delta();//�ð� ���

	if (mMoveVirtualPlayerTime > mMaxMoveTime) {
		//�����÷��̾� �����̱� [ 2~5�ʷ� ��ǥ ����? ]
		//�ϴ� ���� �÷��̾��� �߽� ��ǥ���� ���������� - mVirtualLook
		uniform_int_distribution<int> dis(-10, 10);

		int tempPlusValue = 5;

		float x = (float)dis(gen);
		if (0 <= x) x += tempPlusValue;
		else if (x < 0) x -= tempPlusValue;

		float y = (float)dis(gen);
		if (0 <= y) y += tempPlusValue;
		else if (y < 0) y -= tempPlusValue;

		mVirtualPlayer.x += x;
		mVirtualPlayer.y += y;

		if (mVirtualPlayer.x < (-mVirtualMax) || mVirtualMax < mVirtualPlayer.x) mVirtualPlayer.x = mVirtualMax - x;
		if (mVirtualPlayer.y < (-mVirtualMax) || mVirtualMax < mVirtualPlayer.y) mVirtualPlayer.y = mVirtualMax - y;

		mMoveVirtualPlayerTime = 0.0f;	
	}


	//���� �÷��̾�(head)�� ���� ī�޶�(tail)������ ������ ũ��(��Į��)���ϱ�
	float tempScala = GetVectorLength(mVirtualPlayer, mVirtualCameraPos);


	//�������� ���ϱ�
	//�Ӹ����� ���������� �� ������[�÷��̾�� ī�޶�] ������ x,y �� �˾Ƴ���
	mVirtualMove = mVirtualPlayer - mVirtualCameraPos;
	mVirtualMove /= tempScala; //�������� ����
	mVirtualMove *= (tempScala / 100); //�Ÿ��� ����ؼ� �ӵ��� �߰��� [�ָ� �ּ��� ������] �ڿ� 15�� 2�� ����

	//���������� ��Į�� ���ϱ�
	float ttScala = GetVectorLength(mVirtualMove, D3DXVECTOR3(0, 0, 0));

	//�Ÿ����̰� �������� - ��Į����0�̾ƴϸ� ���̳��°��� ����
	//�����ϰŸ� < �÷��̾������ �Ÿ�
	mVirtualMove.z = 0;

	//���� ī�޶� �̵����͸�ŭ �̵�
	mVirtualCameraPos += mVirtualMove;
}

void Camera::FollowPlayer( D3DXVECTOR3 playerCenterPos)
{

	//�ϴ� �÷��̾��� �߽� ��ǥ���� ���������� - playerCenterPos
	

	//�÷��̾�(head)�� ī�޶�(tail)������ ������ ũ��(��Į��)���ϱ�
	float tempScala = GetVectorLength(playerCenterPos, mPosition);
	
	
	//�������� ���ϱ�
	//�Ӹ����� ���������� �� ������[�÷��̾�� ī�޶�] ������ x,y �� �˾Ƴ���
	playerCenterPos -= mPosition;
	playerCenterPos /= tempScala;
	playerCenterPos *= (tempScala/15); //�Ÿ��� ����ؼ� �ӵ��� �߰���

	//���������� ��Į�� ���ϱ�
	float ttScala = GetVectorLength(playerCenterPos, D3DXVECTOR3(0, 0, 0));

	//�Ÿ����̰� �������� - ��Į����0�̾ƴϸ� ���̳��°��� ����
	//�����ϰŸ� < �÷��̾������ �Ÿ�
	if (ttScala < tempScala) {
		
		//�̵����͸�ŭ �̵�
		PlusCameraPosition(playerCenterPos);
	}

	return;
}

void Camera::SetCamera(D3DXVECTOR3 position)
{
	mPosition = position;
	mLookAt = position;

	//�� z�� ��� ���� ���� ����!
	mPosition.z = 0;
	mLookAt.z = 1;

	return;
}

void Camera::PlusCameraPosition(D3DXVECTOR3 moveValue)
{
	mPosition += moveValue;
	mLookAt += moveValue;

	mPosition.z = 0;
	mLookAt.z = 1;
}

D3DXMATRIX Camera::GetCameraMatrix()
{
	return m_viewMatrix;
}

void Camera::camShake(D3DXVECTOR3 virtualPos)
{
	
		//�����÷��̾� �����̱� [ 2~5�ʷ� ��ǥ ����? ]
		//�ϴ� ���� �÷��̾��� �߽� ��ǥ���� ���������� - mVirtualLook
		uniform_int_distribution<int> dis(-10, 10);

		int tempPlusValue = 5;

		float x = (float)dis(gen);
		if (0 <= x) x += tempPlusValue;
		else if (x < 0) x -= tempPlusValue;

		float y = (float)dis(gen);
		if (0 <= y) y += tempPlusValue;
		else if (y < 0) y -= tempPlusValue;

		mVirtualPlayer.x += x;
		mVirtualPlayer.y += y;

		if (mVirtualPlayer.x < (-mShakeMax) || mShakeMax < mVirtualPlayer.x) mVirtualPlayer.x = mShakeMax - x;
		if (mVirtualPlayer.y < (-mShakeMax) || mShakeMax < mVirtualPlayer.y) mVirtualPlayer.y = mShakeMax - y;

		mMoveVirtualPlayerTime = 0.0f;


	//���� �÷��̾�(head)�� ���� ī�޶�(tail)������ ������ ũ��(��Į��)���ϱ�
	float tempScala = GetVectorLength(mVirtualPlayer, mVirtualCameraPos);


	//�������� ���ϱ�
	//�Ӹ����� ���������� �� ������[�÷��̾�� ī�޶�] ������ x,y �� �˾Ƴ���
	mVirtualMove = mVirtualPlayer - mVirtualCameraPos;
	mVirtualMove /= tempScala; //�������� ����
	mVirtualMove *= (tempScala / 5); //�Ÿ��� ����ؼ� �ӵ��� �߰��� [�ָ� �ּ��� ������] �ڿ� 15�� 2�� ����

	//���������� ��Į�� ���ϱ�
	float ttScala = GetVectorLength(mVirtualMove, D3DXVECTOR3(0, 0, 0));

	//�Ÿ����̰� �������� - ��Į����0�̾ƴϸ� ���̳��°��� ����
	//�����ϰŸ� < �÷��̾������ �Ÿ�
	mVirtualMove.z = 0;

	//���� ī�޶� �̵����͸�ŭ �̵�
	mVirtualCameraPos += mVirtualMove;
}

////////////////////////////////////////////////////////////////////////////////
//PublicCamera class
////////////////////////////////////////////////////////////////////////////////

PublicCamera::PublicCamera()
{
	mCamera = new Camera();
}

PublicCamera::~PublicCamera()
{
}
