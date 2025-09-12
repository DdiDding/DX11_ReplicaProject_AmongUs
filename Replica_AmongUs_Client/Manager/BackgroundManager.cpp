#include "../stdafx.h"
#include "../Geometry/Mesh.h"
#include "../Geometry/ColorMesh.h"
#include "PlayerManager.h"
#include "../Render.h"
#include "BackgroundManager.h"


////////////////////////////////////////////////////////////////////////////////
//Update
////////////////////////////////////////////////////////////////////////////////
void BackgroundManager::Update()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: Update_mainMenu(); break;

	case SCENE_LOBY: Update_loby(); break;

	case SCENE_INGAME_START: Update_inGame_start(); break;

	case SCENE_INGAME_PLAY:	Update_inGame(); break;

	case SCENE_INGAME_END:	Update_inGame_end(); break;

	default:
		break;
	}
}

void BackgroundManager::Update_mainMenu()
{
	mInGame_Space->Update_ps_float(1.0f);
	mInGame_Space->Update();
	mLogo->Update();
	updateSnowData();
	
	updateCrew();
	for (int index = 0; index < 6; index++) {
		mCrew[index]->Update_player(mCrewData[index].mColor.mColor_body, mCrewData[index].mColor.mColor_body_shadow);
	}

}

void BackgroundManager::Update_loby()
{
	mInGame_Space->Update_ps_float(1.0f);
	mInGame_Space->Update();
	updateSnowData_loby();
	mLoby_map->Update();
}

void BackgroundManager::Update_inGame_start()
{
	mAniTime += Time::Get()->Delta();
	if (mAniNextTime_2 < mAniTime) {
	
		Render::Get()->RequestSetSceneEndManager();
		SceneManager::Get()->SetNextScene(SCENE_INGAME_PLAY);
	}
	else if (mAniNextTime_1 < mAniTime) {
		mInGameWhatAni = true; //���� �ִϸ��̼����� �Ѿ��
	}

	//SHH �ִ� �κ�
	if (mInGameWhatAni == false) {
		mShh_pan->SetPlusRotation(0.1f);

		mShh_son->SetRotation(mPanRotation);

		if (mPanState == 0) {
			mPanRotation += mPanFast;
			if (mPanMaxRotation < mPanRotation) mPanState = 1;
		}
		else if (mPanState == 1) {
			mPanRotation -= mPanFast;
			if (mPanRotation < 0) mPanState = 2;
		}
		else if (mPanState == 2) {
			mPanRotation = 0;

			//����� Ŀ������
			if (mIsShowText == false) {

				mMainTime += Time::Get()->Delta();

				mShh_main->SetSize(mMainMaxSize);
				mShh_main->SetTrans(mMainMaxTrans);

				if (mMainChangeTime < mMainTime) {
					mIsShowText = true;
				}
			}
			//�ٽ� �۾�������
			else {

				mShh_main->SetSize(mMainOriginSize);
				mShh_main->SetTrans(mMainOriginTrans);
			}
		}



		mShh_pan->Update();
		mShh_main->Update();
		mShh_son->Update();
		mShh_front->Update();
		mShh_text->Update();
	}
	//���� �ִ� �κ�
	else {
		
		if (0 < mAllBlackAlpha) {
			mAllBlackAlpha -= 0.005f;
		}
		mInGame_Space->Update_ps_float(mAllBlackAlpha);
		mInGame_Space->Update();

		//�������Ͷ��
		if (ClientData::Get()->mImImposter == true) {
			mShow_imposter->Update();
		}
		else {
			mShow_crew->Update();
		}

		for (UINT index = 0; index < mComPlayer.size(); index++) {

			mComPlayer.at(index)->Update_player(mComPlayerColor[index].mColor_body, mComPlayerColor[index].mColor_body_shadow);
		}

		//�÷��̾� �κ�
		mMainPlayer->Update_player(ClientData::Get()->mPlayerFirstColorBody, ClientData::Get()->mPlayerFirstColorShadow);
		
	}

	
}

