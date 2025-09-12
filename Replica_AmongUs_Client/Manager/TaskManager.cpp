#include "../stdafx.h"
#include "TaskActtiveManager.h"

#include "../Geometry/InGame/Task.h"
#include "UiManager.h"

#include "TaskManager.h"


void TaskManager::Update(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea )
{
	//ũ����̸�
	if (ClientData::Get()->mImImposter == false) {

		Update_crew(playerTrans, playerSize, cameraPos, playerArea);
	}
	//�������͸�
	else {
		Update_imposter(playerTrans, playerSize, cameraPos, playerArea);
	}
	

}
void TaskManager::Update_crew(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea)
{
	{

		//////////////////////////////////////////////////////////////////
		//���� : �׽�ũ�� �÷��̾�� �Ÿ��� ������ [ 1. ���� use�Ҽ��ִ� �׽�ũ�� ����ٴ°� �˼� ����, ���� �����Ѵ� ]
		//////////////////////////////////////////////////////////////////

		//1. ī�޶��� �ӽ� �浹 Rect�� �����Ѵ�
		RECT tempCameraRect = {
			(int)cameraPos.x - WinMaxWidthHalf, (int)cameraPos.y + WinMaxHeightHalf, //�������
			(int)cameraPos.x + WinMaxWidthHalf, (int)cameraPos.y - WinMaxHeightHalf //�����ϴ�
		};
		//2. �÷��̾�� �׽�ũ ���� �Ÿ��� �˱����� �÷��̾��� �߽����� �����Ѵ�
		D3DXVECTOR2 tempPlayerCenter = { playerTrans.x + (playerSize.x / 2), playerTrans.y + (playerSize.y / 2) };

		//3.1 �÷��̾�� ������ �׽�ũ�� �ִ���! �ϴ� false�� �ʱ�ȭ!
		bool nearTaskCnt = false;

		//3.2 �� �Ÿ��� ����Ʈ�� ��´� (���°� NEAR_VERY�� ���ܿ��� ��� 0���� ��´� ]
		vector<float> nearList;

		//3.��� �׽�ũ�� �˻��Ѵ�
		for (UINT index = 0; index < mVacTask.size(); index++) {


			//////////////////////////////////////////////////////////////////
			//ī�޶�� �׽�ũ�� �浹�˻� [ ī�޶� �ȿ� �˻��ϴ� �׽�ũ�� �ִ��� ] - �������� �ϴ��� ���ϴ����Ǻκ�
			//////////////////////////////////////////////////////////////////
			if (Collision::Get()->AabbCollision(mVacTask.at(index)->GetRect(), tempCameraRect) == true) {

				//�浹�ߴٸ� �������� �϶�� true�� �Ѱ��ش�
				mVacTask.at(index)->SetIsRender(true);


				// (�÷��̾� ����Ʈ�� �ߺ��Ǵ°� ����??  || �ٵ� Whiee �迭�̸� �������ؾ��Ѵ� )
				if ((mVacTask.at(index)->GetThisBlack() == false || mVacTask.at(index)->GetIsYellow() == false)) {


					//�÷��̾��� ��ġ�� ���� ��ġ���� �˻�
					if (playerArea == mVacTask.at(index)->GetArea()) {


						//////////////////////////////////////////////////////////////////
						//���� ��� ������ �Ϻ��ϸ� �׽�ũ�� �Ÿ� ���� ����
						//////////////////////////////////////////////////////////////////

						//task ������Ʈ(Head)�� �÷��̾�(Tail)���� �Ÿ��� ���Ѵ�
						float tempDistance = GetVectorLength(mVacTask.at(index)->GetCenterPos(), tempPlayerCenter);

						//1. ���� �ֶ�, �����׵θ��� ���̴� ���
						if ((UINT)tempDistance > MAX_NEAR_MIDDLE) {
							mVacTask.at(index)->SetNear(NEAR_LITTLE);
							nearList.push_back(9999);
						}
						//2. �߰� �Ÿ��� ��
						else if ((UINT)tempDistance > MAX_NEAR_VERY) {

							nearList.push_back(9999);
							mVacTask.at(index)->SetNear(NEAR_MIDDLE);
						}
						//3. ���� ����� ��, ��������� ��ü�� �ڵ��� -> �̶��� Ȱ��ȭ�� �׽�ũ�� �ִܼҸ���
						else {

							//����� �׽�ũ ī���� ����
							nearTaskCnt = true;
							//����Ʈ�� �Ÿ� �� �߰� 
							nearList.push_back(tempDistance);
							//�ߺ��Ǵ� Ȱ��ȭ �׽�ũ�� �������� �����ϱ� �ϴ� 2�� �����ϰ� �ؿ��� �߰������� ����ؼ�
							//���� ����� �Ÿ��� 1�� ������ �ش�
							mVacTask.at(index)->SetNear(NEAR_MIDDLE);
						}

					}
					else {
						mVacTask.at(index)->SetNear(NEAR_LITTLE);
						nearList.push_back(9999);
					}
				}
				else {
					mVacTask.at(index)->SetNear(NEAR_LITTLE);
					nearList.push_back(9999);
				}

			}
			//5. ��ġ�� ������ ������������� false�� �Ѱ��ش�
			else {
				nearList.push_back(9999);
				mVacTask.at(index)->SetIsRender(false);
			}///if()
		}///for()



		//////////////////////////////////////////////////////////////////
		//���� �����Ÿ��� ���ϱ� ���� ��� ����Ʈ���� �ּҰ��� ã�Ƴ� NEAR_VERY�� �����Ѵ�
		//////////////////////////////////////////////////////////////////

		//����� �׽�ũ�� �����Ѵٸ� [�׽�ũ Ȱ��ȭ]
		if (nearTaskCnt == true) {

			mIsActtiveTask = true;

			float tempMin = 9999; //���� �ּҰ� ��� ��� ���� �ּҰ� �񱳸� ���� ����
			mActtiveIndex = 0; //�ӽ÷� ���� �ּҰ��� �ε����� ��� ����
			//������ ���������� ����Ʈ�� �������� �׽�ũ ���� ������ ���⶧���� �� ������ �̿��Ϸ��� �Ѱ�
			for (UINT index = 0; index < nearList.size(); index++) {

				if (tempMin > nearList.at(index)) {

					//�ּҰ��� ��� ������Ʈ
					tempMin = nearList.at(index);
					//�ּҰ��� ��� �ε����� ��� ������Ʈ
					mActtiveIndex = index;
				}
			}

			//Ȱ��ȭ�� ���� ����� �׽�ũ�� ���� ������Ʈ
			mWhatIcon = mVacTask.at(mActtiveIndex)->GetIcon(); // � ������
			mActtiveTaskName = mVacTask.at(mActtiveIndex)->GetTaskName(); //�׽�ũ �̸� [ ���� - �̼��̸� ]
			mVacTask.at(mActtiveIndex)->SetNear(NEAR_VERY);
		}
		//Ȱ��ȭ �� �׽�ũ�� ������ false�� ����
		else {

			mIsActtiveTask = false;
		}


		//������Ʈ �Ѵ� �ڹ����� ��� ��ġ�� ������Ʈ!!
		for (UINT index = 0; index < mVacTask.size(); index++) {
			mVacTask.at(index)->Update();
		}



		if (Mouse::Get()->Down(1)) {

			//�÷��̾����׽�ũ ����Ʈ && �¿� �ִϸ��̼� ****************************************************
			if (mIsOpenTask == false && UiManager::Get()->GetIsOpenMiniMap() == false) {
				if (mListBackGround->IsClik() == true) {

					mListBackMove = true;
					mListMoveRight = !mListMoveRight;
				};
			}

		}

		if (UiManager::Get()->GetIsOpenMiniMap() == false) {

			if (mListBackMove == true) {

				//������������ �̵�
				if (mListMoveRight == true) {

					mListBackTransX += mListMoveFast;

					if (mListBackMax <= mListBackTransX) {

						mListBackTransX = mListBackMax;
						mListBackMove = false;
					}
				}
				//�޹������� �̵�
				else {

					mListBackTransX -= mListMoveFast;

					if (mListBackTransX < mListBackMin) {

						mListBackTransX = mListBackMin;
						mListBackMove = false;
					}
				}


			}
			mListBackGround->SetTrans(mListBackTransX, mListBackTransY);
			mListBackGround->Update_withCam();
		}


		//Use�� Ŭ�������� �׽�ũ[�̴ϰ���] �����ϱ�****************************************************
		if (UiManager::Get()->GetIsSlot2Click() == true && mIsActtiveTask == true && mIsOpenTask == false) {


			//���⼭ �׽�ũ��ü ���� - �����ϸ� ���� �ȵǰ� �� [ �����ϴ°�� �������Ͱ� �̼��Ϸ����Ҷ� ]
			if (TaskActtiveManager::Get()->CreateTask(mActtiveTaskName) == true)
			{
				mIsOpenTask = true;
			}
		}


		//�׽�ũ Ȱ��ȭ�Ǿ��ִٸ�
		if (mIsOpenTask == true) {


			//�׽�ũ�� �Ϸ� �߳���??
			if (TaskActtiveManager::Get()->GetTaskComplete() == true) {

				TaskActtiveManager::Get()->SetTaskComplete(false);
				mVacTask.at(mActtiveIndex)->SetThisBlack(true);
				setCompletePlayerList(mActtiveTaskName);
				mTotalCompleteTask++;
				mIsOpenTask = false;
			}
			//�׽�ũ�� ���� ����Ǿ���??
			else if (TaskActtiveManager::Get()->GetClickEnd() == true) {

				TaskActtiveManager::Get()->SetClickEnd(false);
				mIsOpenTask = false;
			}
		}

	}
}

