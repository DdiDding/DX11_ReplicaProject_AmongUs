#include "../../../stdafx.h"
#include "../../Mesh.h"
#include "Admin_SwipeCard.h"

Admin_SwipeCard::Admin_SwipeCard()
{
	init();
}

Admin_SwipeCard::~Admin_SwipeCard()
{
	SAFE_DELETE(mBackGround);
	SAFE_DELETE(mCard);
	SAFE_DELETE(mSliderTop);
	SAFE_DELETE(mWalletFront);
	SAFE_DELETE(mClosseBtn);
}

void Admin_SwipeCard::Update()
{

	//////////////////////////////////////////
	//ī�� ������Ʈ �κ�

	//���콺�� ī�带 Ŭ���ߴ°� && ī�尡 Ȱ��ȭ �Ǿ����� ������
	//�� mWalletFront�� ���� �� �����ִ� ī�� �κи� Ŭ���ǰ� �Ϸ���!
	if (Mouse::Get()->Down(1) == true && mCard->IsClik() == true && mWalletFront->IsClik() == false && mCardActtive == false) {

		mIsCardBiger = true;
	}


	//ī�尡 Ŀ�����ִ°�
	if (mIsCardBiger == true) {

		//�ð��� ���ϰ�
		mCardTime += Time::Get()->Delta();

		//0.01�ʸ��� ���� ���Ѵ�
		if (0.01f <= mCardTime) {

			mCard->SetPlusTrans(mCardUnitTrans);
			mCard->SetPlusSize(mCardUnitSize);
			mCardTime = 0.0f;

			mCardMaxCnt--;//Ƚ�� ī��Ʈ�� ����

			//������ Ƚ����ŭ ��� ���� ���ϸ�
			if (mCardMaxCnt == 0) {
				
				//���� ������ �����Ѵ�
				mCard->SetTrans({ 286, 388 });
				mCard->SetSize(mCardChangeSize);

				mTextStatus = 1; //�ؽ�Ʈ 1�� ����
				mCardActtive = true; //ī��, Ȱ��ȭ��ٰ� ����
				mIsCardBiger = false; //���� �׸� Ŀ���ٰ� ����
				mSilderStatus = 1; //�ʷϺҸ� Ű��� ����
			}
		}
	}


	//////////////////////////////////////////
	//ī�� Ȱ��ȭ ������ �κ�
	if (mCardActtive == true) {


		//ī�尡 �����ߴ� �ǵ��ư��°�?
		if(mIsCardRespon == false){


			//���� ��ġ ����
			if (Mouse::Get()->Down(1) && mCard->IsClik()) {

				mSilderStatus = 0;
				mIsCardMove = true;
			}
			//������������ �ð� ���� ����
			else if (Mouse::Get()->Press(1) && mIsCardMove == true) {

				mSwipeTime += Time::Get()->Delta();
			}
			//�� ��ġ �����ؼ� ���
			else if (Mouse::Get()->Up(1) && mIsCardMove == true) {

				mIsCardMove = false;

				//������ �J������!
				if (mCard->GetTrans().x == mCardMaxX) {
					
					//�ɸ� �ð� ���
					int tempResult = CheckSwipeTime(mSwipeTime);
					mSwipeTime = 0.0f; //�ð� �ʱ�ȭ
					if (tempResult == 0) {

						//����
						mTextStatus = 5;
						mSilderStatus = 1; //�ʷϺҸ� ������ ����
						mIsComplete = true; //���� 
					}
					//�ʹ� �����ų������ų� ����
					else {

						//�ʹ� ����
						if (tempResult == -1)
							mTextStatus = 4;
						//�ʹ� ����
						else if (tempResult == 1)
							mTextStatus = 3;

						mIsCardRespon = true;
						mSilderStatus = 2; //�����Ҹ� ������ ����
					}

				}
				//����������. �ǵ��ư���
				else {

					mTextStatus = 2; //������ �ȱܾ���!
					mIsCardRespon = true;
					mSilderStatus = 2; //�����Ҹ� ������ ����
				}
				mIsCardRespon = true;
			}



			//���� �����̰������� ���콺 ���󰡶�
			if (mIsCardMove == true) {

				float tempX = Mouse::Get()->GetPosition().x - (mCardChangeSize.x / 2);

				if ( tempX < mCardChangeTrans.x) tempX = mCardChangeTrans.x;
				if (mCardMaxX < tempX) tempX = mCardMaxX;

				mCard->SetTransX(tempX);
			}


		}

		//ī�尡 �����ؼ� �ǵ��ư�����  && �������� �ʾ�������!
		else if (mIsCardRespon == true && mIsComplete == false) {

			//�Ÿ� ����
			float tempDis = mCard->GetTrans().x - mCardChangeTrans.x;

			//�����̴� ��
			float tempMove = mCardResponFast * tempDis;

			mCard->SetMinTransX( tempMove );

			//�����ڸ��� ���ư�����
			if (mCard->GetTrans().x - 1.0f <= mCardChangeTrans.x) {

				//��Ȯ�� ��ġ ���߰�
				mCard->SetTransX(mCardChangeTrans.x);
				//������ ����
				mIsCardRespon = false;
			}
		}
	}


	//////////////////////////////////////////
	//�ؽ�Ʈ �¿� �̵� �κ�
	mTextTime += Time::Get()->Delta();

	if (mTextMaxTime < mTextTime) {
		mTextMoveSwitch = !mTextMoveSwitch;
		mTextTime = 0.0f;
	}


	//////////////////////////////////////////
	//���� �ö󰡰ų� �������� �ִϸ��̼� �κ�
	{

		//�ö󰡴� ���̸� ���� �����ش� [���� ���̳ʽ��̱⿡]
		if (mIsUp == true) {

			mAllMeshMove+= mAllMeshMoveFast;

			mBackGround->SetTransY( 111 + mAllMeshMove);
			mCard->SetTransY(122 + mAllMeshMove);
			mSliderTop->SetTransY( 440 + mAllMeshMove);
			mWalletFront->SetTransY( 114 + mAllMeshMove);
			mClosseBtn->SetTransY( 576 + mAllMeshMove);

			//�� �ö󰡸� ��ž
			if ( 0 < mAllMeshMove) {

				mAllMeshMove = 0;
				mIsUp = false;
			}
		}
		//��������! -> ��������
		else if(mIsComplete == true){

			if (mDownMaxTime > mDownTime) {

				//�ڵ����� ������������� �ð� ���
				mDownTime += Time::Get()->Delta();
			}
			else {

				mAllMeshMove -= mAllMeshMoveFast;

				mBackGround->SetTransY(111 + mAllMeshMove);
				mCard->SetTransY(364 + mAllMeshMove);
				mSliderTop->SetTransY(440 + mAllMeshMove);
				mWalletFront->SetTransY(114 + mAllMeshMove);
				mClosseBtn->SetTransY(576 + mAllMeshMove);

				//�� �ö󰡸� ��ž
				if (mAllMeshMove <= mAllMeshMoveMin) {

					mAllMeshMove = mAllMeshMoveMin;
					mIsClickEnd = true;
				}
			}
		}
	}


	//////////////////////////////////////////
	//������ư�������� �κ�
	if (Mouse::Get()->Down(1) == true) {

		//��ü �簢���� ������ �ʾ����� && ī�带 ������ �ʾ����� -> �����ٰ� ó���ȴ�
		if (mBackGround->IsClik() == false && mCard->IsClik() == false) {
			mIsClickEnd = true;
		}
	}


	//////////////////////////////////////////
	//�⺻ ������Ʈ �κ�
	{
		mBackGround->Update_withCam();
		mCard->Update_withCam();
		mSliderTop->Update_withCam();
		mSliderTop->Update_ps_int(mSilderStatus);
		mWalletFront->Update_withCam();
		mClosseBtn->Update_withCam();
	}
}

