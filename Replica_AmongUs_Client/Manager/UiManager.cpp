#include "../stdafx.h"
#include "../Manager/PlayerManager.h"
#include "../Render.h"
#include "UiManager.h"


////////////////////////////////////////////////////////////////////////////////
//Update
////////////////////////////////////////////////////////////////////////////////
void UiManager::Update()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: Update_mainMenu(); break;

	case SCENE_LOBY: Update_loby(); break;

	case SCENE_INGAME_PLAY:	Update_inGame(); break;

	default:
		break;
	}
}

void UiManager::Update_mainMenu()
{
	if (mStart->IsClik() == true) { 
		mStart->Update_ps_int(1); 
	}
	else mStart->Update_ps_int(0);
	if (mExit->IsClik() == true) mExit->Update_ps_int(1);
	else mExit->Update_ps_int(0);
	if (mSetting->IsClik() == true) mSetting->Update_ps_int(1);
	else mSetting->Update_ps_int(0);
	if (mNaver->IsClik() == true) mNaver->Update_ps_int(1);
	else mNaver->Update_ps_int(0);

	mStart->Update();
	mExit->Update();
	mSetting->Update();
	mNaver->Update();

	if (Mouse::Get()->Down(1) == true || Keyboard::Get()->Down(VK_RETURN) == true) {
		if (mStart->IsClik() == true || Keyboard::Get()->Down(VK_RETURN) == true) {
			//�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
			//������ - �ٲٴ°� �̷��� �ΰ� �ϸ� �ȴ�
			//�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
			Render::Get()->RequestSetSceneEndManager();
			SceneManager::Get()->SetNextScene(SCENE_LOBY);
		};
		if (mNaver->IsClik() == true) { system("explorer https://blog.naver.com/kdjwand"); }
	}
}

void UiManager::Update_loby()
{
	
	//�����϶��� ������Ʈ
	if (ClientData::Get()->mIsAdmin == true) {

		mGameStart->Update_withCam();
		mGameStart->Update_ps_int((int)mIsPossibleStart);
		
		//�ѿ� �θ��̻��϶� ���콺 ��ȣ�ۿ밡���ϰ� ��ư�� ������������
		if (ClientData::Get()->mTotalPlayer >= 2) mIsPossibleStart = true;


		if (Mouse::Get()->Down(1) == true) {

			if (mGameStart->IsClik() == true) {

				

				if (mIsPossibleStart == true) {
					//�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
					//������
					//�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
					ClientData::Get()->mRequestGameStart = true;
					/*SceneManager::Get()->SetScene(SCENE_INGAME_START);
					PlayerManager::Get()->SetMyPlayerTrans(D3DXVECTOR2(2660, 1900));*/
				}
				else {
					mGomujulActtive = true;
				}
			}
		}


		//���� �ִϸ��̼� ������Ʈ
		if (mGomujulActtive == true) { updateGomujul(); }
	}

	mTotalIcon->Update_withCam();
}

void UiManager::Update_inGame()
{
	//���콺 ���� ����
	if (mIsOpenMiniMap == false) {

		if (Mouse::Get()->Down(1) || Keyboard::Get()->Down('M') == true) {
			if (mMiniMapBtn->IsClik() == true || Keyboard::Get()->Down('M') == true) {
				mIsOpenMiniMap = !mIsOpenMiniMap;
			}
		}
	}
	else {

		if (Mouse::Get()->Down(1) || Keyboard::Get()->Down('M') == true) {
			if (mMiniMapCloseBtn->IsClik() == true || Keyboard::Get()->Down('M') == true) {
				mIsOpenMiniMap = !mIsOpenMiniMap;
			};
		}
	}


	//������ ���� ����
	if (mIsOpenMiniMap == false) {

		mMiniMapBtn->Update_withCam();
		mUiInGame->Update(ClientData::Get()->mImImposter);
	}
	else if (mIsOpenMiniMap == true) {

		mUiMiniMap->Update();
		mMiniMapCloseBtn->Update_withCam();
	}

	string tempArea = PlayerManager::Get()->GetMyArea_string();
	//�̼���ҿ� �ִٸ� ���ڿ��� ��ü���ش�
	if (findTextLoby(tempArea) == false) {

		mPlayerArea = tempArea;
		mIsBeInLoby = false;
	}
	//���� �κ� �ִٸ� ���� �������ִ��ɰ�� ������ �ִ´� ������ ���ϴ� �ؽ�Ʈ �ö���°Ͷ���;;
	else {
		mIsBeInLoby = true;
	}
}



