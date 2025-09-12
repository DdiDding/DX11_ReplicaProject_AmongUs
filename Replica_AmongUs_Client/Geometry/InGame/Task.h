#pragma once
#include "../Mesh.h"

//테스크와 플레이어 간의 거리 상태
enum {

	NEAR_VERY = 1, //가까움 - 한 테스크만 가능해야한다 이거는 taskManager에서 관리해줌 플레이어와 가장가까운 테스크만 이 상태가가능하게
	NEAR_MIDDLE = 2, //중간
	NEAR_LITTLE = 3 //멀다 or 미션이 아님
};


class Task : public Mesh
{
public:

	Task(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute, int area, int icon, string taskName, bool isYellow);
	~Task();

	void Update() override final;
	void Render() override final;


	void SetNear(UINT state) { mNearToPlayer = state; };
	void SetIsRender(bool value) { mIsRender = value; };
	void SetThisBlack(bool value) { mThisBlack = value; };

	UINT GetNear() { return mNearToPlayer; };
	D3DXVECTOR2 GetCenterPos() { return D3DXVECTOR2(mCenterPosX, mCenterPosY); };
	bool GetIsRender() { return mIsRender; };
	RECT GetRect() { return mRect; };
	int GetArea() { return mArea; };
	int GetIcon() { return mIcon; };
	string GetTaskName() { return mTaskName; };
	bool GetIsYellow() { return mIsYellow; };
	bool GetThisBlack() { return mThisBlack; };

private:

	//랜더링이 되야하는지 [ 카메라 안에 있는지 ]
	bool mIsRender;

	//이 테스크는 검은색만 랜더링해도 될까요? 라는 뜻
	//추가로 완료된 테스크를 의미하기도 한다! true면 무조건 검은색이고 false면 색칠할수있네
	bool mThisBlack;

	//테스크와 플레이어간의 거리상태 값
	UINT mNearToPlayer = 1;

	//중앙 좌표
	float mCenterPosX;
	float mCenterPosY;

	//카메라에 들어가는지 충돌검사하기위한 RECT
	RECT mRect;

	//테스크가 위치한 장소 , 플레이어와 같은곳에 없으면 거리가 가장 멀게 지정된다
	int mArea;

	//이 테스크의 상호작용할 아이콘의 번호는 무엇인지
	int mIcon;

	//연결된 테스크의 이름
	string mTaskName;

	//노란테스크인지 하얀테스크인지.. true면 노란색이다..
	bool mIsYellow;

};


