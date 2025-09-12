#include "../../stdafx.h"
#include "../../Manager/PlayerManager.h"
#include "../../Manager/ImposterManager.h"
#include "Ui.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ui_inGame
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

Ui_inGame::Ui_inGame()
{
	mAnimation = AnimationManager::Get()->GetAnimation("Ui_Play");

	mUiSlot[0] = new Ui_inGameRect(113, 115, 0, 0, L"./Hlsl/Ui_inGameShader.hlsl", L"Resorce/Ui/Ui_play.png");
	mUiSlot[1] = new Ui_inGameRect(113, 115, 0, 0, L"./Hlsl/Ui_inGameShader.hlsl", L"Resorce/Ui/Ui_play.png");
	mUiSlot[2] = new Ui_inGameRect(113, 115, 0, 0, L"./Hlsl/Ui_inGameShader.hlsl", L"Resorce/Ui/Ui_play.png");

	mUiSlot[0]->SetOriginTrans(D3DXVECTOR2(1132, 153));
	mUiSlot[1]->SetOriginTrans(D3DXVECTOR2(987, 16));
	mUiSlot[2]->SetOriginTrans(D3DXVECTOR2(1132, 16));


	changeImage(mUiSlot[0], 1); //1�������� ������ report�� ������ �ٲ��ʿ� ����
	changeImage(mUiSlot[1], 3); //�������� ������ ������ kill
	changeImage(mUiSlot[2], 2);
}

Ui_inGame::~Ui_inGame()
{
}

//TODO;; �Ű������� ��ó�� ��ü�� �ִ��� �߰��ؼ� 0�����԰� ����
void Ui_inGame::Update(bool isImposter)
{
	//Ŭ�����ѻ��·� �ʱ�ȭ
	mIsSlot2Click = false;


	//ī�޶���� ������ġ ������Ʈ - ��� ����
	D3DXVECTOR3 tempCamera = GETCAMERA->GetCameraPos();
	tempCamera.x -= WinMaxWidthHalf;
	tempCamera.y -= WinMaxHeightHalf;

	mUiSlot[0]->SetTrans(tempCamera.x + mUiSlot[0]->GetOriginTrans().x, tempCamera.y + mUiSlot[0]->GetOriginTrans().y);
	mUiSlot[1]->SetTrans(tempCamera.x + mUiSlot[1]->GetOriginTrans().x, tempCamera.y + mUiSlot[1]->GetOriginTrans().y);
	mUiSlot[2]->SetTrans(tempCamera.x + mUiSlot[2]->GetOriginTrans().x, tempCamera.y + mUiSlot[2]->GetOriginTrans().y);


	//��Ÿ�� �̹��� ���� && //ps�� ���� ���(����,������) ������Ʈ 
	//if.1 ������������ �ù�����?
	//�ù��� ���
	if (isImposter == false) {

		//0������ 
		//if(��ó�� ��ü���ִ��� ����) - ������Ʈ�ϱ�
		mUiSlot[0]->Update(1);


		//2�� ����
		//Ȱ��ȭ �� �׽�ũ�ִٸ�
		if (TaskManager::Get()->GetIsActtiveTask() == true) {

			changeImage(mUiSlot[2], TaskManager::Get()->GetWhatIcon());
			mUiSlot[2]->Update(0);
		}
		else {
			changeImage(mUiSlot[2], TaskIcon::USE);
			mUiSlot[2]->Update(1);
		}

		
	}
	//���������� ��� 
	else {
		//1�� �����̰� 0�� �������̴�
		mUiSlot[0]->Update(1);



		////////////////////////////////////////////////////////////////////
		//1������ - [KILL]

		//ų ��Ÿ���� ����������
		if (mIsKillCoolTime == true) {

			mCoolTime += Time::Get()->Delta();
			
			if (mMaxCoolTime < mCoolTime) {
				mIsKillCoolTime = false;
				mCoolTime = 0.0f;
			}
		}


		//��ó�� �ù����ִ����޾ƿͼ� -1���̸� ���°Ű� 0�̻��̸� ������ �����Ѵٴ°����� Ȱ��ȭ�Ѵ�
		if ( 0 <= ImposterManager::Get()->GetPossibleKill()  && mIsKillCoolTime == false) {
			mUiSlot[1]->Update(0);
			mPossibleSlot1 = true; //���� Ȱ��ȭ �Ǿ��ٰ�� ����
		}
		else {
			mUiSlot[1]->Update(1);
			mPossibleSlot1 = false;//���� "��Ȱ��ȭ" �Ǿ��ٰ�� ����
		}



		////////////////////////////////////////////////////////////////////
		//2�� ����
		//Ȱ��ȭ �� �׽�ũ�ִٸ�
		if (TaskManager::Get()->GetIsActtiveTask() == true) {

			changeImage(mUiSlot[2], TaskManager::Get()->GetWhatIcon());
			mUiSlot[2]->Update(0); //Ȱ��ȭ �� �׽�ũ�� �´� ������ ��Ÿ�� �ٵ���Ȱ��ȭ �Ұ��� ����
		}
		else {
			changeImage(mUiSlot[2], 4);
			mUiSlot[2]->Update(1);// �׿ܿ��� �纸Ÿ�� ����
		}

		//2������ ->�ٵ� 0���ƴ�./.??
		//TODO: if �ֺ��� ��ü�� �֤��°�?
		//mUiSlot[2]->Update(1);
	}


	//���� Ȱ��ȭ �� ���¿��� �� ������ Ŭ���� �ߴ��� ���ߴ���
	//�׷��ϱ� Ȱ��ȭ�� �Ǿ����� Ŭ������ ��ȯ���شٴ� �Ҹ��� �ٵ� 2���� ������ ���踦�߸��ؼ� ���� ������ ��������
	if (Mouse::Get()->Down(1)) {
		//ī�޶���ǥ�� ���� �ٽ� ����ǥ��� ����
		D3DXVECTOR3 tempMousePos = Mouse::Get()->GetPosition();

		if (mUiSlot[0]->IsClick(tempMousePos) == true) {
			int a = 0;
		}
		// ���콺�� ������ ������ && ��������ó�� �ְ� && [ ��Ÿ���� �ƴϾ���Ѵ� - �̰Ŵ�  �̸�mPossibleSlot1 ���� �ɷ����� �̰� true�� ��Ÿ���� �ƴѰͰ��� ����]
		else if (mUiSlot[1]->IsClick(tempMousePos) == true && mPossibleSlot1 == true ) {
			
			//�����ٰ� �˸���
			mIsSlot1Click = true;

			//��Ÿ������ �����!
			mIsKillCoolTime = true;
		}
		else if (mUiSlot[2]->IsClick(tempMousePos) == true) {
			mIsSlot2Click = true;
		}
	}
	else {
		mIsSlot1Click = false;
		mIsSlot2Click = false;
	}


}