////////////////////////////////////////////////////////////////////////////////
//Render
////////////////////////////////////////////////////////////////////////////////
void UiManager::Render()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: Render_mainMenu(); break;

	case SCENE_LOBY: Render_loby(); break;


	case SCENE_INGAME_PLAY:	Render_inGame(); break;

	default:
		break;
	}
}

void UiManager::Render_mainMenu()
{
	mStart->Render();
	mExit->Render();
	mSetting->Render();
	mNaver->Render();
}

void UiManager::Render_loby()
{
	//���常 ��������
	if(ClientData::Get()->mIsAdmin ==  true) mGameStart->Render();

	mTotalIcon->Render();

	wstring tempWstr = to_wstring(ClientData::Get()->mTotalPlayer) + L" / 4";
	WCHAR * tempWchar = _wcsdup(tempWstr.c_str());

	/*if (tempWchar == NULL) {
		int a = 0;
	}*/

	UINT32 color = 0xff0000ff; //�̰Ժ��??
	if (ClientData::Get()->mTotalPlayer > 1) color = 0xff00ff00;
	FontManager::Get()->DrawCenter_border(L"Varela", tempWchar, 20.0f, mTextOriginPos + mGoumujulTotal, 645.0f, color, 0xff000000, 1);
	free(tempWchar);
	//570, 45
}

void UiManager::Render_inGame()
{
	if (mIsOpenMiniMap == true) {

		mUiMiniMap->Render();
		mMiniMapCloseBtn->Render();
	}
	else {
		mMiniMapBtn->Render();

		mUiInGame->Render(ClientData::Get()->mImImposter);
	}


	//���ϴ� ������� �ؽ�Ʈ�� ���
	wstring tempWstr = L"";
	tempWstr.assign(mPlayerArea.begin(), mPlayerArea.end());
	WCHAR * tempWchar = _wcsdup(tempWstr.c_str());
	FontManager::Get()->DrawCenter_border(L"HYHeadLine", tempWchar, 32.0f, mAreaTransX, mAreaTransY, 0xffffffff, 0xff000000, 2);
	free(tempWchar);

	//������ Loby��´ܾ ������ [�̼���ҿ� ������] , �ؽ�Ʈ�� �ö󰡴µ� �ƽ�ġ�������ö󰡴°�!
	if (mIsBeInLoby == false) {

		if (mAreaTransY > mAreaTextYMax)
			mAreaTransY -= mAreaTextFast;
	}
	//���� Loby�϶�!, �ؽ�Ʈ�� �������µ� �ּҰ��������������°�@
	else {

		if (mAreaTransY < mAreaTextYMin)
			mAreaTransY += mAreaTextFast;
	}
}



////////////////////////////////////////////////////////////////////////////////
//��Ÿ �Լ�
////////////////////////////////////////////////////////////////////////////////

