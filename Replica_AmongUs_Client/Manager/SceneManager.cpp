#include "../stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
	init();
}

SceneManager::~SceneManager()
{
}

void SceneManager::init()
{
	mScene = SCENE_MAINMENU;
	mNextScene = SCENE_MAINMENU;
}