void BackgroundManager::Update_inGame()
{
	mInGame_Space->Update();
	mInGame_Map->Update();
}

void BackgroundManager::Update_inGame_end()
{

	if (0 < mAllBlackAlpha) {
		mAllBlackAlpha -= 0.005f;
	}

	//�������� �¸����
	if (ClientData::Get()->mIsGameEnd == -1) {
		mShow_imposter->Update();
	}
	//ũ�� �¸���� 
	else if (ClientData::Get()->mIsGameEnd == 1) {
		mShow_crew->Update();
	}

	for (UINT index = 0; index < mComPlayer.size(); index++) {

		mComPlayer.at(index)->Update_player(mComPlayerColor[index].mColor_body, mComPlayerColor[index].mColor_body_shadow);
	}

	mMainPlayer->Update_player( mEndMainColor.mColor_body, mEndMainColor.mColor_body_shadow);

	mInGame_Space->Update_ps_float(mAllBlackAlpha);
	mInGame_Space->Update();
}



////////////////////////////////////////////////////////////////////////////////
//Render
////////////////////////////////////////////////////////////////////////////////
void BackgroundManager::Render()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: Render_mainMenu(); break;

	case SCENE_LOBY: Render_loby(); break;

	case SCENE_INGAME_START: Render_inGame_start(); break;

	case SCENE_INGAME_PLAY:	Render_inGame(); break;

	case SCENE_INGAME_END: Render_inGame_end(); break;
	default:
		break;
	}
	
}

void BackgroundManager::Render_mainMenu()
{
	mInGame_Space->Render();
	
	renderSnowData();

	mCrew[0]->Render();
	mCrew[1]->Render();
	mCrew[2]->Render();
	mCrew[3]->Render();
	mCrew[4]->Render();
	mCrew[5]->Render();

	mLogo->Render();
}

void BackgroundManager::Render_inGame_start()
{
	if (mInGameWhatAni == false) {
		mShh_pan->Render();
		mShh_main->Render();
		mShh_son->Render();
		mShh_front->Render();
		if (mPanState == 2) {
			mShh_text->Render();
		}
	}
	else {


		//�������Ͷ��
		if (ClientData::Get()->mImImposter == true) {
			mShow_imposter->Render();
			FontManager::Get()->DrawCenter(L"VCR OSD Mono", L"Imposter", 140.0f, 640.0f, 80.0f+ mTextMove, 0xff0000ff);
		}
		else {
			mShow_crew->Render();
			FontManager::Get()->DrawCenter(L"VCR OSD Mono", L"Crew", 140.0f, 640.0f, 80.0f + mTextMove, 0xffff0000);
		}

		//�ƽ�ġ���� ���������� �ؽ�Ʈ �������� �ӵ��� �����ش�
		if ( mTextMove < mTextMaxMove) {
			mTextMove += mTextFast;
		}
		
		for (UINT index = 0; index < mComPlayer.size(); index++) {

			mComPlayer.at(index)->Render();
		}

		mMainPlayer->Render();

		mInGame_Space->Render();

	}
}

void BackgroundManager::Render_inGame()
{
		mInGame_Space->Render();
		renderSnowData();
		mInGame_Map->Render();
}

void BackgroundManager::Render_inGame_end()
{
	

	//�������� �¸����
	if (ClientData::Get()->mIsGameEnd == -1) {
		mShow_imposter->Render();
		FontManager::Get()->DrawCenter(L"VCR OSD Mono", L"Victory", 140.0f, 640.0f, 80.0f + mTextMove, 0xff0000ff);
	}
	//ũ�� �¸����
	else if (ClientData::Get()->mIsGameEnd == 1) {
		mShow_crew->Render();
		FontManager::Get()->DrawCenter(L"VCR OSD Mono", L"Victory", 140.0f, 640.0f, 80.0f + mTextMove, 0xffff0000);
	}
	//�ƽ�ġ���� ���������� �ؽ�Ʈ �������� �ӵ��� �����ش�
	if (mTextMove < mTextMaxMove) {
		mTextMove += mTextFast;
	}

	mMainPlayer->Render();

	for (UINT index = 0; index < mComPlayer.size(); index++) {

		mComPlayer.at(index)->Render();
	}

	mInGame_Space->Render();


	//�κ�� ���������� �غ�
	mEndGameTime += Time::Get()->Delta();
	if (mEndGameMaxTime < mEndGameTime) {

		Render::Get()->RequestSetSceneEndManager();
		SceneManager::Get()->SetNextScene(SCENE_LOBY);
	}
}