void TaskManager::Update_imposter(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea)
{

	{
		//////////////////////////////////////////////////////////////////
		//���� : �÷��̾�� �Ÿ��� ������ [ 1. ���� use�Ҽ��ִ� �׽�ũ�� ����ٴ°� �˼� ����, ���� �����Ѵ� ]
		//////////////////////////////////////////////////////////////////

		//1. ī�޶��� �ӽ� �浹 Rect�� �����Ѵ�
		RECT tempCameraRect = {
			(int)cameraPos.x - WinMaxWidthHalf, (int)cameraPos.y + WinMaxHeightHalf, //�������
			(int)cameraPos.x + WinMaxWidthHalf, (int)cameraPos.y - WinMaxHeightHalf //�����ϴ�
		};
		//2. �÷��̾�� �׽�ũ ���� �Ÿ��� �˱����� �÷��̾��� �߽����� �����Ѵ�
		D3DXVECTOR2 tempPlayerCenter = { playerTrans.x + (playerSize.x / 2), playerTrans.y + (playerSize.y / 2) };

		//3.1 �÷��̾�� ������ �׽�ũ�� �ִ���! �ϴ� false�� �ʱ�ȭ!
		bool nearTaskCnt = false;

		//3.2 �� �Ÿ��� ����Ʈ�� ��´� (���°� NEAR_VERY�� ���ܿ��� ��� 0���� ��´� ]
		vector<float> nearList;

		//3.��� �׽�ũ�� �˻��Ѵ�
		for (UINT index = 0; index < mVacTask.size(); index++) {


			//////////////////////////////////////////////////////////////////
			//ī�޶�� �׽�ũ�� �浹�˻� [ ī�޶� �ȿ� �˻��ϴ� �׽�ũ�� �ִ��� ] - �������� �ϴ��� ���ϴ����Ǻκ�
			//////////////////////////////////////////////////////////////////
			if (Collision::Get()->AabbCollision(mVacTask.at(index)->GetRect(), tempCameraRect) == true) {

				//�浹�ߴٸ� �������� �϶�� true�� �Ѱ��ش�
				mVacTask.at(index)->SetIsRender(true);


				// (�÷��̾� ����Ʈ�� �ߺ��Ǵ°� ����??  &&  Whiee �迭�� �������ؾ��Ѵ� )
				if ((mVacTask.at(index)->GetThisBlack() == false && mVacTask.at(index)->GetIsYellow() == false)) {


					//�÷��̾��� ��ġ�� ���� ��ġ���� �˻�
					if (playerArea == mVacTask.at(index)->GetArea()) {


						//////////////////////////////////////////////////////////////////
						//���� ��� ������ �Ϻ��ϸ� �׽�ũ�� �Ÿ� ���� ����
						//////////////////////////////////////////////////////////////////

						//task ������Ʈ(Head)�� �÷��̾�(Tail)���� �Ÿ��� ���Ѵ�
						float tempDistance = GetVectorLength(mVacTask.at(index)->GetCenterPos(), tempPlayerCenter);

						//1. ���� �ֶ�, �����׵θ��� ���̴� ���
						if ((UINT)tempDistance > MAX_NEAR_MIDDLE) {
							mVacTask.at(index)->SetNear(NEAR_LITTLE);
							nearList.push_back(9999);
						}
						//2. �߰� �Ÿ��� ��
						else if ((UINT)tempDistance > MAX_NEAR_VERY) {

							nearList.push_back(9999);
							mVacTask.at(index)->SetNear(NEAR_MIDDLE);
						}
						//3. ���� ����� ��, ��������� ��ü�� �ڵ��� -> �̶��� Ȱ��ȭ�� �׽�ũ�� �ִܼҸ���
						else {

							//����� �׽�ũ ī���� ����
							nearTaskCnt = true;
							//����Ʈ�� �Ÿ� �� �߰� 
							nearList.push_back(tempDistance);
							//�ߺ��Ǵ� Ȱ��ȭ �׽�ũ�� �������� �����ϱ� �ϴ� 2�� �����ϰ� �ؿ��� �߰������� ����ؼ�
							//���� ����� �Ÿ��� 1�� ������ �ش�
							mVacTask.at(index)->SetNear(NEAR_MIDDLE);
						}

					}
					else {
						mVacTask.at(index)->SetNear(NEAR_LITTLE);
						nearList.push_back(9999);
					}
				}
				else {
					mVacTask.at(index)->SetNear(NEAR_LITTLE);
					nearList.push_back(9999);
				}

			}
			//5. ��ġ�� ������ ������������� false�� �Ѱ��ش�
			else {
				nearList.push_back(9999);
				mVacTask.at(index)->SetIsRender(false);
			}///if()
		}///for()



		//////////////////////////////////////////////////////////////////
		//���� �����Ÿ��� ���ϱ� ���� ��� ����Ʈ���� �ּҰ��� ã�Ƴ� NEAR_VERY�� �����Ѵ�
		//////////////////////////////////////////////////////////////////

		//����� �׽�ũ�� �����Ѵٸ� [�׽�ũ Ȱ��ȭ]
		if (nearTaskCnt == true) {

			mIsActtiveTask = true;

			float tempMin = 9999; //���� �ּҰ� ��� ��� ���� �ּҰ� �񱳸� ���� ����
			mActtiveIndex = 0; //�ӽ÷� ���� �ּҰ��� �ε����� ��� ����
			//������ ���������� ����Ʈ�� �������� �׽�ũ ���� ������ ���⶧���� �� ������ �̿��Ϸ��� �Ѱ�
			for (UINT index = 0; index < nearList.size(); index++) {

				if (tempMin > nearList.at(index)) {

					//�ּҰ��� ��� ������Ʈ
					tempMin = nearList.at(index);
					//�ּҰ��� ��� �ε����� ��� ������Ʈ
					mActtiveIndex = index;
				}
			}

			//Ȱ��ȭ�� ���� ����� �׽�ũ�� ���� ������Ʈ
			mWhatIcon = mVacTask.at(mActtiveIndex)->GetIcon(); // � ������
			mActtiveTaskName = mVacTask.at(mActtiveIndex)->GetTaskName(); //�׽�ũ �̸� [ ���� - �̼��̸� ]
			mVacTask.at(mActtiveIndex)->SetNear(NEAR_VERY);
		}
		//Ȱ��ȭ �� �׽�ũ�� ������ false�� ����
		else {

			mIsActtiveTask = false;
		}


		//������Ʈ �Ѵ� �ڹ����� ��� ��ġ�� ������Ʈ!!
		for (UINT index = 0; index < mVacTask.size(); index++) {
			mVacTask.at(index)->Update();
		}



		if (Mouse::Get()->Down(1)) {

			//�÷��̾����׽�ũ ����Ʈ && �¿� �ִϸ��̼� ****************************************************
			if (mIsOpenTask == false && UiManager::Get()->GetIsOpenMiniMap() == false) {
				if (mListBackGround->IsClik() == true) {

					mListBackMove = true;
					mListMoveRight = !mListMoveRight;
				};
			}

		}

		if (UiManager::Get()->GetIsOpenMiniMap() == false) {

			if (mListBackMove == true) {

				//������������ �̵�
				if (mListMoveRight == true) {

					mListBackTransX += mListMoveFast;

					if (mListBackMax <= mListBackTransX) {

						mListBackTransX = mListBackMax;
						mListBackMove = false;
					}
				}
				//�޹������� �̵�
				else {

					mListBackTransX -= mListMoveFast;

					if (mListBackTransX < mListBackMin) {

						mListBackTransX = mListBackMin;
						mListBackMove = false;
					}
				}


			}
			mListBackGround->SetTrans(mListBackTransX, mListBackTransY);
			mListBackGround->Update_withCam();
		}


		//Use�� Ŭ�������� White�׽�ũ �����ϱ�****************************************************
		if (UiManager::Get()->GetIsSlot2Click() == true && mIsActtiveTask == true && mIsOpenTask == false) {


			//���⼭ �׽�ũ��ü ���� - �����ϸ� ���� �ȵǰ� �� [ �����ϴ°�� �������Ͱ� �̼��Ϸ����Ҷ� ]
			if (TaskActtiveManager::Get()->CreateTask(mActtiveTaskName) == true)
			{
				mIsOpenTask = true;
			}
		}


		//�׽�ũ Ȱ��ȭ�Ǿ��ִٸ�
		if (mIsOpenTask == true) {


			//�׽�ũ�� �Ϸ� �߳���??
			if (TaskActtiveManager::Get()->GetTaskComplete() == true) {

				TaskActtiveManager::Get()->SetTaskComplete(false);
				mVacTask.at(mActtiveIndex)->SetThisBlack(true);
				setCompletePlayerList(mActtiveTaskName);
				mTotalCompleteTask++;

				mIsOpenTask = false;
			}
			//�׽�ũ�� ���� ����Ǿ���??
			else if (TaskActtiveManager::Get()->GetClickEnd() == true) {

				TaskActtiveManager::Get()->SetClickEnd(false);
				mIsOpenTask = false;
			}
		}

	}
}

