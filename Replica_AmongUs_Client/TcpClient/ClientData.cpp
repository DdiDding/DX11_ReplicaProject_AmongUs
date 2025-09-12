#include "../stdafx.h"
#include "ClientData.h"

void ClientData::Setting()
{
	
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_LOBY: {

		mIsGameEnd = 0;
	}
	break;
	case SCENE_INGAME_END: {
	
		mRequestGameStart = false;
		mIsGameStart = false;

		mImposterList[0] = false;
		mImposterList[1] = false;
		mImposterList[2] = false;
		mImposterList[3] = false;

		mTotalTaskPercent = 0;

		mAnotherPlayer_Data[0] = LobyPlayerSub();
		mAnotherPlayer_Data[1] = LobyPlayerSub();
		mAnotherPlayer_Data[2] = LobyPlayerSub();
		mAnotherPlayer_Data[3] = LobyPlayerSub();

		mAnotherPlayer_inGame[0] = IngamePlayerSub();
		mAnotherPlayer_inGame[1] = IngamePlayerSub();
		mAnotherPlayer_inGame[2] = IngamePlayerSub();
		mAnotherPlayer_inGame[3] = IngamePlayerSub();

		mImDie = false;
		mWhoIsKill = -1;
		mWhoIKilled = -1;

	}break;
	default:
		break;
	}

}

ClientData::ClientData()
{
	init();
}

ClientData::~ClientData()
{
}

void ClientData::init()
{
	mIsAdmin = false;
	mPlayerNum = 0;
	mTotalPlayer = 0;

	mAnotherPlayer_Data[0].mExist = false;
	mAnotherPlayer_Data[1].mExist = false;
	mAnotherPlayer_Data[2].mExist = false;
	mAnotherPlayer_Data[3].mExist = false;

	mRequestGameStart = false;
	mIsGameStart = false;

	mImposterList[0] = false;
	mImposterList[1] = false;
	mImposterList[2] = false;
	mImposterList[3] = false;

	mTotalTaskPercent = 0;

	mAnotherPlayer_inGame[0] = IngamePlayerSub();
	mAnotherPlayer_inGame[1] = IngamePlayerSub();
	mAnotherPlayer_inGame[2] = IngamePlayerSub();
	mAnotherPlayer_inGame[3] = IngamePlayerSub();

	mImDie = false;
	mWhoIsKill = -1;
	mWhoIKilled = -1;
}
