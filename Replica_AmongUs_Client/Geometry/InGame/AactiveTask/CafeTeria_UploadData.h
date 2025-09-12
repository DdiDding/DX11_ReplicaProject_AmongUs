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
	bool mLeftStop;//�ִϸ��̼� �������?
	bool mRightStop;

	bool mIsLeftReverse; //�Ųٷ�����Ұ���?
	bool mIsRightReverse; //�Ųٷ�����Ұ���?

	float mFolderTime_left; //������ ���� �������� ����ϱ����� �ð�
	float mFolderTime_right; //������ ���� �������� ����ϱ����� �ð�
	float mCloseTime; //���� ������ �������ϴ��� �ð�
	
	float mPassEstTime;//mEstimatedTime�� �Ѿ�� ���� �ð���� ����
	int mEtIndex;//mEstimatedTime�� index
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

	bool mIsComplete; //�̼��� �Ϸ��ߴ��� - 100%�� �Ǹ� true�� �˴ϴ�
	bool mClickEnd; // X��ư �����°�??


	//���� �Ʒ��� ȿ���ֱ����� ��ü���� �̵���(y��)
	float mAllMeshMove;

	bool mIsUp;//���οö󰡴����ΰ�?
	bool mIsDown;//���οö󰡴����ΰ�?

	float mDownTime;//�Ϸ�ǰ� �������� �ִϸ��̼� ���� ���� �ð�
};

