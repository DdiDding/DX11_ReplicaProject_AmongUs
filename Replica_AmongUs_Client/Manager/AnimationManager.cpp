#include "../stdafx.h"
#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	//�÷��̾��� ���� ������
	mPlayerOriginSize.x = 84.0f;
	mPlayerOriginSize.y = 110.0f;


	Init();
}

AnimationManager::~AnimationManager()
{
}
