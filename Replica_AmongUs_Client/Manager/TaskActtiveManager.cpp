#include "../stdafx.h"
#include "PlayerManager.h"
#include "CrewManager.h"
#include "TaskActtiveManager.h"

/*
---taskName 목록---
cafeteria_uploadData
*/
TaskActtiveManager::TaskActtiveManager()
{
}

TaskActtiveManager::~TaskActtiveManager()
{
}

bool TaskActtiveManager::CreateTask(string taskName)
{
	

	//White계열 먼저 검사하고 밑에서 Yellow형식은 임포스터가아니면 가능하게끔 하고 밑에서 최종 반환

	//////////////////////
	//White계열
	if (taskName == "Sequrity: Sequrity") {

		mSequrity = new Sequrity_Sequrity();

		//이제 미니게임 시작할거라고 값 정의
		mIsActtive = true;
		PlayerManager::Get()->SetIsMoveOK(false); //플레이어 움직임 막는다

		return true;
	}
	else if (taskName == "Admin_admin") {

		mAdmin = new Admin_Admin();

		//이제 미니게임 시작할거라고 값 정의
		mIsActtive = true;
		PlayerManager::Get()->SetIsMoveOK(false); //플레이어 움직임 막는다

		return true;
	}
	


	//////////////////////
	//Yellow계열 - 임포스터가 아니면 가능
	if (ClientData::Get()->mImImposter == false) {

		//if (taskName == "Cafeteria: Upload Data") {
		if (taskName == "Cafeteria: Upload Data" ||
			taskName == "O2: Clean O2"||
			taskName =="Cafeteria: Empty Chute"
			) {

			mUploadData = new CafeTeria_UploadData();

			//이제 미니게임 시작할거라고 값 정의
			mIsActtive = true;
			PlayerManager::Get()->SetIsMoveOK(false); //플레이어 움직임 막는다

			return true;
		}


		else if (taskName == "Admin: Swipe Card") {

			mSwipeCard = new Admin_SwipeCard();

			mIsActtive = true;
			PlayerManager::Get()->SetIsMoveOK(false); //플레이어 움직임 막는다

			return true;
		}
		
		else if (taskName == "O2: Divert Power") {

			mClienFilter = new O2_ClienFilter();

			mIsActtive = true;
			PlayerManager::Get()->SetIsMoveOK(false); //플레이어 움직임 막는다

			return true;
		}
	}
	

	//여기까지 오면 false다
	return false;
}

