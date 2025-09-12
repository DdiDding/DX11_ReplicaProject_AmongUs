#include "../stdafx.h"
#include "PlayerManager.h"
#include "UiManager.h"
#include "ImposterManager.h"

void ImposterManager::Update_Last()
{
	//Kill을 했는가?
	if (UiManager::Get()->GetIsSlot1Click() == true) {
		
		//이게 죽인플레이어 인덱스임
		//mIsPossibleKill

		//킬 애니메이션 으로 넘어감
		PlayerManager::Get()->SetMyIsKilling(true);

		ClientData::Get()->mWhoIKilled = GetNearCrewIndex();

		//죽였다고 알림
		mIsKill = true;
	}
}

int ImposterManager::GetNearCrewIndex()
{

	//////////////////////////////////////////////////////////////////
	//목적 : 일단 플레이어 중심점을 구한다
	//////////////////////////////////////////////////////////////////
	D3DXVECTOR2 tempMyTrans = PlayerManager::Get()->GetMyTrans();
	D3DXVECTOR2 tempMySize = PlayerManager::Get()->GetMySize();
	D3DXVECTOR2 tempMyHalfSize = { tempMySize.x / 2 , tempMySize.y / 2 }; //반 거리
	D3DXVECTOR2 tempMyPlayerCenter = { tempMyTrans.x + tempMyHalfSize.x, tempMyTrans.y + tempMyHalfSize.y };

	//각 다른 "크루"와의 거리를 리스트에 담는다
	float nearList[4];
	bool isNear = false; //가까운 크루원이 있는지?

	//모든 플레이어를 검사한다 / 4는 게임총 인원
	for (UINT index = 0; index < 4; index++) {

		//test
		if (Mouse::Get()->Down(1)) {
			int a = 0;
		}
		
		//★다만 자신과의 거리는 필요없고 && 임포스터가 아니어야한다 && 죽은것도 아니어야한다
		if (index != ClientData::Get()->mPlayerNum && ClientData::Get()->mImposterList[index] == false
			&& ClientData::Get()->mAnotherPlayer_inGame[index].mIsDieSecond == false) {

			//상대방의 중심점을 구함
			D3DXVECTOR2 tempAnotherPlayerCenter = ClientData::Get()->mAnotherPlayer_inGame[index].mPos;
			tempAnotherPlayerCenter.x += tempMyHalfSize.x;
			tempAnotherPlayerCenter.y += tempMyHalfSize.y;

			//자신을 제외한 다른 크루원[헤드]와 자신의[꼬리] 거리를 구한다
			float tempDestance = GetVectorLength(tempAnotherPlayerCenter, tempMyPlayerCenter);

			//※거리가 최소 거리 에 들어오면
			if (tempDestance < mMinLegth) {

				nearList[index] = tempDestance;
				isNear = true;
			}
			//※거리가 최소 거리에 들어오지 않으면
			else {

				nearList[index] = 9999;
			}
		}
		//★자신이나 임포스터의 거리 세팅
		else {
			nearList[index] = 9999;
		}
	}

	//만약 가까운 크루원이 있다면
	if (isNear == true) {

		int tempIndex = -1; //플레이어 인덱스를 담을 변수
		float tempMin = 9999; //반복연산하면서 최소값을 계속담을 변수
		//리스트에 담겨진 값을 비교해 제일 가까운 플레이어 인덱스를 찾아낸다
		for (int index = 0; index < 4; index++) {

			//비교대상이 최소값보다 작다면
			if (nearList[index] < tempMin) {

				//값 업데이트
				tempIndex = index;
				tempMin = nearList[index];
			}
		}

		mIsPossibleKill = tempIndex; //값 보관
		return tempIndex;
	}

	mIsPossibleKill = -1; //값 보관
	return -1;
}

void ImposterManager::Setting()
{

	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_INGAME_END: {

		mIsPossibleKill = -1;
		mIsKill = false;
	} break;
	default:
		break;
	}
	
}

ImposterManager::ImposterManager()
{
	init();
}

ImposterManager::~ImposterManager()
{
}

void ImposterManager::init()
{
	mMinLegth = 220.0f;
	mIsPossibleKill = -1;
	mIsKill = false;
}

