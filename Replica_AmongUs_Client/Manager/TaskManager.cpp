#include "../stdafx.h"
#include "TaskActtiveManager.h"

#include "../Geometry/InGame/Task.h"
#include "UiManager.h"

#include "TaskManager.h"


void TaskManager::Update(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea )
{
	//크루원이면
	if (ClientData::Get()->mImImposter == false) {

		Update_crew(playerTrans, playerSize, cameraPos, playerArea);
	}
	//임포스터면
	else {
		Update_imposter(playerTrans, playerSize, cameraPos, playerArea);
	}
	

}
void TaskManager::Update_crew(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea)
{
	{

		//////////////////////////////////////////////////////////////////
		//목적 : 테스크와 플레이어간의 거리를 나눈다 [ 1. 무언가 use할수있는 테스크가 생겼다는걸 알수 있음, 색을 구분한다 ]
		//////////////////////////////////////////////////////////////////

		//1. 카메라의 임시 충돌 Rect를 정의한다
		RECT tempCameraRect = {
			(int)cameraPos.x - WinMaxWidthHalf, (int)cameraPos.y + WinMaxHeightHalf, //좌측상단
			(int)cameraPos.x + WinMaxWidthHalf, (int)cameraPos.y - WinMaxHeightHalf //우측하단
		};
		//2. 플레이어와 테스크 간의 거리를 알기위해 플레이어의 중심점을 정의한다
		D3DXVECTOR2 tempPlayerCenter = { playerTrans.x + (playerSize.x / 2), playerTrans.y + (playerSize.y / 2) };

		//3.1 플레이어와 인접한 테스크가 있는지! 일단 false로 초기화!
		bool nearTaskCnt = false;

		//3.2 각 거리를 리스트에 담는다 (상태가 NEAR_VERY일 경우외에는 모두 0으로 담는다 ]
		vector<float> nearList;

		//3.모든 테스크를 검사한다
		for (UINT index = 0; index < mVacTask.size(); index++) {


			//////////////////////////////////////////////////////////////////
			//카메라와 테스크의 충돌검사 [ 카메라 안에 검사하는 테스크가 있는지 ] - 렌더링을 하느냐 안하느냐의부분
			//////////////////////////////////////////////////////////////////
			if (Collision::Get()->AabbCollision(mVacTask.at(index)->GetRect(), tempCameraRect) == true) {

				//충돌했다면 랜더링을 하라는 true를 넘겨준다
				mVacTask.at(index)->SetIsRender(true);


				// (플레이어 리스트에 중복되는게 있음??  || 근데 Whiee 계열이면 랜더링해야한다 )
				if ((mVacTask.at(index)->GetThisBlack() == false || mVacTask.at(index)->GetIsYellow() == false)) {


					//플레이어의 위치와 같은 위치인지 검사
					if (playerArea == mVacTask.at(index)->GetArea()) {


						//////////////////////////////////////////////////////////////////
						//이제 모든 조건이 완벽하면 테스크의 거리 상태 세팅
						//////////////////////////////////////////////////////////////////

						//task 오브젝트(Head)와 플레이어(Tail)간의 거리를 구한다
						float tempDistance = GetVectorLength(mVacTask.at(index)->GetCenterPos(), tempPlayerCenter);

						//1. 가장 멀때, 검은테두리만 보이는 경우
						if ((UINT)tempDistance > MAX_NEAR_MIDDLE) {
							mVacTask.at(index)->SetNear(NEAR_LITTLE);
							nearList.push_back(9999);
						}
						//2. 중간 거리일 때
						else if ((UINT)tempDistance > MAX_NEAR_VERY) {

							nearList.push_back(9999);
							mVacTask.at(index)->SetNear(NEAR_MIDDLE);
						}
						//3. 가장 가까울 때, 노란색으로 전체가 뒤덮임 -> 이뜻은 활성화할 테스크가 있단소리다
						else {

							//가까운 테스크 카운터 증가
							nearTaskCnt = true;
							//리스트에 거리 값 추가 
							nearList.push_back(tempDistance);
							//중복되는 활성화 테스크가 있을수도 있으니까 일단 2로 설정하고 밑에서 추가적으로 계산해서
							//제일 가까운 거리에 1을 설정해 준다
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
			//5. 걸치지 않으면 랜더하지말라고 false를 넘겨준다
			else {
				nearList.push_back(9999);
				mVacTask.at(index)->SetIsRender(false);
			}///if()
		}///for()



		//////////////////////////////////////////////////////////////////
		//가장 가까운거리를 정하기 위해 담긴 리스트에서 최소값을 찾아내 NEAR_VERY로 세팅한다
		//////////////////////////////////////////////////////////////////

		//가까운 테스크가 존재한다면 [테스크 활성화]
		if (nearTaskCnt == true) {

			mIsActtiveTask = true;

			float tempMin = 9999; //가장 최소값 계속 담아 가장 최소값 비교를 위한 변수
			mActtiveIndex = 0; //임시로 가장 최소값의 인덱스를 담는 변수
			//정렬을 안한이유는 리스트에 담긴순서가 테스크 백터 순서와 같기때문에 이 순서를 이용하려고 한것
			for (UINT index = 0; index < nearList.size(); index++) {

				if (tempMin > nearList.at(index)) {

					//최소값을 계속 업데이트
					tempMin = nearList.at(index);
					//최소값이 담긴 인덱스를 계속 업데이트
					mActtiveIndex = index;
				}
			}

			//활성화된 가장 가까운 테스크에 값을 업데이트
			mWhatIcon = mVacTask.at(mActtiveIndex)->GetIcon(); // 어떤 아이콘
			mActtiveTaskName = mVacTask.at(mActtiveIndex)->GetTaskName(); //테스크 이름 [ 구역 - 미션이름 ]
			mVacTask.at(mActtiveIndex)->SetNear(NEAR_VERY);
		}
		//활성화 된 테스크가 없으면 false를 대입
		else {

			mIsActtiveTask = false;
		}


		//업데이트 한다 ★무조건 모두 마치고 업데이트!!
		for (UINT index = 0; index < mVacTask.size(); index++) {
			mVacTask.at(index)->Update();
		}



		if (Mouse::Get()->Down(1)) {

			//플레이어의테스크 리스트 && 좌우 애니메이션 ****************************************************
			if (mIsOpenTask == false && UiManager::Get()->GetIsOpenMiniMap() == false) {
				if (mListBackGround->IsClik() == true) {

					mListBackMove = true;
					mListMoveRight = !mListMoveRight;
				};
			}

		}

		if (UiManager::Get()->GetIsOpenMiniMap() == false) {

			if (mListBackMove == true) {

				//오른방향으로 이동
				if (mListMoveRight == true) {

					mListBackTransX += mListMoveFast;

					if (mListBackMax <= mListBackTransX) {

						mListBackTransX = mListBackMax;
						mListBackMove = false;
					}
				}
				//왼방향으로 이동
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


		//Use를 클릭했을때 테스크[미니게임] 실행하기****************************************************
		if (UiManager::Get()->GetIsSlot2Click() == true && mIsActtiveTask == true && mIsOpenTask == false) {


			//여기서 테스크객체 생성 - 실패하면 생성 안되게 함 [ 실패하는경우 임포스터가 미션하려고할때 ]
			if (TaskActtiveManager::Get()->CreateTask(mActtiveTaskName) == true)
			{
				mIsOpenTask = true;
			}
		}


		//테스크 활성화되어있다면
		if (mIsOpenTask == true) {


			//테스크를 완료 했나요??
			if (TaskActtiveManager::Get()->GetTaskComplete() == true) {

				TaskActtiveManager::Get()->SetTaskComplete(false);
				mVacTask.at(mActtiveIndex)->SetThisBlack(true);
				setCompletePlayerList(mActtiveTaskName);
				mTotalCompleteTask++;
				mIsOpenTask = false;
			}
			//테스크가 강제 종료되었음??
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
		//목적 : 플레이어간의 거리를 나눈다 [ 1. 무언가 use할수있는 테스크가 생겼다는걸 알수 있음, 색을 구분한다 ]
		//////////////////////////////////////////////////////////////////

		//1. 카메라의 임시 충돌 Rect를 정의한다
		RECT tempCameraRect = {
			(int)cameraPos.x - WinMaxWidthHalf, (int)cameraPos.y + WinMaxHeightHalf, //좌측상단
			(int)cameraPos.x + WinMaxWidthHalf, (int)cameraPos.y - WinMaxHeightHalf //우측하단
		};
		//2. 플레이어와 테스크 간의 거리를 알기위해 플레이어의 중심점을 정의한다
		D3DXVECTOR2 tempPlayerCenter = { playerTrans.x + (playerSize.x / 2), playerTrans.y + (playerSize.y / 2) };

		//3.1 플레이어와 인접한 테스크가 있는지! 일단 false로 초기화!
		bool nearTaskCnt = false;

		//3.2 각 거리를 리스트에 담는다 (상태가 NEAR_VERY일 경우외에는 모두 0으로 담는다 ]
		vector<float> nearList;

		//3.모든 테스크를 검사한다
		for (UINT index = 0; index < mVacTask.size(); index++) {


			//////////////////////////////////////////////////////////////////
			//카메라와 테스크의 충돌검사 [ 카메라 안에 검사하는 테스크가 있는지 ] - 렌더링을 하느냐 안하느냐의부분
			//////////////////////////////////////////////////////////////////
			if (Collision::Get()->AabbCollision(mVacTask.at(index)->GetRect(), tempCameraRect) == true) {

				//충돌했다면 랜더링을 하라는 true를 넘겨준다
				mVacTask.at(index)->SetIsRender(true);


				// (플레이어 리스트에 중복되는게 있음??  &&  Whiee 계열만 랜더링해야한다 )
				if ((mVacTask.at(index)->GetThisBlack() == false && mVacTask.at(index)->GetIsYellow() == false)) {


					//플레이어의 위치와 같은 위치인지 검사
					if (playerArea == mVacTask.at(index)->GetArea()) {


						//////////////////////////////////////////////////////////////////
						//이제 모든 조건이 완벽하면 테스크의 거리 상태 세팅
						//////////////////////////////////////////////////////////////////

						//task 오브젝트(Head)와 플레이어(Tail)간의 거리를 구한다
						float tempDistance = GetVectorLength(mVacTask.at(index)->GetCenterPos(), tempPlayerCenter);

						//1. 가장 멀때, 검은테두리만 보이는 경우
						if ((UINT)tempDistance > MAX_NEAR_MIDDLE) {
							mVacTask.at(index)->SetNear(NEAR_LITTLE);
							nearList.push_back(9999);
						}
						//2. 중간 거리일 때
						else if ((UINT)tempDistance > MAX_NEAR_VERY) {

							nearList.push_back(9999);
							mVacTask.at(index)->SetNear(NEAR_MIDDLE);
						}
						//3. 가장 가까울 때, 노란색으로 전체가 뒤덮임 -> 이뜻은 활성화할 테스크가 있단소리다
						else {

							//가까운 테스크 카운터 증가
							nearTaskCnt = true;
							//리스트에 거리 값 추가 
							nearList.push_back(tempDistance);
							//중복되는 활성화 테스크가 있을수도 있으니까 일단 2로 설정하고 밑에서 추가적으로 계산해서
							//제일 가까운 거리에 1을 설정해 준다
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
			//5. 걸치지 않으면 랜더하지말라고 false를 넘겨준다
			else {
				nearList.push_back(9999);
				mVacTask.at(index)->SetIsRender(false);
			}///if()
		}///for()



		//////////////////////////////////////////////////////////////////
		//가장 가까운거리를 정하기 위해 담긴 리스트에서 최소값을 찾아내 NEAR_VERY로 세팅한다
		//////////////////////////////////////////////////////////////////

		//가까운 테스크가 존재한다면 [테스크 활성화]
		if (nearTaskCnt == true) {

			mIsActtiveTask = true;

			float tempMin = 9999; //가장 최소값 계속 담아 가장 최소값 비교를 위한 변수
			mActtiveIndex = 0; //임시로 가장 최소값의 인덱스를 담는 변수
			//정렬을 안한이유는 리스트에 담긴순서가 테스크 백터 순서와 같기때문에 이 순서를 이용하려고 한것
			for (UINT index = 0; index < nearList.size(); index++) {

				if (tempMin > nearList.at(index)) {

					//최소값을 계속 업데이트
					tempMin = nearList.at(index);
					//최소값이 담긴 인덱스를 계속 업데이트
					mActtiveIndex = index;
				}
			}

			//활성화된 가장 가까운 테스크에 값을 업데이트
			mWhatIcon = mVacTask.at(mActtiveIndex)->GetIcon(); // 어떤 아이콘
			mActtiveTaskName = mVacTask.at(mActtiveIndex)->GetTaskName(); //테스크 이름 [ 구역 - 미션이름 ]
			mVacTask.at(mActtiveIndex)->SetNear(NEAR_VERY);
		}
		//활성화 된 테스크가 없으면 false를 대입
		else {

			mIsActtiveTask = false;
		}


		//업데이트 한다 ★무조건 모두 마치고 업데이트!!
		for (UINT index = 0; index < mVacTask.size(); index++) {
			mVacTask.at(index)->Update();
		}



		if (Mouse::Get()->Down(1)) {

			//플레이어의테스크 리스트 && 좌우 애니메이션 ****************************************************
			if (mIsOpenTask == false && UiManager::Get()->GetIsOpenMiniMap() == false) {
				if (mListBackGround->IsClik() == true) {

					mListBackMove = true;
					mListMoveRight = !mListMoveRight;
				};
			}

		}

		if (UiManager::Get()->GetIsOpenMiniMap() == false) {

			if (mListBackMove == true) {

				//오른방향으로 이동
				if (mListMoveRight == true) {

					mListBackTransX += mListMoveFast;

					if (mListBackMax <= mListBackTransX) {

						mListBackTransX = mListBackMax;
						mListBackMove = false;
					}
				}
				//왼방향으로 이동
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


		//Use를 클릭했을때 White테스크 실행하기****************************************************
		if (UiManager::Get()->GetIsSlot2Click() == true && mIsActtiveTask == true && mIsOpenTask == false) {


			//여기서 테스크객체 생성 - 실패하면 생성 안되게 함 [ 실패하는경우 임포스터가 미션하려고할때 ]
			if (TaskActtiveManager::Get()->CreateTask(mActtiveTaskName) == true)
			{
				mIsOpenTask = true;
			}
		}


		//테스크 활성화되어있다면
		if (mIsOpenTask == true) {


			//테스크를 완료 했나요??
			if (TaskActtiveManager::Get()->GetTaskComplete() == true) {

				TaskActtiveManager::Get()->SetTaskComplete(false);
				mVacTask.at(mActtiveIndex)->SetThisBlack(true);
				setCompletePlayerList(mActtiveTaskName);
				mTotalCompleteTask++;

				mIsOpenTask = false;
			}
			//테스크가 강제 종료되었음??
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

		//화면안에 있는것만! 랜더링
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

		//플레이어 리스트를 세팅한다
		SetPlayerTaskList();
		//세팅한 리스트를 따라서 테스크의 집합에 있는 isBlack(색깔 변경안해도 되냐?) 를 설정해준다!
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


//테스크 초기세팅
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
			
			//Black 기본 초기화 값이 ture니까 
			//화이트계열테스크는 그냥 포함  || 플레이어 테스크목록을 뒤져서 같으면 색변경하라고 false로 만들고 break후 다시 처음으로
			if ( mPlayerTaskList[index].mStr.find(mVacTask.at(taskIndex)->GetTaskName()) != string::npos) {

				mVacTask.at(taskIndex)->SetThisBlack(false);
				break;
			}
		}
	}
}


int TaskManager::GetTotalTaskComplete()
{
	// - 한 미션 개수  /  총 미션 개수 
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

		//찾았다면!
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

	//리스트 뒷 하얀 투명 배경
	mListBackGround = new Mesh(425.0f, 145.0f, mListBackTransX, mListBackTransY, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_TaskList.png");

	//벡터 리스트에 Task 객체들 추가

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
