#pragma once
#include "../stdafx.h"

////////////////////////////////////////////////////////////////////////////////
//카메라 클래스
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

	//카메라의 정중앙좌표를 반환함
	//D3DXVECTOR3 GetCameraPos() { return mPosition; }; //원래위쪽이였는데문제있으면 원본 살리고 하나 만들자
	D3DXVECTOR3 GetCameraPos() { return mPosition + mVirtualCameraPos; };
	D3DXVECTOR3 GetCameraPos_onlyCam() { return mPosition; };
	//카메라의 좌측하단 좌표를 반환함
	D3DXVECTOR2 GetCameraLdPos() { return mLdCamPos; };

	void SetCamera(D3DXVECTOR3 position);

	void PlusCameraPosition(D3DXVECTOR3 moveValue);

	D3DXMATRIX  GetCameraMatrix();

private:

	void camShake(D3DXVECTOR3 playerPos);

private:

	//카메라의 뷰행렬
	D3DXMATRIX m_viewMatrix;

	//카메라의 월드 위치
	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mLookAt;
	D3DXVECTOR3 mUp;

	//쫒아가는 사물과의 최대 거리
	UINT mMaxInterval;

	//카메라의 좌측하단 좌표 - 존내 많이써서 걍 저장함 ㅅㅂ
	D3DXVECTOR2 mLdCamPos;

	
	//플레이어의 주위를 가상으로 돌아다니는 하나의 시점
	//말이 그렇지 ( 0, 0 ) 에서 mVirtualMax 안으로 돌아다니는것이ㄷ
	//이걸 마지막에mPosition과 더해주면될듯하다
	//이 시점은 플레이어와의 거리 (mVirtualMax) 내로 돌아다닌다
	//Worldview로 저장해야할듯
	D3DXVECTOR3 mVirtualPlayer; //가상의플레이어
	D3DXVECTOR3 mVirtualCameraPos; //가상의 카메라
	D3DXVECTOR3 mVirtualMove; //가상의카메라가 움직여야하는 값

	float mMoveVirtualPlayerTime = 10.0f;
	float mMaxMoveTime = 1.25f;

	float mVirtualMax = 15.0f;

	float mShakeMax = 30.0f;
};


////////////////////////////////////////////////////////////////////////////////
//공용 카메라 (싱글턴)
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