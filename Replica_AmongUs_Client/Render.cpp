#include "Render.h"
#include "PipeLine/BufferResource/VertexDatas.h"
#include "System/Camera.h"
#include "Manager/UiManager.h"
#include "Manager/PlayerManager.h"
#include "Manager/TaskManager.h"
#include "Manager/TaskActtiveManager.h"
#include "Manager/BackgroundManager.h"
#include "Manager/EndAniManager.h"
#include "Manager/GuitarClass.h"
#include "Manager/ImposterManager.h"
#include "Manager/CrewManager.h"
#include "Geometry/AnimationMesh.h"


Render::Render()
{
	mRequestScene = SCENE_MAINMENU;
	mIsActtiveTask = false;
	mIsGameEnd = false;

	Init();
}


Render::~Render()
{
	CrewManager::Delete();
	ImposterManager::Delete();
	PlayerManager::Delete();
	SceneManager::Delete();
}

void Render::Init()
{
	/////////////////////////////////////////////////////////////////
	//Tcp Init
	/////////////////////////////////////////////////////////////////
	ClientData::Create();
	mTcp.StartTCP();
	

	/////////////////////////////////////////////////////////////////
	//Manager Init
	/////////////////////////////////////////////////////////////////
	SceneManager::Create();
	EndAniManager::Create();
	TaskActtiveManager::Create();
	PlayerManager::Create();
	BackgroundManager::Create();
	TaskManager::Create();
	UiManager::Create();
	GuitarClass::Create();
	ImposterManager::Create();
	CrewManager::Create();
	//밑에꺼 지우기
	//UiManager::Get()->SaveMyColor(PlayerManager::Get()->GetMyColor_body(), PlayerManager::Get()->GetMyColor_shadow());

	
	/////////////////////////////////////////////////////////////////
	//Camera Init
	/////////////////////////////////////////////////////////////////
	GETCAMERA->SetCamera(D3DXVECTOR3(0, 0 ,0));


	/////////////////////////////////////////////////////////////////
	//Geometri Init
	/////////////////////////////////////////////////////////////////

	//line = new DebugMap();

	
}


////////////////////////////////////////////////////////////////////////////////
//Update
////////////////////////////////////////////////////////////////////////////////

void Render::Update()
{
	if (Mouse::Get()->Down(2)) {
		PlayerManager::Get()->ChangeMyAni("Player_DieBody");
		PlayerManager::Get()->SetIsGhost(true);
	}


	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: Update_mainMenu();	break;

	case SCENE_LOBY : Update_loby();	break;

	case SCENE_INGAME_START:Update_inGame_start(); break;

	case SCENE_INGAME_PLAY:	Update_inGame(); break;

	case SCENE_INGAME_END:	Update_inGame_end(); break;


	default: break;
	}

	GuitarClass::Get()->Update();


	//게임끝났는지 확인
	if (mIsGameEnd == false) {
		if (ClientData::Get()->mIsGameEnd != 0) {

			if (ClientData::Get()->mIsGameEnd == 1) {

				//★★★★★★★★★★★★★★★★★★★★★★★★★★★
				//씬변경 - 바꾸는건 이렇게 두개 하면 된다
				//★★★★★★★★★★★★★★★★★★★★★★★★★★★
				Render::Get()->RequestSetSceneEndManager();
				SceneManager::Get()->SetNextScene(SCENE_INGAME_END);
			}
			else if (ClientData::Get()->mIsGameEnd == -1) {
				Render::Get()->RequestSetSceneEndManager();
				SceneManager::Get()->SetNextScene(SCENE_INGAME_END);
				//mIsGameEnd = true;

			}
		}
	}

	EndAniManager::Get()->Update();
	
}

 
void Render::Update_mainMenu()
{
	/////////////////////////////////////////////////////////////////
	//Camera Update
	/////////////////////////////////////////////////////////////////

	GETCAMERA->Update();

	BackgroundManager::Get()->Update();


	UiManager::Get()->Update();
}

void Render::Update_loby()
{
	/////////////////////////////////////////////////////////////////
	//Camera Update
	/////////////////////////////////////////////////////////////////

	GETCAMERA->Update_loby(PlayerManager::Get()->GetMyTrans(), PlayerManager::Get()->GetMySize());


	/////////////////////////////////////////////////////////////////
	//BackGround Update
	/////////////////////////////////////////////////////////////////
	BackgroundManager::Get()->Update();

	PlayerManager::Get()->Update();


	UiManager::Get()->Update();
}