//true 면 랜더링을 해야한다, false면 랜더링까지 안가도 된다 이제
bool TaskActtiveManager::Update(string * taskName)
{
	//클릭값초기화
	mClickEnd = false;


	//if (*(taskName) == "Cafeteria: Upload Data")
	if (*(taskName)== "Cafeteria: Upload Data" ||
		*(taskName)== "O2: Clean O2" ||
		*(taskName)== "Cafeteria: Empty Chute"
		) 
	{

		//미니게임 업데이트
		mUploadData->Update();

		
		//목적 : 업데이트 했는데 엑스버튼 누름?
		//죽었을때! [ 정확히는 처음 죽을때만 계산하는것 ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mUploadData->SetIsClickEnd(true);
		}
		//죽지않을때 정상적으로 클래스에서 받아온다
		else {
			mClickEnd = mUploadData->GetIsClickEnd();

		}

		
		//완료했음??
		if (mUploadData->GetComplete() == true) {

			mTaskComplete = true;


			if (mUploadData->GetIsClickEnd() == true) {

				mIsActtive = false;
				mTaskComplete = false; //이미 한번 체크됬을테니까 초기화
				PlayerManager::Get()->SetIsMoveOK(true); //플레이어 움직임 다시 가능하게 설정
				mClickEnd = false;
				SAFE_DELETE(mUploadData);
				*(taskName) = "NULL";
				return false;
			}
				
			return true;
		}
		else if (mUploadData->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //플레이어 움직임 다시 가능하게 설정
			SAFE_DELETE(mUploadData);
			//*(taskName) = "NULL";
			return false;
		}

		return true;
	}

	else if (*(taskName) == "Admin: Swipe Card") {

		mSwipeCard->Update();


		//목적 : 업데이트 했는데 엑스버튼 누름?
		//죽었을때! [ 정확히는 처음 죽을때만 계산하는것 ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mSwipeCard->SetIsClickEnd(true);
		}
		//죽지않을때 정상적으로 클래스에서 받아온다
		else {
			mClickEnd = mSwipeCard->GetIsClickEnd();
		}


		//완료했음??
		if (mSwipeCard->GetComplete() == true) {

			mTaskComplete = true;


			if (mSwipeCard->GetIsClickEnd() == true) {

				mIsActtive = false;
				mTaskComplete = false; //이미 한번 체크됬을테니까 초기화
				PlayerManager::Get()->SetIsMoveOK(true); //플레이어 움직임 다시 가능하게 설정
				mClickEnd = false;
				SAFE_DELETE(mSwipeCard);
				*(taskName) = "NULL";
				return false;
			}

			return true;
		}
		else if (mSwipeCard->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //플레이어 움직임 다시 가능하게 설정
			SAFE_DELETE(mSwipeCard);
			//*(taskName) = "NULL";
			return false;
		}

		return true;
	}

	else if (*(taskName) == "O2: Divert Power") {

		mClienFilter->Update();


		//목적 : 업데이트 했는데 엑스버튼 누름?
		//죽었을때! [ 정확히는 처음 죽을때만 계산하는것 ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mClienFilter->SetIsClickEnd(true);
		}
		//죽지않을때 정상적으로 클래스에서 받아온다
		else {
			mClickEnd = mClienFilter->GetIsClickEnd();
		}


		//완료했음??
		if (mClienFilter->GetComplete() == true) {

			mTaskComplete = true;


			if (mClienFilter->GetIsClickEnd() == true) {

				mIsActtive = false;
				mTaskComplete = false; //이미 한번 체크됬을테니까 초기화
				PlayerManager::Get()->SetIsMoveOK(true); //플레이어 움직임 다시 가능하게 설정
				mClickEnd = false;
				SAFE_DELETE(mClienFilter);
				*(taskName) = "NULL";
				return false;
			}

			return true;
		}
		else if (mClienFilter->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //플레이어 움직임 다시 가능하게 설정
			SAFE_DELETE(mClienFilter);
			//*(taskName) = "NULL";
			return false;
		}

		return true;
	}

	else if (*(taskName) == "Sequrity: Sequrity") {

		mSequrity->Update();


		//목적 : 업데이트 했는데 엑스버튼 누름?
		//죽었을때! [ 정확히는 처음 죽을때만 계산하는것 ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mSequrity->SetIsClickEnd(true);
		}
		//죽지않을때 정상적으로 클래스에서 받아온다
		else {
			mClickEnd = mSequrity->GetIsClickEnd();
		}
		

		//종료 버튼눌렀을 때
		if (mSequrity->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //플레이어 움직임 다시 가능하게 설정
			SAFE_DELETE(mSequrity);
			*(taskName) = "NULL";
			return false;
		}

		return true; // return true를 해줘야 랜더링까지 넘어간다
	}

	else if (*(taskName) == "Admin_admin") {

		mAdmin->Update();


		//목적 : 업데이트 했는데 엑스버튼 누름?
		//죽었을때! [ 정확히는 처음 죽을때만 계산하는것 ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mAdmin->SetIsClickEnd(true);
		}
		//죽지않을때 정상적으로 클래스에서 받아온다
		else {
			mClickEnd = mAdmin->GetIsClickEnd();
		}


		//종료 버튼눌렀을 때
		if (mAdmin->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //플레이어 움직임 다시 가능하게 설정
			SAFE_DELETE(mAdmin);
			*(taskName) = "NULL";
			return false;
		}
		return true;
	}

	return false;
}

void TaskActtiveManager::Render(string taskName)
{
	//if (taskName == "Cafeteria: Upload Data") 
	if (taskName == "Cafeteria: Upload Data" ||
		taskName == "O2: Clean O2" ||
		taskName == "Cafeteria: Empty Chute"
		) 
	{

		mUploadData->Render();
	}
	else if (taskName == "Admin: Swipe Card") {

		mSwipeCard->Render();

	}
	else if (taskName == "O2: Divert Power") {

		mClienFilter->Render();

	}

	else if (taskName == "Sequrity: Sequrity") {

		mSequrity->Render();
	}

	else if (taskName == "Admin_admin") {

		mAdmin->Render();
	}
}
