#include "../../../stdafx.h"
#include "../../Mesh.h"
#include "../../AnimationMesh.h"
#include "O2_ClienFilter.h"

O2_ClienFilter::O2_ClienFilter()
{
	init();
}

O2_ClienFilter::~O2_ClienFilter()
{
}

void O2_ClienFilter::Update()
{
	
	mClosseBtn->Update_withCam();
	mBackGround->Update_withCam();
	mFront->Update_withCam();

	if (mActtiveArrow == true) {
		mRightArrow->UpdateFromCam(false, false);
		mLeftArrow->UpdateFromCam(false, false);
	}

	updateLeaf();

	if (mIsComplete == true) {
		mRightCompleteArrow->Update_withCam();
		mLeftCompleteArrow->Update_withCam();
	}

	//마우스클릭했는데, 나뭇잎을 하나라도 안눌렀거나 && 사각형을 누르지않으면 -> 나간다
	if (Mouse::Get()->Down(1) == true && isLeafClick() == false && mBackGround->IsClik() == false) {

		mClickEnd = true;
	}


	//////////////////////////////////////////
	//위로 올라가거나 내려가는 애니메이션 부분
	{

		//올라가는 중이면 값을 더해준다 [원래 마이너스이기에]
		if (mIsUp == true) {

			mAllMeshMove += mAllMeshMoveFast;

			//다 올라가면 스탑
			if (0 < mAllMeshMove) {

				mAllMeshMove = 0;
				mIsUp = false;
			}

			mBackGround->SetTransY(111 + mAllMeshMove);
			mFront->SetTransY(111 + mAllMeshMove);
			mClosseBtn->SetTransY(576 + mAllMeshMove);

			for (int index = 0; index < 7; index++) {

				mLeaf[index].mLeafMesh->SetTransY(mLeaf[index].mLeafTrans.y + mAllMeshMove);
			}
		}
		//끝났을때! -> 내려간다
		else if (mIsComplete == true) {

			if (mDownTime < mDownMaxTime) {

				//자동으로 내려가기까지의 시간 계산
				mDownTime += Time::Get()->Delta();
			}
			else {

				mAllMeshMove -= mAllMeshMoveFast;

				mBackGround->SetTransY(111 + mAllMeshMove);
				mFront->SetTransY(111 + mAllMeshMove);
				mClosseBtn->SetTransY(576 + mAllMeshMove);
				mLeftCompleteArrow->SetTransY(337 + mAllMeshMove);
				mRightCompleteArrow->SetTransY(350 + mAllMeshMove);

				//다 올라가면 스탑
				if (mAllMeshMove <= mAllMeshMoveMin) {

					mAllMeshMove = mAllMeshMoveMin;
					mClickEnd = true;
				}
			}
		}
	}
}

void O2_ClienFilter::Render()
{

	mBackGround->Render();
	if (mActtiveArrow == true) {
		mRightArrow->Render();
	}

	renderLeaf();

	mFront->Render();
	if (mActtiveArrow == true) {
		mLeftArrow->Render();
	}

	mRightCompleteArrow->Render();
	mLeftCompleteArrow->Render();

	mClosseBtn->Render();
}