void UiManager::Setting()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: {

	}break;

	case SCENE_LOBY: {
		//Loby-------------------------------------

		mGameStart = new Mesh(185, 107, 548, 100, L"./Hlsl/NonActtiveShader.hlsl", L"Resorce/Ui/Ui_Start.png");
		mTotalIcon = new Mesh(36, 36, 570, 45, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/playerIcon.png");

		mIsPossibleStart = false;

		//����
		setGomujul();
		mIconOriginPos = 570.0f;
		mTextOriginPos = 640.0f;
		mGomujulIndex = 0;
		mGomujulActtive = false;
		mGomujulFast = 23;
		mGoumujulTotal = 0;

	}break;

	case SCENE_INGAME_START: {

		
	} break;

	case SCENE_INGAME_PLAY: {
		//inGame-------------------------------------
		mIsOpenMiniMap = false;

		mIsBeInLoby = false;

		mPlayerArea = "";
		mAreaTransX = 640.0f;
		mAreaTransY = 670.0f;
		mAreaTextYMax = 670.0f;
		mAreaTextYMin = 720.0f;
		mAreaTextFast = 3.0f;

		mUiInGame = new Ui_inGame();
		mUiMiniMap = new Ui_miniMap();

		mMiniMapBtn = new Mesh(65.0f, 65.0f, 1205.0f, 560.0f, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_btn.png");
		mMiniMapBtn->Update_Uv(
			D3DXVECTOR2((1.0f / 3) * 2, 1.0f),
			D3DXVECTOR2((1.0f / 3) * 2, 0.0f),
			D3DXVECTOR2(1.0f, 0.0f),
			D3DXVECTOR2(1.0f, 1.0f)
		);

		mMiniMapCloseBtn = new Mesh(65.0f, 65.0f, 179.0f, 620.0f, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_btn.png");
		mMiniMapCloseBtn->Update_Uv(
			D3DXVECTOR2(0.0f, 1.0f),
			D3DXVECTOR2(0.0f, 0.0f),
			D3DXVECTOR2(1.0f / 3, 0.0f),
			D3DXVECTOR2(1.0f / 3, 1.0f)
		);


	} break;

	default:
		break;
	}
}

//������ �ϰ� minimap�� �� �������ش�
void UiManager::SaveMyColor(D3DXVECTOR4 body, D3DXVECTOR4 shadow)
{
	mColor_body = body;
	mColor_body_shadow = shadow;

	mUiMiniMap->SetColorToIcon(body, shadow);
}


bool UiManager::findTextLoby(string str)
{
	//���ڿ� �ڿ������� ã�´�
	if(str.find("Loby") == string::npos){
		//ã�� ���������
		return false;
	}
	else {
		//ã�������
		return true;
	}
}


void UiManager::setGomujul()
{
	mGomujulPosX[0] = 70;
	mGomujulPosX[1] = -30;
	mGomujulPosX[2] = 45;
	mGomujulPosX[3] = -15;
	mGomujulPosX[4] = 30;
	mGomujulPosX[5] = -5;
	mGomujulPosX[6] = 0;
}

void UiManager::updateGomujul()
{
	//��� �ε��� ��������
	if (mGomujulIndex == 7) {
		mGomujulIndex = 0;
		mGomujulActtive = false;

		return;
	}
	//�������� �����
	else if (mGomujulIndex % 2 == 0) {

		mGoumujulTotal += mGomujulFast;
		if (mGomujulPosX[mGomujulIndex] < mGoumujulTotal) {
			mGomujulIndex++;
		}
	}
	//�������� ������
	else {

		mGoumujulTotal -= mGomujulFast;
		if (mGoumujulTotal < mGomujulPosX[mGomujulIndex] ) {
			mGomujulIndex++;
		}
	}

	mTotalIcon->SetTransX(mIconOriginPos + mGoumujulTotal);
	
}

UiManager::UiManager()
{
	//main Menu-------------------------------------
	mStart = new Mesh(190, 78, 546, 218, L"./Hlsl/Ui_mainMenuShader.hlsl", L"Resorce/Ui/Ui_mainMenu.png");
	mStart->Update_Uv(
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2((1.0f / 2), 0.0f),
		D3DXVECTOR2((1.0f / 2), 1.0f)
	);
	mExit = new Mesh(190, 78, 546, 130, L"./Hlsl/Ui_mainMenuShader.hlsl", L"Resorce/Ui/Ui_mainMenu.png");
	mExit->Update_Uv(
		D3DXVECTOR2((1.0f / 2), 1.0f),
		D3DXVECTOR2((1.0f / 2), 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(1.0f, 1.0f)
	);
	mSetting = new Mesh(90, 90, 1027, 20, L"./Hlsl/Ui_mainMenuShader.hlsl", L"Resorce/Ui/Ui_btn.png");
	mSetting->Update_Uv(
		D3DXVECTOR2((1.0f / 3) , 1.0f),
		D3DXVECTOR2((1.0f / 3) , 0.0f),
		D3DXVECTOR2((1.0f / 3) * 2, 0.0f),
		D3DXVECTOR2((1.0f / 3) * 2, 1.0f)
	);
	mNaver = new Mesh(90, 90, 1155, 20, L"./Hlsl/Ui_mainMenuShader.hlsl", L"Resorce/Ui/Ui_naver.png");


	
	
	
	

}

UiManager::~UiManager()
{
}
