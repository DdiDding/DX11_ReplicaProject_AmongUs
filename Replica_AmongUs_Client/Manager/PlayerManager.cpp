#include "../stdafx.h"
#include "ImposterManager.h"
#include "PlayerManager.h"



void PlayerManager::Setting()
{
	//로비일때의 객체 세팅
	if (SceneManager::Get()->GetScene() == SCENE_LOBY) {

		//1.일단 모두 없애고 처음부터 객체 생성
		SAFE_DELETE(mPlayer);
		SAFE_DELETE(mPlayerSpawn);
		for (int index = 0; index < 4; index++) {
			SAFE_DELETE(mAnotherPlayerMesh[index]);
			mAnotherPlayerMesh[index] = nullptr;
		}


		//2. 플레이어 자신 생성
		mPlayer = new AnimationRect();
		mPlayer->SetPlayerPos(ClientData::Get()->mPlayerFirstPos);
		//서버에서 초기색상 받아와서 설정
		PlayerManager::Get()->SetColorToPlayer(
			ClientData::Get()->mPlayerNum,
			mPlayer->GetColorBodyP(), mPlayer->GetColorBodyShadowP()
		);


		//3. 상대 플레이어는 여기서 말고 계속 업데이트 해야함
		mMyPlayerNum = ClientData::Get()->mPlayerNum;
		for (int index = 0; index < 4; index++) {

			mAnotherPlayerMesh[index] = new AnotherPlayer("Player_Spawn1", L"./Hlsl/NewPlayerShader.hlsl", true, 0, 0);
			*(mAnotherPlayerMesh[index]->GetColorBodyP()) = mPlayerColors[index].mColor_body;
			*(mAnotherPlayerMesh[index]->GetColorBodyShadowP()) = mPlayerColors[index].mColor_body_shadow;
		}
	}
	//인게임 들어갔을 때 세팅
	else if (SceneManager::Get()->GetScene() == SCENE_INGAME_PLAY) {
		SetMyPlayerTrans(mPlayerStartPos[ClientData::Get()->mPlayerNum]);

		

		//임포스터면 상대 플레이어 셰이더를바꿔준다
		if (ClientData::Get()->mImImposter == true) {

			for (int index = 0; index < 4; index++) {

				mAnotherPlayerMesh[index]->ChangeShader(L"./Hlsl/ImposterAnotherShader.hlsl");
			}
		}
		//크루원이면 시체가 될수도있으니까미리 세팅
		else {

			//밑에서 나중에 해야할것은 바라보븐방향과 위치,설정
			mMyDieBody = new AnimationPlayerMesh("Player_DieBody",L"./Hlsl/NewPlayerShader.hlsl",false,0,0);
		}
	}
	//겜끝났을때
	else if (SceneManager::Get()->GetScene() == SCENE_INGAME_END) {

		mSpawnEndCnt = 0;
		mIsDieBodyFrameLast = false;
		mIsDieBodyRender = false;
		mDieBodyTrans = { 0,0 };
		mDieBodyLooking = true;
	}
}



void PlayerManager::Update()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: break;

	case SCENE_LOBY: {

		mPlayer->Update();

		anotherUpdate();

	}break;
	case SCENE_INGAME_START: break;

	case SCENE_INGAME_PLAY: {

		mPlayer->Update();

		//크루원이면
		if (ClientData::Get()->mImImposter == false) {

			//시체
			if (mIsDieBodyRender == true) {

				//시체를 업데이트한다
				mMyDieBody->Update_tillLast(mPlayerColors[ClientData::Get()->mPlayerNum].mColor_body, mPlayerColors[ClientData::Get()->mPlayerNum].mColor_body_shadow, mIsDieBodyFrameLast);
				
				//시체 마지막 프레임이면 프레임 업데이트를 하지 않는다
				if (mMyDieBody->IsFrameMax() == true) {
					mIsDieBodyFrameLast = true;
				}
			}
			anotherUpdate_inGame_crew();
		}
		//임포스터면
		else {

			//제일 가까운 플레이어의 인덱스를 매개변수로 넣음
			anotherUpdate_inGame_imposter(ImposterManager::Get()->GetNearCrewIndex());
		}

	}break;
	default: break;
	}
}

void PlayerManager::Update_noMove()
{
	mPlayer->Update_NoMove();


	//크루원이면
	if (ClientData::Get()->mImImposter == false) {

		anotherUpdate_inGame_crew();
	}
	//임포스터면 (cctv라 그냥 모두 -1)
	else {
		anotherUpdate_inGame_imposter(-1);
	}

}