void Ui_inGame::Render(bool isImposter)
{
	////////////////////////////////////////////////////////////////////
	//0�� ����
	mUiSlot[0]->Render();

	////////////////////////////////////////////////////////////////////
	//1�� ����
	if (isImposter == true) {
		mUiSlot[1]->Render();

		//��Ÿ�� �ð�ǥ��
		if (mIsKillCoolTime == true) {

			int tempTime = (int)(mMaxCoolTime - mCoolTime);

			wstring tempWstr = to_wstring(tempTime);
			WCHAR * tempWchar = _wcsdup(tempWstr.c_str());
			FontManager::Get()->DrawCenter_border(L"Varela", tempWchar, 60.0f, 1042.0f, 603.0f, 0xffffffff, 0xff000000, 1);
			free(tempWchar);
		}
	}

	////////////////////////////////////////////////////////////////////
	//2�� ����
	mUiSlot[2]->Render();
}


void Ui_inGame::changeImage(Ui_inGameRect * slot, UINT uvNum)
{
	slot->Update_Uv(mAnimation.mVecFrame.at(uvNum).mUv0, mAnimation.mVecFrame.at(uvNum).mUv1, mAnimation.mVecFrame.at(uvNum).mUv2, mAnimation.mVecFrame.at(uvNum).mUv3);
	int a = 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ui_miniMap
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ui_miniMap::Ui_miniMap()
{
	init();
}

Ui_miniMap::~Ui_miniMap()
{
}

void Ui_miniMap::Update()
{
	mMiniMapBtn->Update_withCam();

	
	D3DXVECTOR2 tempTrans = getMiniMapPos();
	mPlayerIcon->SetTrans(tempTrans.x, tempTrans.y);
	mPlayerIcon->Update_withCam();
}

void Ui_miniMap::Render()
{
	mMiniMapBtn->Render();
	mPlayerIcon->Render();
}

void Ui_miniMap::SetColorToIcon(D3DXVECTOR4 body, D3DXVECTOR4 shadow)
{
	mPlayerIcon->SaveMyColor(body, shadow);
}

void Ui_miniMap::init()
{
	mMiniMapBtn = new Mesh(mMiniMapSize.x, mMiniMapSize.y, mMiniMapTrans.x, mMiniMapTrans.y, L"./Hlsl/TextureShader.hlsl", L"Resorce/MiniMap/miniMap.png");
	mPlayerIcon = new Mesh_player(30.0f, 25.0f, 0.0f, 0.0f, L"./Hlsl/PlayerShader.hlsl", L"Resorce/MiniMap/playerIcon.png");
	mPlayerIcon->SaveMyColor(ClientData::Get()->mPlayerFirstColorBody, ClientData::Get()->mPlayerFirstColorShadow);
}

D3DXVECTOR2 Ui_miniMap::getMiniMapPos()
{
	D3DXVECTOR2 result;
	float ratio = 0;

	//�÷��̾� ������ǥ �޾ƿ԰�~
	D3DXVECTOR2 tempPlayerTrans = PlayerManager::Get()->GetMyTrans();

	//�ϴ� X���ϱ�
	//1. ���� ��ġ���� ��ü�ʰ� ������ �������� ���� ����
	result.x = tempPlayerTrans.x - mToDoMinValue.x;

	//2.������ ���ϱ� �����ʻ����� / ������ġ
	ratio = mOnlyAreaSize.x / result.x;

	//3.�̴ϸʿ����� ��ġ - �̴ϸ�ũ�� / ����
	result.x = mMiniMapSize.x / ratio;

	//Y ���ϱ�
	result.y = tempPlayerTrans.y - mToDoMinValue.y;
	ratio = mOnlyAreaSize.y / result.y;
	result.y = mMiniMapSize.y / ratio;

	//ȭ����� ���� �����ֱ�
	result.x += mMiniMapTrans.x;
	result.y += mMiniMapTrans.y;

	return result;
}