void TaskManager::Render()
{

	for (UINT index = 0; index < mVacTask.size(); index++) {

		//ȭ��ȿ� �ִ°͸�! ������
		if (mVacTask.at(index)->GetIsRender() == true) {
			mVacTask.at(index)->Render();
		}
	}

}

void TaskManager::Setting()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_INGAME_PLAY: {

		init();

		//�÷��̾� ����Ʈ�� �����Ѵ�
		SetPlayerTaskList();
		//������ ����Ʈ�� ���� �׽�ũ�� ���տ� �ִ� isBlack(���� ������ص� �ǳ�?) �� �������ش�!
		SetTaskIsBlack();

	}break;
	case SCENE_INGAME_END: {
	
		mTotalCompleteTask = 0;
		mIsActtiveTask = false;
		mIsOpenTask = false;
		mActtiveIndex = 0;

		SAFE_DELETE(mListBackGround);

		mVacTask.clear();
		vector<Task*>().swap(mVacTask);

	} break;
	default: break;
	}
}


//�׽�ũ �ʱ⼼��
void TaskManager::SetPlayerTaskList()
{
	int tempList[3];
	uniform_int_distribution<int> rand(0, 4);


	for (int i = 0; i < 3; i++) {

		tempList[i] = rand(gen);
		for (int j = 0; j < i; j++) {

			if (tempList[i] == tempList[j]) i--;
		}
	}

	if (tempList[0] == tempList[2]) {
		int a = 0;
	}

	for (int i = 0; i < 3; i++) {

		mPlayerTaskList[i].mBool = false;
		mPlayerTaskList[i].mStr = "";
		mPlayerTaskList[i]= stringBool(mTaskList[tempList[i]], false);
	}
}