void PlayerManager::Render()
{

	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: break;

	case SCENE_LOBY: {

		renderToOrder_loby();
		/*mPlayer->Render();
		anotherRender();*/

	}	break;
	case SCENE_INGAME_START: break;

	case SCENE_INGAME_PLAY: {

		//시체
		if (mIsDieBodyRender == true) {
			mMyDieBody->Render();
		}

		renderToOrder_inGame();

		//자신 플레이어
		//mPlayer->Render();
		
		//다른 플레이어
		//anotherRender_inGame();


	}	break;
	default: break;
	}

}


void PlayerManager::SetColorToPlayer(int index, D3DXVECTOR4 * playerBody, D3DXVECTOR4 * playerBodyShadow)
{
	*(playerBody) = ClientData::Get()->mPlayerFirstColorBody;
	*(playerBodyShadow) = ClientData::Get()->mPlayerFirstColorShadow;
}


//시체의 세팅을 맡음
void PlayerManager::SettingMyDieBody()
{
	//할것, 바라보는방향, 위치, 랜더링하라고 알림
	mIsDieBodyRender = true;
	mDieBodyTrans = mPlayer->GetTrans();
	mDieBodyLooking = mPlayer->GetIsRight();

	mMyDieBody->SetIsLookingRight(mDieBodyLooking);
	mMyDieBody->SetTrans(mDieBodyTrans);
}



void PlayerManager::anotherUpdate()
{
	for (int index = 0; index < 4; index++) {

		//자기 자신이 아니라면
		if (index != mMyPlayerNum) {

			//존재하는 플레이어라면
			if (ClientData::Get()->mAnotherPlayer_Data[index].mExist == true) {

				mAnotherPlayerMesh[index]->SetAnimation(ClientData::Get()->mAnotherPlayer_Data[index].mAniName);
				mAnotherPlayerMesh[index]->SetTrans(ClientData::Get()->mAnotherPlayer_Data[index].mPos);
				mAnotherPlayerMesh[index]->SetFrame(ClientData::Get()->mAnotherPlayer_Data[index].mFrame);
				mAnotherPlayerMesh[index]->SetIsLookingRight(ClientData::Get()->mAnotherPlayer_Data[index].mIsRight);

				mAnotherPlayerMesh[index]->Update();
			}
		}
		
	}
}

void PlayerManager::anotherUpdate_inGame_crew()
{
	for (int index = 0; index < 4; index++) {

		//자기 자신이 아니라면
		if (index != mMyPlayerNum) {


			//TODO 유령이 아니라면
			//존재하는 플레이어라면
			if (ClientData::Get()->mAnotherPlayer_inGame[index].mExist == true) {
				//1번째 돌때 여기다
				mAnotherPlayerMesh[index]->SetAnimation(ClientData::Get()->	mAnotherPlayer_inGame[index].mAniName);
				mAnotherPlayerMesh[index]->SetTrans(ClientData::Get()->	mAnotherPlayer_inGame[index].mPos);
				mAnotherPlayerMesh[index]->SetFrame(ClientData::Get()->	mAnotherPlayer_inGame[index].mFrame);
				mAnotherPlayerMesh[index]->SetIsLookingRight(ClientData::Get()->mAnotherPlayer_inGame[index].mIsRight);

				mAnotherPlayerMesh[index]->Update();
			}
		}

	}
}

void PlayerManager::anotherUpdate_inGame_imposter(int nearIndex)
{
	for (int index = 0; index < 4; index++) {

		//자기 자신이 아니라면
		if (index != mMyPlayerNum) {

			
			//존재하는 플레이어라면
			if (ClientData::Get()->mAnotherPlayer_inGame[index].mExist == true) {

				mAnotherPlayerMesh[index]->SetAnimation(ClientData::Get()->mAnotherPlayer_inGame[index].mAniName);
				mAnotherPlayerMesh[index]->SetTrans(ClientData::Get()->mAnotherPlayer_inGame[index].mPos);
				mAnotherPlayerMesh[index]->SetFrame(ClientData::Get()->mAnotherPlayer_inGame[index].mFrame);
				mAnotherPlayerMesh[index]->SetIsLookingRight(ClientData::Get()->mAnotherPlayer_inGame[index].mIsRight);


				//제일가까운 플레이어면 테두리빨갛게하기 - 1을 주면 빨갛게되고 0 을주면 원래대로 렌더링된다
				if (nearIndex == index) {
					mAnotherPlayerMesh[index]->Update_ps_int(1); //빨간테두리
				}
				else {
					mAnotherPlayerMesh[index]->Update_ps_int(0); //원본이미지
				}
				mAnotherPlayerMesh[index]->Update();
			}
		}///if(index)
	}///for
}

void PlayerManager::anotherRender()
{

	for (int index = 0; index < 4; index++) {

		if (ClientData::Get()->mAnotherPlayer_Data[index].mExist == true) {

			mAnotherPlayerMesh[index]->Render();
		}
	}
}

