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

	//왼손 좌표계 뷰행렬을 생성한다
	D3DXMatrixLookAtLH(&m_viewMatrix, &mPosition, &mLookAt, &mUp);

	return;
}

void Camera::Update(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize)
{
	//일단 플레이어의 중심 좌표값을 가지고있음
	D3DXVECTOR3 playerCenterVec;
	playerCenterVec.x = playerTrans.x + (playerSize.x / 2);
	playerCenterVec.y = playerTrans.y + (playerSize.y / 2);
	
	FollowPlayer(playerCenterVec);
	RandShake(playerCenterVec);

	//카메라 중앙으로맞춰주기 근데 왜 좌측하단이 기준인지 모르겠다 나중에 ㄹ알아보기
	//실제로 값은 바꾸면 안되기때문에 임시로 저장한걸 빼서 중앙으로 맞춰서 사용한다
	D3DXVECTOR3 tempPos = mPosition + mVirtualCameraPos;
	D3DXVECTOR3 tempLook = mLookAt + mVirtualCameraPos;
	
	tempPos.x -= WinMaxWidthHalf;
	tempLook.x -= WinMaxWidthHalf;

	tempPos.y -= WinMaxHeightHalf;
	tempLook.y -= WinMaxHeightHalf;

	//좌측하단 좌표 저장
	mLdCamPos.x = tempPos.x;
	mLdCamPos.y = tempPos.y;

	//왼손 좌표계 뷰행렬을 생성한다
	D3DXMatrixLookAtLH(&m_viewMatrix, &tempPos, &tempLook, &mUp);
}

void Camera::Update_loby(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize)
{

	//일단 플레이어의 중심 좌표값을 가지고있음
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

	//좌측하단 좌표 저장
	mLdCamPos.x = tempPos.x;
	mLdCamPos.y = tempPos.y;

	//왼손 좌표계 뷰행렬을 생성한다
	D3DXMatrixLookAtLH(&m_viewMatrix, &tempPos, &tempLook, &mUp);
}

void Camera::Update_inGame_start()
{
	//왼손 좌표계 뷰행렬을 생성한다
	D3DXMatrixLookAtLH(&m_viewMatrix, &mPosition, &mLookAt, &mUp);
}

void Camera::Update_inGame_end()
{
	//왼손 좌표계 뷰행렬을 생성한다
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
	mMoveVirtualPlayerTime += Time::Get()->Delta();//시간 재기

	if (mMoveVirtualPlayerTime > mMaxMoveTime) {
		//가상플레이어 움직이기 [ 2~5초로 좌표 변경? ]
		//일단 가상 플레이어의 중심 좌표값을 가지고있음 - mVirtualLook
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


	//가상 플레이어(head)와 가상 카메라(tail)사이의 벡터의 크기(스칼라)구하기
	float tempScala = GetVectorLength(mVirtualPlayer, mVirtualCameraPos);


	//단위벡터 구하기
	//머리에서 꼬리를빼서 그 사이의[플레이어와 카메라] 백터의 x,y 를 알아낸다
	mVirtualMove = mVirtualPlayer - mVirtualCameraPos;
	mVirtualMove /= tempScala; //단위벡터 생성
	mVirtualMove *= (tempScala / 100); //거리에 비례해서 속도를 추가함 [멀면 멀수록 빠르게] 뒤에 15는 2차 조절

	//단위벡터의 스칼라 구하기
	float ttScala = GetVectorLength(mVirtualMove, D3DXVECTOR3(0, 0, 0));

	//거리차이가 난ㄷ나면 - 스칼라값이0이아니면 차이나는거지 ㅋㅋ
	//움직일거리 < 플레이어까지의 거리
	mVirtualMove.z = 0;

	//가상 카메라 이동벡터만큼 이동
	mVirtualCameraPos += mVirtualMove;
}

void Camera::FollowPlayer( D3DXVECTOR3 playerCenterPos)
{

	//일단 플레이어의 중심 좌표값을 가지고있음 - playerCenterPos
	

	//플레이어(head)와 카메라(tail)사이의 벡터의 크기(스칼라)구하기
	float tempScala = GetVectorLength(playerCenterPos, mPosition);
	
	
	//단위벡터 구하기
	//머리에서 꼬리를빼서 그 사이의[플레이어와 카메라] 백터의 x,y 를 알아낸다
	playerCenterPos -= mPosition;
	playerCenterPos /= tempScala;
	playerCenterPos *= (tempScala/15); //거리에 비례해서 속도를 추가함

	//단위벡터의 스칼라 구하기
	float ttScala = GetVectorLength(playerCenterPos, D3DXVECTOR3(0, 0, 0));

	//거리차이가 난ㄷ나면 - 스칼라값이0이아니면 차이나는거지 ㅋㅋ
	//움직일거리 < 플레이어까지의 거리
	if (ttScala < tempScala) {
		
		//이동벡터만큼 이동
		PlusCameraPosition(playerCenterPos);
	}

	return;
}

void Camera::SetCamera(D3DXVECTOR3 position)
{
	mPosition = position;
	mLookAt = position;

	//★ z를 모두 같게 하지 말자!
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
	
		//가상플레이어 움직이기 [ 2~5초로 좌표 변경? ]
		//일단 가상 플레이어의 중심 좌표값을 가지고있음 - mVirtualLook
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


	//가상 플레이어(head)와 가상 카메라(tail)사이의 벡터의 크기(스칼라)구하기
	float tempScala = GetVectorLength(mVirtualPlayer, mVirtualCameraPos);


	//단위벡터 구하기
	//머리에서 꼬리를빼서 그 사이의[플레이어와 카메라] 백터의 x,y 를 알아낸다
	mVirtualMove = mVirtualPlayer - mVirtualCameraPos;
	mVirtualMove /= tempScala; //단위벡터 생성
	mVirtualMove *= (tempScala / 5); //거리에 비례해서 속도를 추가함 [멀면 멀수록 빠르게] 뒤에 15는 2차 조절

	//단위벡터의 스칼라 구하기
	float ttScala = GetVectorLength(mVirtualMove, D3DXVECTOR3(0, 0, 0));

	//거리차이가 난ㄷ나면 - 스칼라값이0이아니면 차이나는거지 ㅋㅋ
	//움직일거리 < 플레이어까지의 거리
	mVirtualMove.z = 0;

	//가상 카메라 이동벡터만큼 이동
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