void TaskManager::SetTaskIsBlack()
{
	for (int index = 0; index < mTotalTask; index++) {

		for (UINT taskIndex = 0; taskIndex < mVacTask.size(); taskIndex++) {
			
			//Black �⺻ �ʱ�ȭ ���� ture�ϱ� 
			//ȭ��Ʈ�迭�׽�ũ�� �׳� ����  || �÷��̾� �׽�ũ����� ������ ������ �������϶�� false�� ����� break�� �ٽ� ó������
			if ( mPlayerTaskList[index].mStr.find(mVacTask.at(taskIndex)->GetTaskName()) != string::npos) {

				mVacTask.at(taskIndex)->SetThisBlack(false);
				break;
			}
		}
	}
}


int TaskManager::GetTotalTaskComplete()
{
	// - �� �̼� ����  /  �� �̼� ���� 
	float playerCompleteTaskCnt = 0.0f;

	for (int index = 0; index < mTotalTask; index++) {
		if (mPlayerTaskList->mBool == true) {
			playerCompleteTaskCnt += 1.0f;
		}
	}

	float result;

	result = playerCompleteTaskCnt / (float)mTotalTask * 100;

	return (int)result;
}

void TaskManager::RenderPlayerTaskList()
{
	if (UiManager::Get()->GetIsOpenMiniMap() == false) {
		mListBackGround->Render();

		for (int index = 0; index < 3; index++) {

			UINT32 textColor = 0xffffffff;

			if (mPlayerTaskList[index].mBool == true)textColor = 0xff007700;

			wstring tempWstr;
			tempWstr.assign(mPlayerTaskList[index].mStr.begin(), mPlayerTaskList[index].mStr.end());
			WCHAR * tempWchar = _wcsdup(tempWstr.c_str());
			FontManager::Get()->DrawFont_border(L"HYHeadLine", tempWchar, 20.0f, mListBackTransX + 15.0f, 80.0f + (35 * index), textColor, 0xff000000, 1);

			free(tempWchar);
		}
	}
}