void PlayerManager::anotherRender_inGame()
{
	for (int index = 0; index < 4; index++) {

		if (ClientData::Get()->mAnotherPlayer_inGame[index].mExist == true) {

			mAnotherPlayerMesh[index]->Render();
		}
	}
}

void PlayerManager::renderToOrder_loby()
{

	//구조체를 담을 리스트
	vector<sRenderToOrder> tempList;

	//먼저 컴퓨터부터 담는다
	for (int index = 0; index < 4; index++) {

		if (ClientData::Get()->mAnotherPlayer_Data[index].mExist == true && index != ClientData::Get()->mPlayerNum) {

			tempList.push_back( sRenderToOrder(false, index, mAnotherPlayerMesh[index]->GetTrans().y));
		}
	}

	//나를 담는다
	tempList.push_back(sRenderToOrder(true, 0, mPlayer->GetTrans().y));

	//y를 기준으로 정렬한다 [작은순으로 정렬됨]
	sort(tempList.begin(), tempList.end(), compare);

	for (int index = 0; index < tempList.size(); index++) {

		if (tempList.at(index).mIsMe == true) {
			mPlayer->Render();
		}
		else {
			mAnotherPlayerMesh[tempList.at(index).mIndex]->Render();
		}
	}
}

void PlayerManager::renderToOrder_inGame()
{

	//구조체를 담을 리스트
	vector<sRenderToOrder> tempList;

	//먼저 컴퓨터부터 담는다
	for (int index = 0; index < 4; index++) {

		if (ClientData::Get()->mAnotherPlayer_inGame[index].mExist == true && index != ClientData::Get()->mPlayerNum) {

			tempList.push_back(sRenderToOrder(false, index, mAnotherPlayerMesh[index]->GetTrans().y));
		}
	}

	//나를 담는다
	tempList.push_back(sRenderToOrder(true, 0, mPlayer->GetTrans().y));

	//y를 기준으로 정렬한다 [작은순으로 정렬됨]
	sort(tempList.begin(), tempList.end(), compare);

	for (int index = 0; index < tempList.size(); index++) {

		if (tempList.at(index).mIsMe == true) {
			mPlayer->Render();
		}
		else {
			mAnotherPlayerMesh[tempList.at(index).mIndex]->Render();
		}
	}
}


PlayerManager::PlayerManager()
{
	init();
}


PlayerManager::~PlayerManager()
{
}


void PlayerManager::init()
{
	mSpawnEndCnt = 0;
	mIsDieBodyFrameLast = false; //낮나중에 false로바꿔야함 테스트용임 true는
	mIsDieBodyRender = false;
	mDieBodyTrans = { 0,0 };
	mDieBodyLooking = true;

	defineColor();
	for (int index = 0; index < 4; index++) {
		mPlayerStartPos[index] = D3DXVECTOR2((float)2300+(index * 200), 1900);
	}
}


void PlayerManager::defineColor()
{
	//빨간계열
	mPlayerColors[0] = PlayerColors(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.6f, 0.0f, 0.0f, 1.0f));
	//초록계열
	mPlayerColors[1] = PlayerColors(D3DXVECTOR4(0.0f, 0.5f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.35f, 0.0f, 1.0f));
	//파란계열
	mPlayerColors[2] = PlayerColors(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.6f, 1.0f));
	//검은계열
	mPlayerColors[3] = PlayerColors(D3DXVECTOR4(0.34f, 0.34f, 0.34f, 1.0f), D3DXVECTOR4(0.101f, 0.101f, 0.101f, 1.0f));
	//보라계열
	mPlayerColors[4] = PlayerColors(D3DXVECTOR4(0.466f, 0.0f, 0.931f, 1.0f), D3DXVECTOR4(0.196f, 0.0f, 0.354f, 1.0f));
	//갈색계열
	mPlayerColors[5] = PlayerColors(D3DXVECTOR4(0.647f, 0.376f, 0, 1.0f), D3DXVECTOR4(0.337f, 0.196f, 0, 1.0f));
	//핑크계열
	mPlayerColors[6] = PlayerColors(D3DXVECTOR4(1, 0.294f, 0.811f, 1.0f), D3DXVECTOR4(0.674f, 0.227f, 0.552f, 1.0f));
	//주황계열
	mPlayerColors[7] = PlayerColors(D3DXVECTOR4(1, 0.517f, 0, 1.0f), D3DXVECTOR4(0.631f, 0.294f, 0, 1.0f));
	//노란계열
	mPlayerColors[8] = PlayerColors(D3DXVECTOR4(1, 1, 0, 1.0f), D3DXVECTOR4(0.803f, 0.643f, 0, 1.0f));
}
