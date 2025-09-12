#pragma once
#include "../../Mesh.h"
#include "../../AnimationMesh.h"

class CafeTeria_UploadData
{
public:

	CafeTeria_UploadData();
	~CafeTeria_UploadData();

	void Update();
	void Render();
	

	void SetIsClickEnd(bool value) { mClickEnd = value; };
	bool GetIsClickEnd() { return mClickEnd; };	
	bool GetComplete() {return mIsComplete;	}

private:

	Mesh * mDownload;
	bool mIsTaskStop;

	Mesh * mBase;
	Mesh * mFile;
	Mesh * mProgressBar; 
	int mProgressPercent;

	Mesh * mMiniFile;
	float mMiniFileTransX;
	float mMiniFileTransY;


	Mesh * mClosseBtn;
	
	Mesh * mShine;

	AnimationMesh mFolderTop_left = AnimationMesh("Task_UploadData_Folder", L"./Hlsl/TextureShader.hlsl", true, 446.0f, 360.0f);
	AnimationMesh mFolderTop_right = AnimationMesh("Task_UploadData_Folder", L"./Hlsl/TextureShader.hlsl", false, 697.0f, 360.0f);
	bool mLeftStop;//애니메이션 멈출거임?
	bool mRightStop;

	bool mIsLeftReverse; //거꾸로재생할거임?
	bool mIsRightReverse; //거꾸로재생할거임?

	float mFolderTime_left; //폴더의 언제 접히는지 계산하기위한 시간
	float mFolderTime_right; //폴더의 언제 접히는지 계산하기위한 시간
	float mCloseTime; //언제 폴더가 접혀야하는지 시간
	
	float mPassEstTime;//mEstimatedTime가 넘어가기 위한 시간재는 변수
	int mEtIndex;//mEstimatedTime의 index
	WCHAR * mEstimatedTime[8] = { 
	{L"1d  18hr  14m  26s"}, 
	{L"1d  11hr  22m  2s"},
	{L"7hr  31m  6s"},
	{L"2hr  8m  54s"},
	{L"9m  14s"},
	{L"3s"}, 
	{L"2s"}, 
	{L"1s"}
	};

	bool mIsComplete; //미션을 완료했는지 - 100%가 되면 true가 됩니다
	bool mClickEnd; // X버튼 눌렀는가??


	//위로 아래로 효과주기위한 전체적인 이동값(y축)
	float mAllMeshMove;

	bool mIsUp;//위로올라가는중인가?
	bool mIsDown;//위로올라가는중인가?

	float mDownTime;//완료되고 내려가는 애니메이션 간의 차이 시간
};

