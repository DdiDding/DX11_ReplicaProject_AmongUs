#include "../stdafx.h"
#include "PlayerManager.h"
#include "CrewManager.h"
#include "TaskActtiveManager.h"

/*
---taskName ���---
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
	

	//White�迭 ���� �˻��ϰ� �ؿ��� Yellow������ �������Ͱ��ƴϸ� �����ϰԲ� �ϰ� �ؿ��� ���� ��ȯ

	//////////////////////
	//White�迭
	if (taskName == "Sequrity: Sequrity") {

		mSequrity = new Sequrity_Sequrity();

		//���� �̴ϰ��� �����ҰŶ�� �� ����
		mIsActtive = true;
		PlayerManager::Get()->SetIsMoveOK(false); //�÷��̾� ������ ���´�

		return true;
	}
	else if (taskName == "Admin_admin") {

		mAdmin = new Admin_Admin();

		//���� �̴ϰ��� �����ҰŶ�� �� ����
		mIsActtive = true;
		PlayerManager::Get()->SetIsMoveOK(false); //�÷��̾� ������ ���´�

		return true;
	}
	


	//////////////////////
	//Yellow�迭 - �������Ͱ� �ƴϸ� ����
	if (ClientData::Get()->mImImposter == false) {

		//if (taskName == "Cafeteria: Upload Data") {
		if (taskName == "Cafeteria: Upload Data" ||
			taskName == "O2: Clean O2"||
			taskName =="Cafeteria: Empty Chute"
			) {

			mUploadData = new CafeTeria_UploadData();

			//���� �̴ϰ��� �����ҰŶ�� �� ����
			mIsActtive = true;
			PlayerManager::Get()->SetIsMoveOK(false); //�÷��̾� ������ ���´�

			return true;
		}


		else if (taskName == "Admin: Swipe Card") {

			mSwipeCard = new Admin_SwipeCard();

			mIsActtive = true;
			PlayerManager::Get()->SetIsMoveOK(false); //�÷��̾� ������ ���´�

			return true;
		}
		
		else if (taskName == "O2: Divert Power") {

			mClienFilter = new O2_ClienFilter();

			mIsActtive = true;
			PlayerManager::Get()->SetIsMoveOK(false); //�÷��̾� ������ ���´�

			return true;
		}
	}
	

	//������� ���� false��
	return false;
}

//true �� �������� �ؾ��Ѵ�, false�� ���������� �Ȱ��� �ȴ� ����
bool TaskActtiveManager::Update(string * taskName)
{
	//Ŭ�����ʱ�ȭ
	mClickEnd = false;


	//if (*(taskName) == "Cafeteria: Upload Data")
	if (*(taskName)== "Cafeteria: Upload Data" ||
		*(taskName)== "O2: Clean O2" ||
		*(taskName)== "Cafeteria: Empty Chute"
		) 
	{

		//�̴ϰ��� ������Ʈ
		mUploadData->Update();

		
		//���� : ������Ʈ �ߴµ� ������ư ����?
		//�׾�����! [ ��Ȯ���� ó�� �������� ����ϴ°� ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mUploadData->SetIsClickEnd(true);
		}
		//���������� ���������� Ŭ�������� �޾ƿ´�
		else {
			mClickEnd = mUploadData->GetIsClickEnd();

		}

		
		//�Ϸ�����??
		if (mUploadData->GetComplete() == true) {

			mTaskComplete = true;


			if (mUploadData->GetIsClickEnd() == true) {

				mIsActtive = false;
				mTaskComplete = false; //�̹� �ѹ� üũ�����״ϱ� �ʱ�ȭ
				PlayerManager::Get()->SetIsMoveOK(true); //�÷��̾� ������ �ٽ� �����ϰ� ����
				mClickEnd = false;
				SAFE_DELETE(mUploadData);
				*(taskName) = "NULL";
				return false;
			}
				
			return true;
		}
		else if (mUploadData->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //�÷��̾� ������ �ٽ� �����ϰ� ����
			SAFE_DELETE(mUploadData);
			//*(taskName) = "NULL";
			return false;
		}

		return true;
	}

	else if (*(taskName) == "Admin: Swipe Card") {

		mSwipeCard->Update();


		//���� : ������Ʈ �ߴµ� ������ư ����?
		//�׾�����! [ ��Ȯ���� ó�� �������� ����ϴ°� ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mSwipeCard->SetIsClickEnd(true);
		}
		//���������� ���������� Ŭ�������� �޾ƿ´�
		else {
			mClickEnd = mSwipeCard->GetIsClickEnd();
		}


		//�Ϸ�����??
		if (mSwipeCard->GetComplete() == true) {

			mTaskComplete = true;


			if (mSwipeCard->GetIsClickEnd() == true) {

				mIsActtive = false;
				mTaskComplete = false; //�̹� �ѹ� üũ�����״ϱ� �ʱ�ȭ
				PlayerManager::Get()->SetIsMoveOK(true); //�÷��̾� ������ �ٽ� �����ϰ� ����
				mClickEnd = false;
				SAFE_DELETE(mSwipeCard);
				*(taskName) = "NULL";
				return false;
			}

			return true;
		}
		else if (mSwipeCard->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //�÷��̾� ������ �ٽ� �����ϰ� ����
			SAFE_DELETE(mSwipeCard);
			//*(taskName) = "NULL";
			return false;
		}

		return true;
	}

	else if (*(taskName) == "O2: Divert Power") {

		mClienFilter->Update();


		//���� : ������Ʈ �ߴµ� ������ư ����?
		//�׾�����! [ ��Ȯ���� ó�� �������� ����ϴ°� ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mClienFilter->SetIsClickEnd(true);
		}
		//���������� ���������� Ŭ�������� �޾ƿ´�
		else {
			mClickEnd = mClienFilter->GetIsClickEnd();
		}


		//�Ϸ�����??
		if (mClienFilter->GetComplete() == true) {

			mTaskComplete = true;


			if (mClienFilter->GetIsClickEnd() == true) {

				mIsActtive = false;
				mTaskComplete = false; //�̹� �ѹ� üũ�����״ϱ� �ʱ�ȭ
				PlayerManager::Get()->SetIsMoveOK(true); //�÷��̾� ������ �ٽ� �����ϰ� ����
				mClickEnd = false;
				SAFE_DELETE(mClienFilter);
				*(taskName) = "NULL";
				return false;
			}

			return true;
		}
		else if (mClienFilter->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //�÷��̾� ������ �ٽ� �����ϰ� ����
			SAFE_DELETE(mClienFilter);
			//*(taskName) = "NULL";
			return false;
		}

		return true;
	}

	else if (*(taskName) == "Sequrity: Sequrity") {

		mSequrity->Update();


		//���� : ������Ʈ �ߴµ� ������ư ����?
		//�׾�����! [ ��Ȯ���� ó�� �������� ����ϴ°� ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mSequrity->SetIsClickEnd(true);
		}
		//���������� ���������� Ŭ�������� �޾ƿ´�
		else {
			mClickEnd = mSequrity->GetIsClickEnd();
		}
		

		//���� ��ư������ ��
		if (mSequrity->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //�÷��̾� ������ �ٽ� �����ϰ� ����
			SAFE_DELETE(mSequrity);
			*(taskName) = "NULL";
			return false;
		}

		return true; // return true�� ����� ���������� �Ѿ��
	}

	else if (*(taskName) == "Admin_admin") {

		mAdmin->Update();


		//���� : ������Ʈ �ߴµ� ������ư ����?
		//�׾�����! [ ��Ȯ���� ó�� �������� ����ϴ°� ] 
		if (CrewManager::Get()->GetStartDieAni() == true) {
			mClickEnd = true;
			mAdmin->SetIsClickEnd(true);
		}
		//���������� ���������� Ŭ�������� �޾ƿ´�
		else {
			mClickEnd = mAdmin->GetIsClickEnd();
		}


		//���� ��ư������ ��
		if (mAdmin->GetIsClickEnd() == true) {

			mIsActtive = false;
			PlayerManager::Get()->SetIsMoveOK(true); //�÷��̾� ������ �ٽ� �����ϰ� ����
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
