#pragma once
#include "stdafx.h"
#include "Geometry/Mesh.h"
#include "Geometry/Line.h"
#include "Geometry/AnimationRect.h"
#include "Geometry/Debug/DebugMap.h"
#include "TcpClient/MatchingClient.h"

class AnimationMesh;

class Render : public SingletonBase< Render>
{
public:
	Render();
	~Render();


	void Init();


	void Update();
	void Update_mainMenu();
	void Update_loby();
	void Update_inGame_start();
	void Update_inGame();
	void Update_inGame_end();


	void Rendering();
	void Render_mainMenu();
	void Render_loby();
	void Render_inGame_start();
	void Render_inGame();
	void Render_inGame_end();

	void RequestSetSceneEndManager(); //���� �Ŵ������� �� �ٲ�޶�� ��û
	void RequestSetScene(int scene); //���� �ٲ�޶�� ��û�ϴ� �Լ�
	void UpdateScene();//��û�ϴ� ������ ����� ������ �ٸ��� ���� ����

	void Setting();
	
	bool GetGameEnd() { return mIsGameEnd; };




private:
	friend class SingletonBase< Render>;

	DebugMap * line;

	//TaskActtiveManager�� Update���� �����Ǹ� �Ŀ� Render���� ���� �Ȱ��� �����Ѵ�
	bool mIsActtiveTask;

	bool mIsGameEnd; //���� ���Ṯ ���߿� �� �Ŵ������� ���޾Ƽ� ������Ʈ


	//���
	MatchingClient mTcp;

	//�� �κ�
	int mRequestScene; //��û�� ��

	//test-----------------------

	Mesh * test;

};

