#include "../stdafx.h"
#include "ImposterManager.h"
#include "PlayerManager.h"



void PlayerManager::Setting()
{
	//�κ��϶��� ��ü ����
	if (SceneManager::Get()->GetScene() == SCENE_LOBY) {

		//1.�ϴ� ��� ���ְ� ó������ ��ü ����
		SAFE_DELETE(mPlayer);
		SAFE_DELETE(mPlayerSpawn);
		for (int index = 0; index < 4; index++) {
			SAFE_DELETE(mAnotherPlayerMesh[index]);
			mAnotherPlayerMesh[index] = nullptr;
		}


		//2. �÷��̾� �ڽ� ����
		mPlayer = new AnimationRect();
		mPlayer->SetPlayerPos(ClientData::Get()->mPlayerFirstPos);
		//�������� �ʱ���� �޾ƿͼ� ����
		PlayerManager::Get()->SetColorToPlayer(
			ClientData::Get()->mPlayerNum,
			mPlayer->GetColorBodyP(), mPlayer->GetColorBodyShadowP()
		);


		//3. ��� �÷��̾�� ���⼭ ���� ��� ������Ʈ �ؾ���
		mMyPlayerNum = ClientData::Get()->mPlayerNum;
		for (int index = 0; index < 4; index++) {

			mAnotherPlayerMesh[index] = new AnotherPlayer("Player_Spawn1", L"./Hlsl/NewPlayerShader.hlsl", true, 0, 0);
			*(mAnotherPlayerMesh[index]->GetColorBodyP()) = mPlayerColors[index].mColor_body;
			*(mAnotherPlayerMesh[index]->GetColorBodyShadowP()) = mPlayerColors[index].mColor_body_shadow;
		}
	}
	//�ΰ��� ���� �� ����
	else if (SceneManager::Get()->GetScene() == SCENE_INGAME_PLAY) {
		SetMyPlayerTrans(mPlayerStartPos[ClientData::Get()->mPlayerNum]);

		

		//�������͸� ��� �÷��̾� ���̴����ٲ��ش�
		if (ClientData::Get()->mImImposter == true) {

			for (int index = 0; index < 4; index++) {

				mAnotherPlayerMesh[index]->ChangeShader(L"./Hlsl/ImposterAnotherShader.hlsl");
			}
		}
		//ũ����̸� ��ü�� �ɼ��������ϱ�̸� ����
		else {

			//�ؿ��� ���߿� �ؾ��Ұ��� �ٶ󺸺����� ��ġ,����
			mMyDieBody = new AnimationPlayerMesh("Player_DieBody",L"./Hlsl/NewPlayerShader.hlsl",false,0,0);
		}
	}
	//�׳�������
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

		//ũ����̸�
		if (ClientData::Get()->mImImposter == false) {

			//��ü
			if (mIsDieBodyRender == true) {

				//��ü�� ������Ʈ�Ѵ�
				mMyDieBody->Update_tillLast(mPlayerColors[ClientData::Get()->mPlayerNum].mColor_body, mPlayerColors[ClientData::Get()->mPlayerNum].mColor_body_shadow, mIsDieBodyFrameLast);
				
				//��ü ������ �������̸� ������ ������Ʈ�� ���� �ʴ´�
				if (mMyDieBody->IsFrameMax() == true) {
					mIsDieBodyFrameLast = true;
				}
			}
			anotherUpdate_inGame_crew();
		}
		//�������͸�
		else {

			//���� ����� �÷��̾��� �ε����� �Ű������� ����
			anotherUpdate_inGame_imposter(ImposterManager::Get()->GetNearCrewIndex());
		}

	}break;
	default: break;
	}
}

