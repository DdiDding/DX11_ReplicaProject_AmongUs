#include "../stdafx.h"
#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	//플레이어의 기준 사이즈
	mPlayerOriginSize.x = 84.0f;
	mPlayerOriginSize.y = 110.0f;


	Init();
}

AnimationManager::~AnimationManager()
{
}
