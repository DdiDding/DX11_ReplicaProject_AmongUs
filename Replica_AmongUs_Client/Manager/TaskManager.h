#pragma once

class TaskActtiveManager;
class Task;
class Mesh;


struct stringBool {
	stringBool() {};
	stringBool(string str, bool bol) {
		mStr = str;
		mBool = bol;
	};

	string mStr; //테스크의 이름
	bool mBool; //테스크가 완료 됐는지
};

namespace TaskIcon {
	enum {
		USE = 2,
		ADMIN = 6,
		SEQURITY = 7,
		CUSTOMIZE = 0
	};
};

//모든 Task의 상태(플레이어와의 가까음) , 랜더링하는지 안하는지 결정
class TaskManager : public SingletonBase<TaskManager>
{
public:


	friend class SingletonBase<TaskManager>;

	//크루용 업데이트
	void Update(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea);

	void Update_crew(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea);
	//임포스터용 업데이트
	void Update_imposter(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, D3DXVECTOR3 cameraPos, int playerArea);

	void Render();

	void Setting();

	//플레이어 테스크 리스트 목록을 세팅해준다(string)
	void SetPlayerTaskList();
	//플레이어 리스트에 따른 테스크의 isBlack을 세팅해준다 /isblakc은 색변경안해도된다는 bool형 데이터
	void SetTaskIsBlack();

	//현재 완료된 테스크의 퍼센트를 반환한다
	int GetTotalTaskComplete();

	int GetActtiveIndex() { return mActtiveIndex; };
	bool GetIsActtiveTask() { return mIsActtiveTask; };
	int GetWhatIcon() { return mWhatIcon; };
	string GetActtiveTaskName() { return mActtiveTaskName; };
	string * GetActtiveTaskNameP() { return &mActtiveTaskName; };
	bool GetIsOpenTask() { return mIsOpenTask; };
	int GetTotalCompleteTask() { return mTotalCompleteTask; };


	//플레이어보다 밑에 랜더링되는데 테스크 리스트 업데이트 여기서하고 랜더링만 마지막에 하면되는거아님??
	//그걸위한 함수
	void RenderPlayerTaskList();


private:

	//안쓰는데 혹심로라 일단 놔뒀다 ㅋㅋ 나중에피려없으면 지워~~~~~
	//매개변수의 string이 playerTakeList에 있는지 확인한다
	//리스트에 값이 있으면 true 반환, 없으면 false!
	bool checkIsInPlayerTaskList(string value);

	//플레이어의 리스트에 초록색으로 칠해준다
	//매개변수는 끝난 테스크의 테스크이름[구역 - 미션이름]
	void setCompletePlayerList(string value);

private:

	const UINT MAX_NEAR_VERY = 150; // NEAR_VERY상태의 최대 값
	const UINT MAX_NEAR_MIDDLE = 450; //NEAR_MIDDLE의 최대 값

	TaskManager();
	~TaskManager();

	void init();

	vector<Task*> mVacTask; //테스크 오브젝트가 들어있다
	
	int mActtiveIndex; //현재 활성화중인 테스크의 인덱스번호
	

	//Ui_inGame에서 사용할것들
	bool mIsActtiveTask; //현재 활성화중인 테스크가 있습니까? 있으면 true 없으면 false
	bool mIsOpenTask; // 활성화 말고 테스크를 실행하는중인지?
	int mWhatIcon; //어떤 아이콘을 사용하는지
					/*
					2 - use
					7 - sequrity
					6 - admin
					*/

	string mActtiveTaskName; //어떤 테스크를 오픈할건지 스트링으로 저장
							//그러려면 테스크마다 가지고있는 스트링값이 있어야겠네
							//형식은 구역이름_테스크이름 이런식으로 ㄱㄱ


	//미션들의 테스크목록 을 집합해둠 [ 하양색 제외 ]
	string mTaskList[5] = {
		"Cafeteria: Upload Data",
		"Cafeteria: Empty Chute",
		"Admin: Swipe Card",
		"O2: Divert Power",
		"O2: Clean O2"
	};


	//위에서 랜덤으로 뽑아다 플레이어 리스트에 넣는다
	stringBool mPlayerTaskList[3];

	int mTotalTask = 3;// 플레이어의 총 미션 개수

	int mTotalCompleteTask = 0; //플레이어가 완료한 미션 개수

	bool mListBackMove = false; //리스트가 움직이는중인지
	bool mListMoveRight = true; //만약 움직이면 오른쪽으로움직이는가?

	Mesh * mListBackGround;
	float mListBackTransX = 10.0f;
	float mListBackTransY = 520.0f;

	float mListBackMin = -385.0f; //줄어드는 최소값
	float mListBackMax = 10.0f; //커지는 최대값

	float mListMoveFast = 10.0f;// 리스트 이동하는 속도


};