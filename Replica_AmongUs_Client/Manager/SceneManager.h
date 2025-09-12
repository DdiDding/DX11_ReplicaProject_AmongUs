#pragma once

enum {
	SCENE_MAINMENU = 0,
	SCENE_LOBY = 1,
	SCENE_INGAME_START = 2, //�̰� ���� ������ ������������ �ù����� �����
	SCENE_INGAME_PLAY = 3, //�������� ���� ���� ��
	SCENE_INGAME_CHAT,
	SCENE_INGAME_END,//������ ���������� �غ�
	SCENE_RESULT//�����ǰ��ȭ��
};

class SceneManager :public SingletonBase<SceneManager>
{
public:

	friend class SingletonBase<SceneManager>;

	
	void SetScene(UINT setSceneNum) { mScene = setSceneNum; };
	UINT GetScene() { return mScene; };

	void SetNextScene(UINT setSceneNum) { mNextScene = setSceneNum; };
	UINT GetNextScene() { return mNextScene; };

	//���������� �ٲ۴�
	void ChangeScene() { mScene = mNextScene; };

private:

	SceneManager();
	~SceneManager();

	void init();


	UINT mScene;
	UINT mNextScene;
};

