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


	changeImage(mUiSlot[0], 1); //1번슬롯은 무조건 report다 앞으로 바꿀필요 없음
	changeImage(mUiSlot[1], 3); //임포스터 전용임 무조건 kill
	changeImage(mUiSlot[2], 2);
}

Ui_inGame::~Ui_inGame()
{
}

//TODO;; 매개변수로 근처에 시체가 있는지 추가해서 0번슬롯과 연결
void Ui_inGame::Update(bool isImposter)
{
	//클릭안한상태로 초기화
	mIsSlot2Click = false;


	//카메라기준 월드위치 업데이트 - 모두 공통
	D3DXVECTOR3 tempCamera = GETCAMERA->GetCameraPos();
	tempCamera.x -= WinMaxWidthHalf;
	tempCamera.y -= WinMaxHeightHalf;

	mUiSlot[0]->SetTrans(tempCamera.x + mUiSlot[0]->GetOriginTrans().x, tempCamera.y + mUiSlot[0]->GetOriginTrans().y);
	mUiSlot[1]->SetTrans(tempCamera.x + mUiSlot[1]->GetOriginTrans().x, tempCamera.y + mUiSlot[1]->GetOriginTrans().y);
	mUiSlot[2]->SetTrans(tempCamera.x + mUiSlot[2]->GetOriginTrans().x, tempCamera.y + mUiSlot[2]->GetOriginTrans().y);


	//나타낼 이미지 선택 && //ps에 보낼 상수(투명,반투명) 업데이트 
	//if.1 임포스터인지 시민인지?
	//시민인 경우
	if (isImposter == false) {

		//0번슬롯 
		//if(근처에 시체가있는지 변수) - 업데이트하기
		mUiSlot[0]->Update(1);


		//2번 슬롯
		//활성화 된 테스크있다면
		if (TaskManager::Get()->GetIsActtiveTask() == true) {

			changeImage(mUiSlot[2], TaskManager::Get()->GetWhatIcon());
			mUiSlot[2]->Update(0);
		}
		else {
			changeImage(mUiSlot[2], TaskIcon::USE);
			mUiSlot[2]->Update(1);
		}

		
	}
	//임포스터인 경우 
	else {
		//1이 투명이고 0이 불투명이다
		mUiSlot[0]->Update(1);



		////////////////////////////////////////////////////////////////////
		//1번슬롯 - [KILL]

		//킬 쿨타임이 돌고있으면
		if (mIsKillCoolTime == true) {

			mCoolTime += Time::Get()->Delta();
			
			if (mMaxCoolTime < mCoolTime) {
				mIsKillCoolTime = false;
				mCoolTime = 0.0f;
			}
		}


		//근처에 시민이있는지받아와서 -1이이면 없는거고 0이상이면 누군가 존재한다는것으로 활성화한다
		if ( 0 <= ImposterManager::Get()->GetPossibleKill()  && mIsKillCoolTime == false) {
			mUiSlot[1]->Update(0);
			mPossibleSlot1 = true; //슬롯 활성화 되었다고ㅓ 저장
		}
		else {
			mUiSlot[1]->Update(1);
			mPossibleSlot1 = false;//슬롯 "비활성화" 되었다고ㅓ 저장
		}



		////////////////////////////////////////////////////////////////////
		//2번 슬롯
		//활성화 된 테스크있다면
		if (TaskManager::Get()->GetIsActtiveTask() == true) {

			changeImage(mUiSlot[2], TaskManager::Get()->GetWhatIcon());
			mUiSlot[2]->Update(0); //활성화 된 테스크에 맞는 아이콘 나타냄 근데비활성화 할거임 ㅋㅋ
		}
		else {
			changeImage(mUiSlot[2], 4);
			mUiSlot[2]->Update(1);// 그외에는 사보타지 ㄱㄱ
		}

		//2번슬롯 ->근데 0번아님./.??
		//TODO: if 주변에 시체가 있ㄴ는가?
		//mUiSlot[2]->Update(1);
	}


	//무언가 활성화 된 상태에서 각 슬롯을 클릭을 했는지 안했는지
	//그러니까 활성화가 되야지만 클릭값을 반환해준다는 소리다 근데 2번은 내가ㅐ 설계를잘못해서 쟤만 예외임 ㅋㅋㅅㅂ
	if (Mouse::Get()->Down(1)) {
		//카메라좌표를 빼서 다시 뷰좌표계로 만듬
		D3DXVECTOR3 tempMousePos = Mouse::Get()->GetPosition();

		if (mUiSlot[0]->IsClick(tempMousePos) == true) {
			int a = 0;
		}
		// 마우스로 슬롯을 눌렀고 && 누군가근처에 있고 && [ 쿨타임이 아니어야한다 - 이거는  미리mPossibleSlot1 에서 걸러져서 이게 true면 쿨타임이 아닌것과도 같다]
		else if (mUiSlot[1]->IsClick(tempMousePos) == true && mPossibleSlot1 == true ) {
			
			//눌렀다고 알리고
			mIsSlot1Click = true;

			//쿨타임으로 만든다!
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
	//0번 슬롯
	mUiSlot[0]->Render();

	////////////////////////////////////////////////////////////////////
	//1번 슬롯
	if (isImposter == true) {
		mUiSlot[1]->Render();

		//쿨타임 시간표시
		if (mIsKillCoolTime == true) {

			int tempTime = (int)(mMaxCoolTime - mCoolTime);

			wstring tempWstr = to_wstring(tempTime);
			WCHAR * tempWchar = _wcsdup(tempWstr.c_str());
			FontManager::Get()->DrawCenter_border(L"Varela", tempWchar, 60.0f, 1042.0f, 603.0f, 0xffffffff, 0xff000000, 1);
			free(tempWchar);
		}
	}

	////////////////////////////////////////////////////////////////////
	//2번 슬롯
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

	//플레이어 월드좌표 받아왔고~
	D3DXVECTOR2 tempPlayerTrans = PlayerManager::Get()->GetMyTrans();

	//일단 X구하기
	//1. 현재 위치에서 전체맵과 구역맵 사이즈의 차를 뺀다
	result.x = tempPlayerTrans.x - mToDoMinValue.x;

	//2.비율을 구하기 구역맵사이즈 / 구역위치
	ratio = mOnlyAreaSize.x / result.x;

	//3.미니맵에서의 위치 - 미니맵크기 / 비율
	result.x = mMiniMapSize.x / ratio;

	//Y 구하기
	result.y = tempPlayerTrans.y - mToDoMinValue.y;
	ratio = mOnlyAreaSize.y / result.y;
	result.y = mMiniMapSize.y / ratio;

	//화면상의 여백 더해주기
	result.x += mMiniMapTrans.x;
	result.y += mMiniMapTrans.y;

	return result;
}