void Admin_SwipeCard::Render()
{
	mBackGround->Render();
	mCard->Render();
	mWalletFront->Render();
	mSliderTop->Render();

	//���������� �¿� �̵��ϴ°�ó�� ���̰� ��
	if (mTextMoveSwitch == false) {
		FontManager::Get()->DrawFont(L"LAB������", mTextList[mTextStatus], 20.0f, 440.0f, 108.0f - mAllMeshMove, 0xffffffff);
	}
	else {
		FontManager::Get()->DrawFont(L"LAB������", mTextList[mTextStatus], 20.0f, 446.0f, 108.0f - mAllMeshMove, 0xffffffff);
	}
	mClosseBtn->Render();
}

void Admin_SwipeCard::init()
{
	mIsClickEnd = false;
	mIsComplete = false;
	mIsUp = true;
	mAllMeshMoveMin = -576;
	mAllMeshMove = mAllMeshMoveMin;
	mAllMeshMoveFast = 60.0f;

	mDownTime = 0.0f;
	mDownMaxTime = 1.2f;

	//ī��----------
	mCardOriginSize = { 165 , 100 };
	mCardOriginTrans = { 456 , 122 };

	mCardChangeSize = { 227, 138 };
	mCardChangeTrans = { 286, 364 };

	mCardDisSize = mCardChangeSize - mCardOriginSize;
	mCardDisTrans = mCardChangeTrans - mCardOriginTrans;

	mCardMaxX = 774;

	mCardMaxCnt = 60;

	mCardUnitSize = mCardDisSize / (float)mCardMaxCnt;
	mCardUnitTrans = mCardDisTrans / (float)mCardMaxCnt;

	mIsCardMove = false;
	mIsCardRespon = false;
	mCardTime = 0.0f;
	mCardActtive = false;

	mSilderStatus = 0;
	mTaskStatus = 0;

	//----Ȱ��ȭ ��
	mIsCardMove = false;

	mSwipeTime = 0.0f;

	mSwipeUnitTime = 0.8f;
	mSwipeDisTime = 0.3f;
	mSwipeMinTime = mSwipeUnitTime - mSwipeDisTime;
	mSwipeMaxTime = mSwipeUnitTime + mSwipeDisTime;

	//---�ؽ�Ʈ
	mTextStatus = 0;
	mTextTime = 0.0f;
	mTextMaxTime = 1.2f;
	mTextMoveSwitch = false;


	//---�⺻

	mBackGround = new Mesh(500, 500, 391, 111 + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/SwipeCard/admin_bg.png");
	mSliderTop = new Mesh(500, 171, 391, 440 + mAllMeshMove, L"./Hlsl/AdminSwipeCardShader.hlsl", L"Resorce/Task/SwipeCard/admin_sliderTop.png");
	mCard = new Mesh(165, 100, 456, 122 + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/SwipeCard/admin_card.png");
	mWalletFront = new Mesh(247, 85, 412, 114 + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/SwipeCard/admin_walletFront.png");
	mClosseBtn = new Mesh(35.0f, 35.0f, 356.0f, 576.0f + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_btn.png");
	mClosseBtn->Update_Uv(
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f / 3, 0.0f),
		D3DXVECTOR2(1.0f / 3, 1.0f)
	);
}

int Admin_SwipeCard::CheckSwipeTime(float swipeTime)
{

	//�ʹ� ������
	if (swipeTime < mSwipeMinTime) 
		return 1;
	//�ʹ� ������
	else if (mSwipeMaxTime < swipeTime) 
		return -1;

	//������ ����
	return 0;
}