void Render::Update_inGame_start()
{
	GETCAMERA->Update_inGame_start();

	BackgroundManager::Get()->Update();
}


void Render::Update_inGame()
{
	/////////////////////////////////////////////////////////////////
	//Camera Update
	/////////////////////////////////////////////////////////////////

	GETCAMERA->Update(PlayerManager::Get()->GetMyTrans(), PlayerManager::Get()->GetMySize());

	/////////////////////////////////////////////////////////////////
	//BackGround Update
	/////////////////////////////////////////////////////////////////
	BackgroundManager::Get()->Update();

	/////////////////////////////////////////////////////////////////
	//InGame Update
	/////////////////////////////////////////////////////////////////
	TaskManager::Get()->Update(PlayerManager::Get()->GetMyTrans(), PlayerManager::Get()->GetMySize(), GETCAMERA->GetCameraPos(), PlayerManager::Get()->GetMyArea());

	UiManager::Get()->Update();

	PlayerManager::Get()->Update();

	if (TaskActtiveManager::Get()->GetIsActtive() == true) {
		mIsActtiveTask = TaskActtiveManager::Get()->Update(TaskManager::Get()->GetActtiveTaskNameP());
	}

	/////////////////////////////////////////////////////////////////
	//Mesh Update
	/////////////////////////////////////////////////////////////////

	//line->Update();
}

void Render::Update_inGame_end()
{
	GETCAMERA->Update_inGame_end();

	BackgroundManager::Get()->Update();
}


////////////////////////////////////////////////////////////////////////////////
//Render
////////////////////////////////////////////////////////////////////////////////
void Render::Rendering()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: Render_mainMenu();	break;

	case SCENE_LOBY: Render_loby();	break;

	case SCENE_INGAME_START: Render_inGame_start(); break;

	case SCENE_INGAME_PLAY:	Render_inGame(); break;

	case SCENE_INGAME_END:	Render_inGame_end(); break;
	default:
		break;
	}

	if (ClientData::Get()->mImImposter == true) {
		int a = 0;
	}

	EndAniManager::Get()->Render();
	UpdateScene();

}

void Render::Render_mainMenu()
{
	BackgroundManager::Get()->Render();

	UiManager::Get()->Render();
}

void Render::Render_loby()
{
	BackgroundManager::Get()->Render();
	PlayerManager::Get()->Render();
	UiManager::Get()->Render();
}

void Render::Render_inGame_start()
{
	BackgroundManager::Get()->Render();
}

void Render::Render_inGame()
{
	BackgroundManager::Get()->Render();
	//line->Render();


	//Task Render 
	TaskManager::Get()->Render();


	//Player Render
	PlayerManager::Get()->Render();

	//Guitar Render
	GuitarClass::Get()->Render();


	//Ui Render
	UiManager::Get()->Render();

	//Task Acttive Render

	if (mIsActtiveTask == true) {
		TaskActtiveManager::Get()->Render(TaskManager::Get()->GetActtiveTaskName());
	}


	//임포스터면 
	if (ClientData::Get()->mImImposter == true) {
		ImposterManager::Get()->Update_Last();
	}
	else {
		CrewManager::Get()->Update_Last();
		CrewManager::Get()->Render();
	}
}

void Render::Render_inGame_end()
{
	BackgroundManager::Get()->Render();
}

void Render::RequestSetSceneEndManager()
{
	EndAniManager::Get()->SetIsStartChangeAni(true);
}

void Render::RequestSetScene(int scene)
{
	this->mRequestScene = scene;
}

void Render::UpdateScene()
{
	//씬이 다르면
	if (SceneManager::Get()->GetScene() != SceneManager::Get()->GetNextScene()) {

		if (EndAniManager::Get()->GetIsOkChangeScene() == true) {

			EndAniManager::Get()->SetIsOkChangeScene(false);
			
			SceneManager::Get()->ChangeScene();
			Setting();
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
//Setting
////////////////////////////////////////////////////////////////////////////////
//Scene이 바뀔때 마다 설정하는 것들
void Render::Setting()
{
	if (mTcp.GetIsConnect() == false) {
		mTcp.Connect();
	}
	BackgroundManager::Get()->Setting();
	PlayerManager::Get()->Setting();
	GETCAMERA->Setting();
	mTcp.Setting();
	UiManager::Get()->Setting();
	ClientData::Get()->Setting();
	TaskManager::Get()->Setting();
	ImposterManager::Get()->Setting();
	CrewManager::Get()->Setting();
	GuitarClass::Get()->Setting();
}
