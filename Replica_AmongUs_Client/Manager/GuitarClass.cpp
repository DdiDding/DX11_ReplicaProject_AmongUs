#include "../stdafx.h"
#include "../Geometry/Mesh.h"
#include "../Manager/TaskManager.h"
#include "GuitarClass.h"

void GuitarClass::Update()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: {


	}; break;
	case SCENE_LOBY: {
	
	}break;
	case SCENE_INGAME_PLAY: {
	
		
		mProgressBar->Update_withCam();

		mProgressBarGage->Update_withCam();
		if (mProgressBarPercent != ClientData::Get()->mTotalTaskPercent) mProgressBarPercent++;
		mProgressBarGage->Update_ps_int(mProgressBarPercent);

	} break;
	default: break;
	}
}

void GuitarClass::Render()
{
	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: {


	}; break;
	case SCENE_LOBY: {

	}break;
	case SCENE_INGAME_PLAY: {

		mProgressBar->Render();
		mProgressBarGage->Render();

		FontManager::Get()->DrawFont_border(L"HYHeadLine", L"TOTAL  TASKS  COMPLETED", 14.0f, 22, 21, 0xffffffff, 0xff000000, 1);

		//랜더 순서때문에 플레이어 리스트 여기서랜더링함
		TaskManager::Get()->RenderPlayerTaskList();
	} break;
	default: break;
	}
}

void GuitarClass::Setting()
{
	switch (SceneManager::Get()->GetScene())
	{

	case SCENE_INGAME_END:	mProgressBarPercent = 0; break;
	default:
		break;
	}
}

GuitarClass::GuitarClass()
{
	init();
}

GuitarClass::~GuitarClass()
{
}

void GuitarClass::init()
{
	
	mProgressBar = new Mesh(547, 41, 10, 670, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/TaskProgress.png");
	mProgressBarGage = new Mesh(533, 25, 17, 678, L"./Hlsl/TaskProgressShader.hlsl", L"Resorce/Task/TaskProgressGage.png");
	mProgressBarPercent = 0;
}
