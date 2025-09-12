#pragma once

enum {
	SCENE_MAINMENU = 0,
	SCENE_LOBY = 1,
	SCENE_INGAME_START = 2, //이게 쉿이 나오고 임포스터인지 시민인지 등장씬
	SCENE_INGAME_PLAY = 3, //본격적인 게임 시작 씬
	SCENE_INGAME_CHAT,
	SCENE_INGAME_END,//게임이 끝나기위한 준비
	SCENE_RESULT//게임의결과화면
};

class SceneManager :public SingletonBase<SceneManager>
{
public:

	friend class SingletonBase<SceneManager>;

	
	void SetScene(UINT setSceneNum) { mScene = setSceneNum; };
	UINT GetScene() { return mScene; };

	void SetNextScene(UINT setSceneNum) { mNextScene = setSceneNum; };
	UINT GetNextScene() { return mNextScene; };

	//다음씬으로 바꾼다
	void ChangeScene() { mScene = mNextScene; };

private:

	SceneManager();
	~SceneManager();

	void init();


	UINT mScene;
	UINT mNextScene;
};

