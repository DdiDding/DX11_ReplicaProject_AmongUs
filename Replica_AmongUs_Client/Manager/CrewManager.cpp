#include "../stdafx.h"
#include "../Geometry/Mesh.h"
#include "../Geometry/ColorMesh.h"
#include "../Geometry/InGame/AnimationPlayerMesh.h"
#include "./PlayerManager.h"
#include "CrewManager.h"

void CrewManager::Update_Last()
{

	//내가 죽었다 && 죽는 애니메이션 하지 않았다
	if (ClientData::Get()->mImDie == true && mEndDieAni == false && mStartDieAni == false) {

		//죽는 애니 시작해라
		mStartDieAni = true;

		//플레이어 유령으로 바꿔라
		PlayerManager::Get()->ChangeMyAni("Player_Ghost"); //유령애니메이션으로 바꿈
		PlayerManager::Get()->ChangeMyShader(L"./Hlsl/PlayerGhostShader.hlsl");
		PlayerManager::Get()->SetIsGhost(true); //유령상태알림

		//시체 세팅
		PlayerManager::Get()->SettingMyDieBody(); 
		
	}
	else if (mStartDieAni == true) {


		if (mAniCnt == 0) {
			mFireTime += Time::Get()->Delta();

			if (mMaxTime_0 < mFireTime) {
				mAniCnt++;
				mFireTime = 0.0f;
			}
		}
		else if (mAniCnt == 1) {
			mFireTime += Time::Get()->Delta();

			if (mMaxTime_1 < mFireTime) {
				mAniCnt++;
				mFireTime = 0.0f;
			}
		}
		else if (mAniCnt == 2) {
			mFireTime += Time::Get()->Delta();

			if (mMaxTime_2 < mFireTime) {
				mAniCnt++;
				mFireTime = 0.0f;
			}
		}

		if (mAniCnt == 0) {
			mAllRed->Update_withCam();
		}
		else {

			mFire->SetTrans(mFireTrans[mAniCnt - 1]);
			mFire->SetSize(mFireSize[mAniCnt - 1]);
			mFire->SetRotation(mFireRotations[mAniCnt - 1]);

			mFire->Update_withCam();
		}

		if (mAniCnt == 3) {

			PlayerColors tempCrewColor = PlayerManager::Get()->GetPlayerColor(ClientData::Get()->mPlayerNum);
			PlayerColors tempImposterColor = PlayerManager::Get()->GetPlayerColor(mWhoIsKill);

			mKillAniImposter->UpdateFromCam(tempImposterColor.mColor_body, tempImposterColor.mColor_body_shadow);
			mKillAniCrew->UpdateFromCam(tempCrewColor.mColor_body, tempCrewColor.mColor_body_shadow);
		}
	}
}

void CrewManager::Render()
{
	//죽는 애니 시작하면
	if (mStartDieAni == true){

		if (mAniCnt == 0) {
			mAllRed->Render();
		}
		else {
			mFire->Render();
		}

		if (mAniCnt == 3) {
			mKillAniImposter->Render();
			mKillAniCrew->Render();
		}


		//만약 애니 끝났다면 애니메이션 종료하기
		if (mKillAniImposter->IsFrameMax() == true) {

			mStartDieAni = false;
			mEndDieAni = true;

			
		}
	}
}

void CrewManager::Setting()
{
	switch (SceneManager::Get()->GetScene())
	{

	case SCENE_INGAME_PLAY: {

		mKillAniImposter = new AnimationPlayerMesh("Kill_Imposter", L"./Hlsl/DiePlayerAnimation.hlsl", true, 398, 254);
		mKillAniCrew = new AnimationPlayerMesh("Kill_Crew", L"./Hlsl/DiePlayerAnimation.hlsl", true, 398, 254);
	}break;
	case SCENE_INGAME_END: {
	
		SAFE_DELETE(mKillAniImposter);
		SAFE_DELETE(mKillAniCrew);

		mStartDieAni = false;
		mWhoIsKill = -1;
		mAniCnt = 0;
		mFireTime = 0.0f;
		mStartDieAni = false;
		mEndDieAni = false;
	} break;
	default:
		break;
	}

}

CrewManager::CrewManager()
{
	init();
}

CrewManager::~CrewManager()
{
}

void CrewManager::init()
{
	mStartDieAni = false;

	mAllRed = new ColorMesh(1280, 720, 0, 0, L"./Hlsl/AllRedShader.hlsl");

	mFire = new Mesh(1538, 220, 643, 357, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/killBackGround.png");
	mFire->SetVertexDataCenter();
}
