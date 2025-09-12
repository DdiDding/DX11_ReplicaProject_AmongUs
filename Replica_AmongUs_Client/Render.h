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

	void RequestSetSceneEndManager(); //엔드 매니저에게 씬 바꿔달라고 요청
	void RequestSetScene(int scene); //씬을 바꿔달라고 요청하는 함수
	void UpdateScene();//요청하는 변수와 현재ㅣ 변수가 다르면 씬을 변경

	void Setting();
	
	bool GetGameEnd() { return mIsGameEnd; };




private:
	friend class SingletonBase< Render>;

	DebugMap * line;

	//TaskActtiveManager의 Update에서 결정되며 후에 Render까지 갈지 안갈지 결정한다
	bool mIsActtiveTask;

	bool mIsGameEnd; //게임 종료문 나중에 각 매니저에게 값받아서 업데이트


	//통신
	MatchingClient mTcp;

	//씬 부분
	int mRequestScene; //요청한 씬

	//test-----------------------

	Mesh * test;

};

