#include "../stdafx.h"
#include "../Geometry/Mesh.h"
#include "../Geometry/ColorMesh.h"
#include "EndAniManager.h"


void EndAniManager::Update()
{
	if (mIsStartChangeAni == true) endAniUpdate();

}

void EndAniManager::Render()
{
	if (mIsRenderChangeAni == true) endAniRender();

}

EndAniManager::EndAniManager()
{
	init();
}


EndAniManager::~EndAniManager()
{
}


void EndAniManager::init()
{
	mInGame_allBlack = new ColorMesh(4874.0f, 3222.0f, 0, 0, L"./Hlsl/AllBlackShader.hlsl");
}


void EndAniManager::endAniUpdate()
{

	switch (SceneManager::Get()->GetScene())
	{
		//메인메뉴에서 끝내달라고 요청들어오면  뭐없으니까 그냥 넘겨준다
	case SCENE_MAINMENU: 
		mIsStartChangeAni = false; 
		mIsRenderChangeAni = false; 
		mIsOkChangeScene = true; 
		break;

		//로비에서 
	case SCENE_LOBY:

		//인게임 시작화면으로 간다면
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_START) {

			//할게 있으니 렌더링해야한다
			mIsRenderChangeAni = true;
			mInGame_allBlack->Update();
			mInGame_allBlack->Update_ps_float(mBlackAlpha);

			//계속 알파값추가해서 어두워지게함
			if (mBlackAlpha < 1.5f) {  mBlackAlpha += 0.01f;  }
		}
		//다시메인메뉴 화면으로가면 그냥 보내준다
		else if (SceneManager::Get()->GetNextScene() == SCENE_MAINMENU) {
		
			mIsStartChangeAni = false;
			mIsRenderChangeAni = false;
			mIsOkChangeScene = true;
		}
		break;
		//게임시작단계에서
	case SCENE_INGAME_START: {

		//실제 인게임으로 갈때
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_PLAY) {

			mIsStartChangeAni = false;
			mIsRenderChangeAni = false;
			mIsOkChangeScene = true;
		}
	} break;
	case SCENE_INGAME_PLAY: {

		//인게임에서 마무리 하기
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_END) {

			//할게 있으니 렌더링해야한다
			mIsRenderChangeAni = true;
			mInGame_allBlack->Update();
			mInGame_allBlack->Update_ps_float(mBlackAlpha);

			//계속 알파값추가해서 어두워지게함
			if (mBlackAlpha < 1.5f) { mBlackAlpha += 0.01f; }
		}
	} break;
	case SCENE_INGAME_END: {

		mIsStartChangeAni = false;
		mIsRenderChangeAni = false;
		mIsOkChangeScene = true;
		break;
	} break;
	default:break;
	}
	
}

void EndAniManager::endAniRender()
{

	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_MAINMENU: break; //뭐 없음

		//로비에서 
	case SCENE_LOBY:

		//인게임 시작화면으로 간다면
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_START) {

			mInGame_allBlack->Render();

			//다 어두워지고 통신특에서도 OK하면 바꿔도 된다고 하고, 랜더링을그만둔다 [ 1.5인 이유는 여운을 남기려고 ]
			if (1.5f < mBlackAlpha) {	

				//애니메이션 완료 - 나머지초기화
				mIsStartChangeAni = false; //업데이트 안해도돼
				mIsRenderChangeAni = false;	 //렌더링 안해도 돼	
				mIsOkChangeScene = true; //이제 씬 바꿔
				mBlackAlpha = 0.0f;//초기화
			}

		}
		//다시메인메뉴 화면으로가면 그냥 보내준다
		else if (SceneManager::Get()->GetNextScene() == SCENE_MAINMENU) {
			mIsStartChangeAni = false; mIsRenderChangeAni = false; mIsOkChangeScene = true;
		}
		break;
	case SCENE_INGAME_START: {

		
	} break;
	case SCENE_INGAME_PLAY: {

		//인게임 시작화면으로 간다면
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_END) {

			mInGame_allBlack->Render();

			//다 어두워지고 통신특에서도 OK하면 바꿔도 된다고 하고, 랜더링을그만둔다 [ 1.5인 이유는 여운을 남기려고 ]
			if (1.5f < mBlackAlpha) {

				//애니메이션 완료 - 나머지초기화
				mIsStartChangeAni = false; //업데이트 안해도돼
				mIsRenderChangeAni = false;	 //렌더링 안해도 돼	
				mIsOkChangeScene = true; //이제 씬 바꿔
				mBlackAlpha = 0.0f;//초기화
				
			}
		}
	} break;
	default:break;
	}

}