void PlayerManager::Update_noMove()
{
	mPlayer->Update_NoMove();


	//ũ����̸�
	if (ClientData::Get()->mImImposter == false) {

		anotherUpdate_inGame_crew();
	}
	//�������͸� (cctv�� �׳� ��� -1)
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

		//��ü
		if (mIsDieBodyRender == true) {
			mMyDieBody->Render();
		}

		renderToOrder_inGame();

		//�ڽ� �÷��̾�
		//mPlayer->Render();
		
		//�ٸ� �÷��̾�
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


//��ü�� ������ ����
void PlayerManager::SettingMyDieBody()
{
	//�Ұ�, �ٶ󺸴¹���, ��ġ, �������϶�� �˸�
	mIsDieBodyRender = true;
	mDieBodyTrans = mPlayer->GetTrans();
	mDieBodyLooking = mPlayer->GetIsRight();

	mMyDieBody->SetIsLookingRight(mDieBodyLooking);
	mMyDieBody->SetTrans(mDieBodyTrans);
}



void PlayerManager::anotherUpdate()
{
	for (int index = 0; index < 4; index++) {

		//�ڱ� �ڽ��� �ƴ϶��
		if (index != mMyPlayerNum) {

			//�����ϴ� �÷��̾���
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

		//�ڱ� �ڽ��� �ƴ϶��
		if (index != mMyPlayerNum) {


			//TODO ������ �ƴ϶��
			//�����ϴ� �÷��̾���
			if (ClientData::Get()->mAnotherPlayer_inGame[index].mExist == true) {
				//1��° ���� �����
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

		//�ڱ� �ڽ��� �ƴ϶��
		if (index != mMyPlayerNum) {

			
			//�����ϴ� �÷��̾���
			if (ClientData::Get()->mAnotherPlayer_inGame[index].mExist == true) {

				mAnotherPlayerMesh[index]->SetAnimation(ClientData::Get()->mAnotherPlayer_inGame[index].mAniName);
				mAnotherPlayerMesh[index]->SetTrans(ClientData::Get()->mAnotherPlayer_inGame[index].mPos);
				mAnotherPlayerMesh[index]->SetFrame(ClientData::Get()->mAnotherPlayer_inGame[index].mFrame);
				mAnotherPlayerMesh[index]->SetIsLookingRight(ClientData::Get()->mAnotherPlayer_inGame[index].mIsRight);


				//���ϰ���� �÷��̾�� �׵θ��������ϱ� - 1�� �ָ� �����Եǰ� 0 ���ָ� ������� �������ȴ�
				if (nearIndex == index) {
					mAnotherPlayerMesh[index]->Update_ps_int(1); //�����׵θ�
				}
				else {
					mAnotherPlayerMesh[index]->Update_ps_int(0); //�����̹���
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

	//����ü�� ���� ����Ʈ
	vector<sRenderToOrder> tempList;

	//���� ��ǻ�ͺ��� ��´�
	for (int index = 0; index < 4; index++) {

		if (ClientData::Get()->mAnotherPlayer_Data[index].mExist == true && index != ClientData::Get()->mPlayerNum) {

			tempList.push_back( sRenderToOrder(false, index, mAnotherPlayerMesh[index]->GetTrans().y));
		}
	}

	//���� ��´�
	tempList.push_back(sRenderToOrder(true, 0, mPlayer->GetTrans().y));

	//y�� �������� �����Ѵ� [���������� ���ĵ�]
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

	//����ü�� ���� ����Ʈ
	vector<sRenderToOrder> tempList;

	//���� ��ǻ�ͺ��� ��´�
	for (int index = 0; index < 4; index++) {

		if (ClientData::Get()->mAnotherPlayer_inGame[index].mExist == true && index != ClientData::Get()->mPlayerNum) {

			tempList.push_back(sRenderToOrder(false, index, mAnotherPlayerMesh[index]->GetTrans().y));
		}
	}

	//���� ��´�
	tempList.push_back(sRenderToOrder(true, 0, mPlayer->GetTrans().y));

	//y�� �������� �����Ѵ� [���������� ���ĵ�]
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
	mIsDieBodyFrameLast = false; //�����߿� false�ιٲ���� �׽�Ʈ���� true��
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
	//�����迭
	mPlayerColors[0] = PlayerColors(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.6f, 0.0f, 0.0f, 1.0f));
	//�ʷϰ迭
	mPlayerColors[1] = PlayerColors(D3DXVECTOR4(0.0f, 0.5f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.35f, 0.0f, 1.0f));
	//�Ķ��迭
	mPlayerColors[2] = PlayerColors(D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.6f, 1.0f));
	//�����迭
	mPlayerColors[3] = PlayerColors(D3DXVECTOR4(0.34f, 0.34f, 0.34f, 1.0f), D3DXVECTOR4(0.101f, 0.101f, 0.101f, 1.0f));
	//����迭
	mPlayerColors[4] = PlayerColors(D3DXVECTOR4(0.466f, 0.0f, 0.931f, 1.0f), D3DXVECTOR4(0.196f, 0.0f, 0.354f, 1.0f));
	//�����迭
	mPlayerColors[5] = PlayerColors(D3DXVECTOR4(0.647f, 0.376f, 0, 1.0f), D3DXVECTOR4(0.337f, 0.196f, 0, 1.0f));
	//��ũ�迭
	mPlayerColors[6] = PlayerColors(D3DXVECTOR4(1, 0.294f, 0.811f, 1.0f), D3DXVECTOR4(0.674f, 0.227f, 0.552f, 1.0f));
	//��Ȳ�迭
	mPlayerColors[7] = PlayerColors(D3DXVECTOR4(1, 0.517f, 0, 1.0f), D3DXVECTOR4(0.631f, 0.294f, 0, 1.0f));
	//����迭
	mPlayerColors[8] = PlayerColors(D3DXVECTOR4(1, 1, 0, 1.0f), D3DXVECTOR4(0.803f, 0.643f, 0, 1.0f));
}