bool TaskManager::checkIsInPlayerTaskList(string value)
{
	for (int index = 0; index < 3; index++) {
		if (mPlayerTaskList[index].mStr == value) return true;
	}
	return false;
}

void TaskManager::setCompletePlayerList(string value)
{
	for (int i = 0; i < 3; i++) {

		//ã�Ҵٸ�!
		if (mPlayerTaskList[i].mStr.find(value) != string::npos) {
			mPlayerTaskList[i].mBool = true;
		}
	}
}


TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
}

void TaskManager::init()
{
	mIsOpenTask = false;

	//����Ʈ �� �Ͼ� ���� ���
	mListBackGround = new Mesh(425.0f, 145.0f, mListBackTransX, mListBackTransY, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_TaskList.png");

	//���� ����Ʈ�� Task ��ü�� �߰�

	///////////////////////////////////////////////////////////////////////////////////////
	//CafeTeria
	///////////////////////////////////////////////////////////////////////////////////////
	mVacTask.push_back(new Task(36, 66, 3270, 2660, L"./Hlsl/TaskShader_yellow.hlsl", L"Resorce/Task/Yellow/obj_uploadData.png", CAFETERIA, TaskIcon::USE, "Cafeteria: Upload Data",true));
	mVacTask.push_back(new Task(36, 66, 3407, 2523, L"./Hlsl/TaskShader_yellow.hlsl", L"Resorce/Task/Yellow/obj_EmptyChute.png", CAFETERIA, TaskIcon::USE, "Cafeteria: Empty Chute",true));
	mVacTask.push_back(new Task(91, 75, 2612, 2112, L"./Hlsl/TaskShader_white.hlsl", L"Resorce/Task/White/obj_emergency.png", CAFETERIA, TaskIcon::USE, "Cafeteria_emergency",false));



	///////////////////////////////////////////////////////////////////////////////////////
	//Admin
	///////////////////////////////////////////////////////////////////////////////////////
	mVacTask.push_back(new Task(66, 124, 1747, 698, L"./Hlsl/TaskShader_yellow.hlsl", L"Resorce/Task/Yellow/obj_swipeCard.png", ADMIN, TaskIcon::USE, "Admin: Swipe Card",true));
	mVacTask.push_back(new Task(54, 123, 2062, 698, L"./Hlsl/TaskShader_white.hlsl", L"Resorce/Task/White/obj_admin.png", ADMIN, TaskIcon::ADMIN, "Admin_admin",false));



	///////////////////////////////////////////////////////////////////////////////////////
	//O2
	///////////////////////////////////////////////////////////////////////////////////////
	mVacTask.push_back(new Task(77, 109, 855, 2154, L"./Hlsl/TaskShader_yellow.hlsl", L"Resorce/Task/Yellow/obj_divertPower.png", O2, TaskIcon::USE, "O2: Divert Power",true));
	mVacTask.push_back(new Task(53, 97, 747, 2113, L"./Hlsl/TaskShader_yellow.hlsl", L"Resorce/Task/Yellow/obj_cleanO2.png", O2, TaskIcon::USE, "O2: Clean O2",true));



	///////////////////////////////////////////////////////////////////////////////////////
	//Security
	///////////////////////////////////////////////////////////////////////////////////////
	mVacTask.push_back(new Task(145, 72, 3921, 2517, L"./Hlsl/TaskShader_white.hlsl", L"Resorce/Task/White/obj_sequrity.png", SECURITY, TaskIcon::SEQURITY,"Sequrity: Sequrity",false));
	

}
