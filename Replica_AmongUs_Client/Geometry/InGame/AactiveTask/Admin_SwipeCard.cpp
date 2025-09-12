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
	//카드 업데이트 부분

	//마우스로 카드를 클릭했는가 && 카드가 활성화 되어있지 않을때
	//※ mWalletFront를 넣은 건 나와있는 카드 부분만 클릭되게 하려고!
	if (Mouse::Get()->Down(1) == true && mCard->IsClik() == true && mWalletFront->IsClik() == false && mCardActtive == false) {

		mIsCardBiger = true;
	}


	//카드가 커지고있는가
	if (mIsCardBiger == true) {

		//시간을 더하고
		mCardTime += Time::Get()->Delta();

		//0.01초마다 값을 더한다
		if (0.01f <= mCardTime) {

			mCard->SetPlusTrans(mCardUnitTrans);
			mCard->SetPlusSize(mCardUnitSize);
			mCardTime = 0.0f;

			mCardMaxCnt--;//횟수 카운트를 센다

			//지정한 횟수만큼 모두 값을 더하면
			if (mCardMaxCnt == 0) {
				
				//최종 값으로 변경한다
				mCard->SetTrans({ 286, 388 });
				mCard->SetSize(mCardChangeSize);

				mTextStatus = 1; //텍스트 1로 변경
				mCardActtive = true; //카드, 활성화됬다고 저장
				mIsCardBiger = false; //이제 그만 커진다고 저장
				mSilderStatus = 1; //초록불만 키라고 저장
			}
		}
	}


	//////////////////////////////////////////
	//카드 활성화 이후의 부분
	if (mCardActtive == true) {


		//카드가 실패했다 되돌아가는가?
		if(mIsCardRespon == false){


			//누른 위치 저장
			if (Mouse::Get()->Down(1) && mCard->IsClik()) {

				mSilderStatus = 0;
				mIsCardMove = true;
			}
			//누르고있으면 시간 누적 저장
			else if (Mouse::Get()->Press(1) && mIsCardMove == true) {

				mSwipeTime += Time::Get()->Delta();
			}
			//땐 위치 저장해서 계산
			else if (Mouse::Get()->Up(1) && mIsCardMove == true) {

				mIsCardMove = false;

				//끝까지 긇었는지!
				if (mCard->GetTrans().x == mCardMaxX) {
					
					//걸린 시간 계산
					int tempResult = CheckSwipeTime(mSwipeTime);
					mSwipeTime = 0.0f; //시간 초기화
					if (tempResult == 0) {

						//성공
						mTextStatus = 5;
						mSilderStatus = 1; //초록불만 켜지게 설정
						mIsComplete = true; //성공 
					}
					//너무 느리거나빠르거나 설정
					else {

						//너무 느림
						if (tempResult == -1)
							mTextStatus = 4;
						//너무 빠름
						else if (tempResult == 1)
							mTextStatus = 3;

						mIsCardRespon = true;
						mSilderStatus = 2; //빨간불만 켜지게 설정
					}

				}
				//실패했을때. 되돌아간다
				else {

					mTextStatus = 2; //끝까지 안긁었음!
					mIsCardRespon = true;
					mSilderStatus = 2; //빨간불만 켜지게 설정
				}
				mIsCardRespon = true;
			}



			//만약 움직이고있으면 마우스 따라가라
			if (mIsCardMove == true) {

				float tempX = Mouse::Get()->GetPosition().x - (mCardChangeSize.x / 2);

				if ( tempX < mCardChangeTrans.x) tempX = mCardChangeTrans.x;
				if (mCardMaxX < tempX) tempX = mCardMaxX;

				mCard->SetTransX(tempX);
			}


		}

		//카드가 실패해서 되돌아가는중  && 성공하지 않았을때만!
		else if (mIsCardRespon == true && mIsComplete == false) {

			//거리 차이
			float tempDis = mCard->GetTrans().x - mCardChangeTrans.x;

			//움직이는 양
			float tempMove = mCardResponFast * tempDis;

			mCard->SetMinTransX( tempMove );

			//원래자리로 돌아갔으면
			if (mCard->GetTrans().x - 1.0f <= mCardChangeTrans.x) {

				//정확히 위치 맞추고
				mCard->SetTransX(mCardChangeTrans.x);
				//리스폰 끝냄
				mIsCardRespon = false;
			}
		}
	}


	//////////////////////////////////////////
	//텍스트 좌우 이동 부분
	mTextTime += Time::Get()->Delta();

	if (mTextMaxTime < mTextTime) {
		mTextMoveSwitch = !mTextMoveSwitch;
		mTextTime = 0.0f;
	}


	//////////////////////////////////////////
	//위로 올라가거나 내려가는 애니메이션 부분
	{

		//올라가는 중이면 값을 더해준다 [원래 마이너스이기에]
		if (mIsUp == true) {

			mAllMeshMove+= mAllMeshMoveFast;

			mBackGround->SetTransY( 111 + mAllMeshMove);
			mCard->SetTransY(122 + mAllMeshMove);
			mSliderTop->SetTransY( 440 + mAllMeshMove);
			mWalletFront->SetTransY( 114 + mAllMeshMove);
			mClosseBtn->SetTransY( 576 + mAllMeshMove);

			//다 올라가면 스탑
			if ( 0 < mAllMeshMove) {

				mAllMeshMove = 0;
				mIsUp = false;
			}
		}
		//끝났을때! -> 내려간다
		else if(mIsComplete == true){

			if (mDownMaxTime > mDownTime) {

				//자동으로 내려가기까지의 시간 계산
				mDownTime += Time::Get()->Delta();
			}
			else {

				mAllMeshMove -= mAllMeshMoveFast;

				mBackGround->SetTransY(111 + mAllMeshMove);
				mCard->SetTransY(364 + mAllMeshMove);
				mSliderTop->SetTransY(440 + mAllMeshMove);
				mWalletFront->SetTransY(114 + mAllMeshMove);
				mClosseBtn->SetTransY(576 + mAllMeshMove);

				//다 올라가면 스탑
				if (mAllMeshMove <= mAllMeshMoveMin) {

					mAllMeshMove = mAllMeshMoveMin;
					mIsClickEnd = true;
				}
			}
		}
	}


	//////////////////////////////////////////
	//엑스버튼눌렀는지 부분
	if (Mouse::Get()->Down(1) == true) {

		//전체 사각형을 누르지 않았을때 && 카드를 누르지 않았을때 -> 나간다고 처리된다
		if (mBackGround->IsClik() == false && mCard->IsClik() == false) {
			mIsClickEnd = true;
		}
	}


	//////////////////////////////////////////
	//기본 업데이트 부분
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

	//변수에따라 좌우 이동하는것처럼 보이게 함
	if (mTextMoveSwitch == false) {
		FontManager::Get()->DrawFont(L"LAB디지털", mTextList[mTextStatus], 20.0f, 440.0f, 108.0f - mAllMeshMove, 0xffffffff);
	}
	else {
		FontManager::Get()->DrawFont(L"LAB디지털", mTextList[mTextStatus], 20.0f, 446.0f, 108.0f - mAllMeshMove, 0xffffffff);
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

	//카드----------
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

	//----활성화 후
	mIsCardMove = false;

	mSwipeTime = 0.0f;

	mSwipeUnitTime = 0.8f;
	mSwipeDisTime = 0.3f;
	mSwipeMinTime = mSwipeUnitTime - mSwipeDisTime;
	mSwipeMaxTime = mSwipeUnitTime + mSwipeDisTime;

	//---텍스트
	mTextStatus = 0;
	mTextTime = 0.0f;
	mTextMaxTime = 1.2f;
	mTextMoveSwitch = false;


	//---기본

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

	//너무 빠를때
	if (swipeTime < mSwipeMinTime) 
		return 1;
	//너무 느릴때
	else if (mSwipeMaxTime < swipeTime) 
		return -1;

	//나머진 성공
	return 0;
}