void O2_ClienFilter::init()
{
	//공용 ------
	mIsComplete = false;
	mClickEnd = false;

	//매쉬들 정의------
	mClosseBtn = new Mesh(35.0f, 35.0f, 352.0f, 576.0f + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_btn.png");
	mClosseBtn->Update_Uv(
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f / 3, 0.0f),
		D3DXVECTOR2(1.0f / 3, 1.0f)
	);

	initLeaf();

	mBackGround = new Mesh(500, 500, 391, 111 + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/CleanFilter/o2_CleanBack.png");
	mFront = new Mesh(49, 500, 391, 111 + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/CleanFilter/o2_CleanFront.png");
	 
	
	mLeftArrow = new AnimationMesh("Task_CleanFilter_leftArrow", L"./Hlsl/TextureShader.hlsl", true, 405, 337);
	mRightArrow = new AnimationMesh("Task_CleanFilter_rightArrow", L"./Hlsl/TextureShader.hlsl", true, 470, 350);
	

	//이건  완료되고 나오기떄문에 mAllMeshMove 를 안붙여준다
	mLeftCompleteArrow = new Mesh(30, 48, 405, 337, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/CleanFilter/arrowFinishedLeft.png");
	mRightCompleteArrow = new Mesh(11, 21, 470, 350, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/CleanFilter/arrowFinishedRight.png");
}

void O2_ClienFilter::initLeaf()
{
	uniform_int_distribution<int> randPosX(558, 829);
	uniform_int_distribution<int> randPosY(233, 484);
	
	
	mLeaf[0].mLeafMesh = new Mesh(22, 61, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf1.png");
	mLeaf[1].mLeafMesh = new Mesh(22, 71, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf2.png");
	mLeaf[2].mLeafMesh = new Mesh(24, 80, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf3.png");
	mLeaf[3].mLeafMesh = new Mesh(23, 54, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf4.png");
	mLeaf[4].mLeafMesh = new Mesh(22, 74, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf5.png");
	mLeaf[5].mLeafMesh = new Mesh(60, 73, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf6.png");
	mLeaf[6].mLeafMesh = new Mesh(32, 47, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf7.png");


	for (int index = 0; index < 7; index++) {

		mLeaf[index].mLeafMesh->SetVertexDataCenter();
		mLeaf[index].mIsComplete = false;
		mLeaf[index].mIsMove = false;
		mLeaf[index].mUintTrans = { 0,0 };
		mLeaf[index].mLeafMinFast = { 0,0 };
		mLeaf[index].mIsOuting = false;
		mLeaf[index].mLeafTrans = mLeaf[index].mLeafMesh->GetTrans();
		mLeaf[index].mLeafTrans.y = mLeaf[index].mLeafTrans.y - mAllMeshMove;
	}
}

void O2_ClienFilter::updateLeaf()
{

	for (int index = 0; index < 7; index++) {

		//완료되지 않은 나뭇잎만 업데이트한다
		if (mLeaf[index].mIsComplete == false) {

			//마우스가 나를 눌렀는지 확인 && 나뭇잎이 들어가있으면 안된다
			if (Mouse::Get()->Down(1) && mLeaf[index].mLeafMesh->IsClik_Center() == true && mLeaf[index].mIsComplete == false) {

				//다른 나뭇잎이 이미 잡혀있으면 그냥 둔다
				for (int i = 0; i < 7; i++) {

					//자기자신이 아닐때만 검사
					if (mLeaf[i].mIsMove == true && i != index) {

						//누군가 잡혀있으면 false하고 탈출
						mLeaf[index].mIsMove = false;
						break;
					}
					//끝까지 누군가 안잡혀있으면 true다
					mLeaf[index].mIsMove = true;
				}
				
				mActtiveArrow = true; //화살표 애니 켠다
			}


			//마우스이동중이면 마우스 따라간다! 
			if (mLeaf[index].mIsMove == true) {
				

				D3DXVECTOR2 tempPos = Mouse::Get()->GetPosition();

				float tempScala = GetVectorLength(tempPos, mLeaf[index].mLeafMesh->GetTrans());

				D3DXVECTOR2 tempMove;

				//거리가 최소값 이하면 0,0으로 초기화
				if (tempScala < 1) {

					tempMove = { 0,0 };
				}
				else {

					//단위 벡터 구하기
					tempMove = tempPos - mLeaf[index].mLeafMesh->GetTrans();
					tempMove /= tempScala;
					tempMove *= 2;
				}

				//단위벡터 저장하고 최근께 계속 남아있게
				mLeaf[index].mUintTrans = tempMove;
				mLeaf[index].mLeafMinFast = tempMove / 150;
			}
			//이동중이 아니면 속도를 점점 줄인다
			else {

				//빨려들어가는 기준선보다 오른쪽에 있으면
				if (mLeafOutX < mLeaf[index].mLeafMesh->GetTrans().x) {

					mLeaf[index].mIsOuting = false; //빨려들게안한다

					//부호저장, true면 양수, false면 음수
					bool tempBuhoBeforeX;
					bool tempBuhoBeforeY;
					bool tempBuhoAffterX;
					bool tempBuhoAffterY;

					//0보다 작으면
					if (mLeaf[index].mUintTrans.x < 0) tempBuhoBeforeX = false; else tempBuhoBeforeX = true;
					if (mLeaf[index].mUintTrans.y < 0) tempBuhoBeforeY = false; else tempBuhoBeforeY = true;

					//일단 계산하고
					mLeaf[index].mUintTrans -= mLeaf[index].mLeafMinFast;

					//계산후 부호 저장
					if (mLeaf[index].mUintTrans.x < 0) tempBuhoAffterX = false; else tempBuhoAffterX = true;
					if (mLeaf[index].mUintTrans.y < 0) tempBuhoAffterY = false; else tempBuhoAffterY = true;


					//부호 다르면 빼는백터 0으로 만듬
					if ((tempBuhoBeforeX != tempBuhoAffterX) || (tempBuhoBeforeY != tempBuhoAffterY)) {
						mLeaf[index].mLeafMinFast.x = 0;
						mLeaf[index].mLeafMinFast.y = 0;
					}
				}
				//빨려들어갈때 한번만 값 정해놓는다
				else if (mLeaf[index].mIsOuting == false){

					//빨려들어가는 원점으로의 단위벡터구한다
					float tempScala = GetVectorLength(mLeatOutPoint, mLeaf[index].mLeafMesh->GetTrans());

					D3DXVECTOR2 tempMove;


					//단위 벡터 구하기
					tempMove = mLeatOutPoint - mLeaf[index].mLeafMesh->GetTrans();
					tempMove /= tempScala;
					tempMove *= 2;
					

					//단위벡터 저장하고 최근께 계속 남아있게
					mLeaf[index].mUintTrans = tempMove;
					mLeaf[index].mLeafMinFast += (tempMove / 10);

					mLeaf[index].mIsOuting = true;
				}
				//플레이어가클릭안하고 빨려들어가는 중일때
				else {
					//단위벡터 더해준다
					mLeaf[index].mUintTrans += mLeaf[index].mLeafMinFast;

					//x축이 300 이하면 0,0으로 초기화 - 300은 내가 대충 서ㅏㄹ정한거다~
					if (mLeaf[index].mLeafMesh->GetTrans().x < 300) {

						mLeaf[index].mIsComplete = true;//들어갔다고 알림
						mLeatOutCnt++;//들어간거 카운트
						mLeaf[index].mLeafMesh->SetTransX(300);
						mLeaf[index].mUintTrans = D3DXVECTOR2(0, 0);
						mLeaf[index].mLeafMinFast = D3DXVECTOR2(0, 0);
					}
				}
			}


			//클릭을 땠으면!
			if (Mouse::Get()->Up(1) && mLeaf[index].mIsMove == true) {
				mLeaf[index].mIsMove = false;
				mActtiveArrow = false; //화살표 애니 끈다
			}

			if (index == 6) {
				int a = 0;
			}

			//이동 계산
			mLeaf[index].mLeafMesh->SetPlusTrans(mLeaf[index].mUintTrans); //단위벡터 더함

			//부딛혔나 결과 저장
			int tempResult = isOut(mLeaf[index].mLeafMesh->GetTrans(), mLeaf[index].mLeafMesh->GetSize());

			//부딛혔다면 [ 0 이 아님]
			if (tempResult != 0) {

				//일단 값 뺴주고 각 결과에 부호 바꿔준다
				mLeaf[index].mLeafMesh->SetMinTrans(mLeaf[index].mUintTrans);

				//부호 바꿀건데 중요한건 단위랑 줄어드는 단위 벡터 2개를 반대로 해야함 ㄹㅇㅇㅋㅋ
				//위,아래 부딛힘 -> Y축 부호 반대
				if (tempResult == 1 || tempResult == 3) {
					mLeaf[index].mUintTrans.y = -mLeaf[index].mUintTrans.y;
					mLeaf[index].mLeafMinFast.y = -mLeaf[index].mLeafMinFast.y;
				}
				//오른쪽 부딛힘 x축 부호 반대
				else if (tempResult == 2) {
					mLeaf[index].mUintTrans.x = -mLeaf[index].mUintTrans.x;
					mLeaf[index].mLeafMinFast.x = -mLeaf[index].mLeafMinFast.x;
				}

				//다시한번 바뀐 부호로 이동 계산
				mLeaf[index].mLeafMesh->SetPlusTrans(mLeaf[index].mUintTrans); //단위벡터 더함
			}

			//최종 업데이트

			mLeaf[index].mLeafMesh->Update_withCam();
		}


	}

	//7개 모두 들어가면 끝
	if (mLeatOutCnt == 7) {

		mIsComplete = true;
	}
}

void O2_ClienFilter::renderLeaf()
{
	for (int index = 0; index < 7; index++) {

		//완료되지 않은 나뭇잎만 업데이트한다
		if (mLeaf[index].mIsComplete == false) {

			mLeaf[index].mLeafMesh->Render();
		}
	}
}

int O2_ClienFilter::isOut(D3DXVECTOR2 leafTrans, D3DXVECTOR2 leafSize)
{
	//오른쪽으로 부딛히면 2
	if (891 < leafTrans.x + leafSize.x) return 2;

	//아래로 나가면 3
	else if ((leafTrans.y - leafSize.y) < 111) return 3;

	//위로 부딛히면 1
	else if( 611 < (leafTrans.y + leafSize.y)) return 1;

	//안부딛히면 0
	return 0;
}

bool O2_ClienFilter::isLeafClick()
{

	for (int index = 0; index < 7; index++) {

		if (mLeaf[index].mLeafMesh->IsClik_Center() == true) return true;
	}
	return false;
}


