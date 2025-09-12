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
		//���θ޴����� �����޶�� ��û������  �������ϱ� �׳� �Ѱ��ش�
	case SCENE_MAINMENU: 
		mIsStartChangeAni = false; 
		mIsRenderChangeAni = false; 
		mIsOkChangeScene = true; 
		break;

		//�κ񿡼� 
	case SCENE_LOBY:

		//�ΰ��� ����ȭ������ ���ٸ�
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_START) {

			//�Ұ� ������ �������ؾ��Ѵ�
			mIsRenderChangeAni = true;
			mInGame_allBlack->Update();
			mInGame_allBlack->Update_ps_float(mBlackAlpha);

			//��� ���İ��߰��ؼ� ��ο�������
			if (mBlackAlpha < 1.5f) {  mBlackAlpha += 0.01f;  }
		}
		//�ٽø��θ޴� ȭ�����ΰ��� �׳� �����ش�
		else if (SceneManager::Get()->GetNextScene() == SCENE_MAINMENU) {
		
			mIsStartChangeAni = false;
			mIsRenderChangeAni = false;
			mIsOkChangeScene = true;
		}
		break;
		//���ӽ��۴ܰ迡��
	case SCENE_INGAME_START: {

		//���� �ΰ������� ����
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_PLAY) {

			mIsStartChangeAni = false;
			mIsRenderChangeAni = false;
			mIsOkChangeScene = true;
		}
	} break;
	case SCENE_INGAME_PLAY: {

		//�ΰ��ӿ��� ������ �ϱ�
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_END) {

			//�Ұ� ������ �������ؾ��Ѵ�
			mIsRenderChangeAni = true;
			mInGame_allBlack->Update();
			mInGame_allBlack->Update_ps_float(mBlackAlpha);

			//��� ���İ��߰��ؼ� ��ο�������
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
	case SCENE_MAINMENU: break; //�� ����

		//�κ񿡼� 
	case SCENE_LOBY:

		//�ΰ��� ����ȭ������ ���ٸ�
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_START) {

			mInGame_allBlack->Render();

			//�� ��ο����� ���Ư������ OK�ϸ� �ٲ㵵 �ȴٰ� �ϰ�, ���������׸��д� [ 1.5�� ������ ������ ������� ]
			if (1.5f < mBlackAlpha) {	

				//�ִϸ��̼� �Ϸ� - �������ʱ�ȭ
				mIsStartChangeAni = false; //������Ʈ ���ص���
				mIsRenderChangeAni = false;	 //������ ���ص� ��	
				mIsOkChangeScene = true; //���� �� �ٲ�
				mBlackAlpha = 0.0f;//�ʱ�ȭ
			}

		}
		//�ٽø��θ޴� ȭ�����ΰ��� �׳� �����ش�
		else if (SceneManager::Get()->GetNextScene() == SCENE_MAINMENU) {
			mIsStartChangeAni = false; mIsRenderChangeAni = false; mIsOkChangeScene = true;
		}
		break;
	case SCENE_INGAME_START: {

		
	} break;
	case SCENE_INGAME_PLAY: {

		//�ΰ��� ����ȭ������ ���ٸ�
		if (SceneManager::Get()->GetNextScene() == SCENE_INGAME_END) {

			mInGame_allBlack->Render();

			//�� ��ο����� ���Ư������ OK�ϸ� �ٲ㵵 �ȴٰ� �ϰ�, ���������׸��д� [ 1.5�� ������ ������ ������� ]
			if (1.5f < mBlackAlpha) {

				//�ִϸ��̼� �Ϸ� - �������ʱ�ȭ
				mIsStartChangeAni = false; //������Ʈ ���ص���
				mIsRenderChangeAni = false;	 //������ ���ص� ��	
				mIsOkChangeScene = true; //���� �� �ٲ�
				mBlackAlpha = 0.0f;//�ʱ�ȭ
				
			}
		}
	} break;
	default:break;
	}

}