void BackgroundManager::Render_loby()
{
	mInGame_Space->Render();
	renderSnowData();
	mLoby_map->Render();
}

void BackgroundManager::Setting()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: {

	}break;

	case SCENE_LOBY: {
		

	}break;

	case SCENE_INGAME_START: {

		mAllBlackAlpha = 1.0f;
		mAniTime = 0.0f;
		mInGameWhatAni = false;
		mPanState = 0;
		

		mIAmImposter = ClientData::Get()->mImImposter;

		mShh_pan = new Mesh(500, 500, 641, 361, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/shh/pan.png");
		mShh_pan->SetVertexDataCenter();
		mShh_main = new Mesh(345, 372, 468, 175, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/shh/main.png");
		mShh_son = new Mesh(131, 394, 578, 0, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/shh/son.png");
		mShh_front = new Mesh(1280, 720, 0, 0, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/shh/front.png");
		mShh_text = new Mesh(405, 105, 438, 75, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/shh/text.png");
	

		mShow_imposter = new Mesh(1280, 720, 0, 0, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/imposter.png");
		mShow_crew = new Mesh(1280, 720, 0, 0, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/crew.png");
		mFadeOut_left = new Mesh(1280, 720, 0, 0, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/fadeOut_left.png");
		mFadeOut_right = new Mesh(1280, 720, 0, 0, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/fadeOut_right.png");
		
		mMainPlayer = new Mesh(153, 215, 563, 168, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png");

		//�÷��̾ ������ŭ ī��Ʈ�ϴ� ����
		int tempPutCnt = 0;
		//�� �÷��̾ŭ �ݺ��Ѵ� 
		for (int index = 0; index < ClientData::Get()->mTotalPlayer; index++) {


			//////////////////////////////////////////////////////////////////////////
			//�ù��϶�
			if (mIAmImposter == false) {
				//�ڽ��ε����� �ƴҶ�
				if (index != ClientData::Get()->mPlayerNum) {

					//ó�� ������ �÷��̾�� slot2�� �ִ´� [�÷��̾� �ٷ� ���� �ڸ�]
					if (tempPutCnt == 0) {
						mComPlayer.push_back(new Mesh(124, 174, 377, 225, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png"));
						mComPlayerColor[0] = PlayerManager::Get()->GetPlayerColor(index);
						tempPutCnt++;
					}
					//�ι�° ������ �÷��̾�� slot3�� �ִ´� [�÷��̾� �ٷ� ������ �ڸ�
					else if (tempPutCnt == 1) {
						mComPlayer.push_back(new Mesh(124, 174, 749, 225, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png"));
						mComPlayerColor[1] = PlayerManager::Get()->GetPlayerColor(index);
						tempPutCnt++;
					}
					//����°������ �÷��̾�� slot1�� �ִ´� [���Ͽ���]
					else if (tempPutCnt == 2) {
						mComPlayer.push_back(new Mesh(93, 127, 229, 278, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png"));
						mComPlayerColor[2] = PlayerManager::Get()->GetPlayerColor(index);
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////
			//���������϶�
			else{

				//�ڽ��ε����� �ƴҶ�
				if (index != ClientData::Get()->mPlayerNum) {

					//ó�� ������ �÷��̾�� slot2�� �ִ´� [�÷��̾� �ٷ� ���� �ڸ�]
					if (tempPutCnt == 0 && ClientData::Get()->mImposterList[index] == true) {
						mComPlayer.push_back(new Mesh(124, 174, 377, 225, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png"));
						mComPlayerColor[0] = PlayerManager::Get()->GetPlayerColor(index);
						tempPutCnt++;
					}
					//�ι�° ������ �÷��̾�� slot3�� �ִ´� [�÷��̾� �ٷ� ������ �ڸ�
					else if (tempPutCnt == 1 && ClientData::Get()->mImposterList[index] == true) {
						mComPlayer.push_back(new Mesh(124, 174, 749, 225, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png"));
						mComPlayerColor[1] = PlayerManager::Get()->GetPlayerColor(index);
						tempPutCnt++;
					}
					//����°������ �÷��̾�� slot1�� �ִ´� [���Ͽ���]
					else if (tempPutCnt == 2 && ClientData::Get()->mImposterList[index] == true) {
						mComPlayer.push_back(new Mesh(93, 127, 229, 278, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png"));
						mComPlayerColor[2] = PlayerManager::Get()->GetPlayerColor(index);
					}
				}
			}
		}
	} break;

	case SCENE_INGAME_PLAY: {
		//delete;
		SAFE_DELETE(mShh_main);
		SAFE_DELETE(mShh_pan);
		SAFE_DELETE(mShh_son);
		SAFE_DELETE(mShh_text);
		SAFE_DELETE(mShh_front);
		

		SAFE_DELETE(mMainPlayer);
		mComPlayer.clear();
		vector<Mesh*>().swap(mComPlayer);



		//create


	} break;

	case SCENE_INGAME_END: {

		mAllBlackAlpha = 1.0f;
		mTextMove = 0.0f; 
		mEndGameTime = 0.0f;

		//ũ��� �¸��϶�
		if (ClientData::Get()->mIsGameEnd == 1) {

			////////////////////////////////
			//���� ũ�� ã�°���
			//���� ũ����϶�!
			if (ClientData::Get()->mImImposter == false) {

				//�� �� ����
				mEndMainColor.mColor_body = PlayerManager::Get()->GetMyColor_body();
				mEndMainColor.mColor_body_shadow = PlayerManager::Get()->GetMyColor_shadow();
				mMainIndex = ClientData::Get()->mPlayerNum; //�ε��� ����
				//���������
				if (ClientData::Get()->mImDie == false) {
					mMainPlayer = new Mesh(153, 215, 563, 168, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png");
				}
				//�׾�����
				else {
					mMainPlayer = new Mesh(153, 215, 563, 168, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/ghostOne.png");
				}
			}
			//���� �������Ϳ��ٸ�
			else {

				int tempIndex = 0; //�ϴ� ó�� �� �÷��̾� �ε��� ������ ���� 

				//�ε��� ã��
				for (int index = 0; index < ClientData::Get()->mTotalPlayer; index++) {

					//�������Ͱ� �ƴҶ� �����Ѵ�
					if (ClientData::Get()->mImposterList[index] == false) {

						//ã�� �÷��̾� �� ����
						mEndMainColor = PlayerManager::Get()->GetPlayerColor(index);
						mMainIndex = index; //�ε��� ����
						tempIndex = index; 
						break;
					}
				}

				//ã�� �÷��̾ ����ִٸ�
				if (ClientData::Get()->mAnotherPlayer_inGame[tempIndex].mIsDieSecond == false) {
					mMainPlayer = new Mesh(153, 215, 563, 168, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png");
				}
				//�׾��ٸ�
				else{
					mMainPlayer = new Mesh(153, 215, 563, 168, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/ghostOne.png");
				}
			}

			////////////////////////////////
			//���� ũ�� ã�°���
			for (int index = 0; index < ClientData::Get()->mTotalPlayer; index++) {


				//////////////////////////////////////////////////////////////////////////
				//�������� �ϵ� ����
				if (ClientData::Get()->mImposterList[index] == false) {

					//�׸��� �����ε���  ������
					if (index != mMainIndex) {

						//ó�� ������ �÷��̾�� slot2�� �ִ´� [�÷��̾� �ٷ� ���� �ڸ�]

						//����Ȯ��
						if (ClientData::Get()->mAnotherPlayer_inGame[index].mIsDieSecond == false) {
							mComPlayer.push_back(new Mesh(124, 174, 377, 225, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png"));
						}
						else {
							mComPlayer.push_back(new Mesh(124, 174, 377, 225, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/ghostOne.png"));
						}
						mComPlayerColor[0] = PlayerManager::Get()->GetPlayerColor(index);
						
					}
				}
			}

		}
		//�������� �¸��϶�
		else if (ClientData::Get()->mIsGameEnd == -1) {

			////////////////////////////////
			//���� ũ�� ã�°���
			//���� ���������϶�!
			if (ClientData::Get()->mImImposter == true) {

				//�� �� ����
				mEndMainColor.mColor_body = PlayerManager::Get()->GetMyColor_body();
				mEndMainColor.mColor_body_shadow = PlayerManager::Get()->GetMyColor_shadow();
				mMainIndex = ClientData::Get()->mPlayerNum; //�ε��� ����
				//���������
				if (ClientData::Get()->mImDie == false) {
					mMainPlayer = new Mesh(153, 215, 563, 168, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png");
				}
				//�׾�����
				else {
					mMainPlayer = new Mesh(153, 215, 563, 168, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/ghostOne.png");
				}
			}
			//���� ũ�翴�ٸ�
			else {

				int tempIndex = 0; //�ϴ� ó�� �� �÷��̾� �ε��� ������ ���� 

				//�ε��� ã��
				for (int index = 0; index < ClientData::Get()->mTotalPlayer; index++) {

					//���������϶�  �����Ѵ�
					if (ClientData::Get()->mImposterList[index] == true) {

						//ã�� �÷��̾� �� ����
						mEndMainColor = PlayerManager::Get()->GetPlayerColor(index);
						mMainIndex = index; //�ε��� ����
						tempIndex = index;
						break;
					}
				}

				//ã�� �÷��̾ ����ִٸ�
				if (ClientData::Get()->mAnotherPlayer_inGame[tempIndex].mIsDieSecond == false) {
					mMainPlayer = new Mesh(153, 215, 563, 168, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png");
				}
				//�׾��ٸ�
				else {
					mMainPlayer = new Mesh(153, 215, 563, 168, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/ghostOne.png");
				}
			}

			////////////////////////////////
			//���� ũ�� ã�°���
			for (int index = 0; index < ClientData::Get()->mTotalPlayer; index++) {


				//////////////////////////////////////////////////////////////////////////
				//ũ�� �ϵ� ����
				if (ClientData::Get()->mImposterList[index] == true) {

					//�׸��� �����ε���  ������
					if (index != mMainIndex) {

						//ó�� ������ �÷��̾�� slot2�� �ִ´� [�÷��̾� �ٷ� ���� �ڸ�]

						//����Ȯ��
						if (ClientData::Get()->mAnotherPlayer_inGame[index].mIsDieSecond == false) {
							mComPlayer.push_back(new Mesh(124, 174, 377, 225, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/stand.png"));
						}
						else {
							mComPlayer.push_back(new Mesh(124, 174, 377, 225, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Player/ghostOne.png"));
						}
						mComPlayerColor[0] = PlayerManager::Get()->GetPlayerColor(index);

					}
				}
			}
		}
	}break;
	default:
		break;
	}
}




void BackgroundManager::putSnowData()
{
	uniform_int_distribution<int> randSize(5, 19);
	uniform_int_distribution<int> ransTransX(10, 1270);
	uniform_int_distribution<int> ransTransY(0, 710);
	uniform_int_distribution<int> randFast(100, 200);


	for (int index = 0; index < mSnowMany; index++) {
		float tempSize = (float)randSize(gen);
		float tempTransX = (float)ransTransX(gen);
		float tempTransY = (float)ransTransY(gen);
		float tempFast = (float)randFast(gen) / 100.0f;
		mSnowData[index] = Snow(D3DXVECTOR2(tempSize, tempSize), D3DXVECTOR3(tempTransX, tempTransY,0), tempFast);
	}
}

void BackgroundManager::updateSnowData()
{
	for (int index = 0; index < mSnowMany; index++) {

		//ȭ�� ��� ��
		if (mSnowData[index].mTrans.x > WinMaxWidth) {

			mSnowData[index].mTrans.x = -10;

			uniform_int_distribution<int> dis(10, 710);
			float tempTranssY = (float)dis(gen);
			mSnowData[index].mTrans.y = tempTranssY;
		}
		else {

			mSnowData[index].mTrans.x += mSnowData[index].mFast;
		}
	}

}

void BackgroundManager::updateSnowData_loby()
{
	for (int index = 0; index < mSnowMany; index++) {

		//ȭ�� ��� ��
		if (mSnowData[index].mTrans.y < 261) {

			//�ʱⰪ ����
			mSnowData[index].mTrans.y = 1720;

			uniform_int_distribution<int> dis(261, 2505);
			float tempTranssX = (float)dis(gen);
			mSnowData[index].mTrans.x = tempTranssX;
		}
		else {

			mSnowData[index].mTrans.y -= mSnowData[index].mFast * 50;
		}
	}
}

void BackgroundManager::renderSnowData()
{
	for (int index = 0; index < mSnowMany; index++) {

		mSnow->SetTrans(mSnowData[index].mTrans);
		mSnow->SetSize(mSnowData[index].mSize);
		mSnow->Update();
		mSnow->Render();
	}
}

void BackgroundManager::initCrew()
{
	uniform_int_distribution<int> randPosX(-100, 1380);
	uniform_int_distribution<int> randPosY(-100, 830);

	uniform_int_distribution<int> randFast(90,800); //1000���� ��������

	uniform_int_distribution<int> randColor(0,8);

	uniform_int_distribution<int> randSize(4,10); //10���� ������ 0.7 / 1.2�������

	uniform_int_distribution<int> randRotation(1,40); //100���� ������ 0.7 / 1.2�������

	//���� ������ ����
	for (int index = 0; index < 6; index++) {

		//��ġ�� �������� ���� �ϴ�
		D3DXVECTOR2 tempStartPos = D3DXVECTOR2((float)randPosX(gen), (float)randPosY(gen));
		//���� ��ġ�� ����
		mCrew[index]->SetTrans(tempStartPos);
		// ȭ���� ��򰡷� �������� ���
		D3DXVECTOR2 tempEndPos = D3DXVECTOR2((float)randPosX(gen), (float)randPosY(gen));

		
		//�� �λ����� �������͸� ���ؼ� fast�� ����
		float tempScala = GetVectorLength(tempEndPos, tempStartPos);
		tempEndPos -= tempStartPos;
		tempEndPos /= tempScala; //�������ͻ���
		tempEndPos *= (float)randFast(gen) / 1000.0f; //�ӵ� �߰������� ����
		mCrewData[index].mCrewFast = tempEndPos; //�ӵ� ����

		//���� �������� ���ؼ� ����
		mCrewData[index].mColor = PlayerManager::Get()->GetPlayerColor(randColor(gen));


		//������ ����
		mCrewData[index].mOriginSize = mCrew[index]->GetSize(); //�� ������ ����
		mCrew[index]->SetMulSize((float)randSize(gen) / 10.0f);

		
		//ȸ��ũ��
		mCrew[index]->SetRotation((float)randPosY(gen));//�ʱ⼼�ð� 
		mCrewData[index].mRotation = (float)randRotation(gen) / 100;

	}
	
}

void BackgroundManager::updateCrew()
{
	//�ӵ� ��� �÷��� ,ȸ���÷�, ���� ����
	for (int index = 0; index < 6; index++) {
		
		mCrew[index]->SetPlusTrans(mCrewData[index].mCrewFast);
		mCrew[index]->SetPlusRotation(mCrewData[index].mRotation);

		//���⼭ �����γ����� �ٽ� �����������~
		if (
			mCrew[index]->GetTrans().y < -200 || 820 < mCrew[index]->GetTrans().y||
			mCrew[index]->GetTrans().x < -200 || 1320 < mCrew[index]->GetTrans().x
			) {

			uniform_int_distribution<int> randPos(-200, 200);
			uniform_int_distribution<int> randPosWindowX(100, 1180);
			uniform_int_distribution<int> randPosWindowY(100, 620);


			uniform_int_distribution<int> randFast(90, 800); //1000���� ��������
			uniform_int_distribution<int> randColor(0, 8);
			uniform_int_distribution<int> randSize(4, 10); //10���� ������ 0.7 / 1.2�������
			uniform_int_distribution<int> randRotation(1, 40); //100���� ������ 0.7 / 1.2�������


			//��ġ�� �������� ���� �ϴ�
			int posX = randPos(gen);
			if (posX >= 0) posX += WinMaxWidth;
			int posY = randPos(gen);
			if (posY >= 0) posY += WinMaxHeight;


			//���� ��ġ�� ����
			D3DXVECTOR2 tempStartPos = D3DXVECTOR2((float)posX, (float)posY);
			mCrew[index]->SetTrans(tempStartPos);
			// ȭ���� ��򰡷� �������� ���
			D3DXVECTOR2 tempEndPos = D3DXVECTOR2((float)randPosWindowX(gen), (float)randPosWindowY(gen));

			//�� �λ����� �������͸� ���ؼ� fast�� ����
			float tempScala = GetVectorLength(tempEndPos, tempStartPos);
			tempEndPos -= tempStartPos;
			tempEndPos /= tempScala; //�������ͻ���
			tempEndPos *= (float)randFast(gen) / 1000.0f; //�ӵ� �߰������� ����
			mCrewData[index].mCrewFast = tempEndPos; //�ӵ� ����

			//���� �������� ���ؼ� ����
			mCrewData[index].mColor = PlayerManager::Get()->GetPlayerColor(randColor(gen));


			//������ ����
			mCrew[index]->SetSize(mCrewData[index].mOriginSize);
			mCrew[index]->SetMulSize((float)randSize(gen) / 10.0f);


			//ȸ��ũ��
			mCrew[index]->SetRotation((float)randPos(gen));//�ʱ⼼�ð� 
			mCrewData[index].mRotation = (float)randRotation(gen) / 100;
		}
	}
}


BackgroundManager::BackgroundManager()
{
	init();
}

BackgroundManager::~BackgroundManager()
{
}

void BackgroundManager::init()
{

	//mainMenu --
	mInGame_Space = new ColorMesh(4874.0f, 3222.0f, 0, 0, L"./Hlsl/AllBlackShader.hlsl");
	mLogo = new Mesh(444, 120, 419, 499, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Logo.png");
	mSnow = new Mesh(19, 19, 100, 100, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/Snow.png");

	mCrew[0] = new Mesh(136, 202, 100, 100, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Background/mainscreenCrew1.png");
	mCrew[1] = new Mesh(139, 220, 200, 100, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Background/mainscreenCrew2.png");
	mCrew[2] = new Mesh(132, 228, 300, 100, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Background/mainscreenCrew3.png");
	mCrew[3] = new Mesh(195, 212, 400, 100, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Background/mainscreenCrew4.png");
	mCrew[4] = new Mesh(184, 185, 500, 100, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Background/mainscreenCrew5.png");
	mCrew[5] = new Mesh(141, 186, 600, 100, L"./Hlsl/Ui_mainMenuCrewShader.hlsl", L"Resorce/Background/mainscreenCrew6.png");
	
	putSnowData();
	initCrew();


	//Loby---
	mLoby_map = new Mesh(2700, 1900, 0, 0, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/lobyFinal.png");

	//inGame --
	mInGame_Map = new Mesh(4874, 3222, 0, 0, L"./Hlsl/TextureShader.hlsl", L"Resorce/Background/FinalMap.png");
}
