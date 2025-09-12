#include "../../../stdafx.h"
#include "CafeTeria_UploadData.h"

CafeTeria_UploadData::CafeTeria_UploadData()
{
	mDownload = new Mesh(91.0f, 28.0f, 594.0f, 292.0f + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/UploadData/download.png");
	mBase = new Mesh(500.0f, 326.0f, 390.0f, 197.0f + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/UploadData/base.png");
	mFile = new Mesh(107.0f, 84.0f, 448.0f, 368.0f + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/UploadData/file.png");
	mProgressBar = new Mesh(308.0f, 23.0f, 445.0f, 300.0f + mAllMeshMove, L"./Hlsl/ProgressShader.hlsl", L"Resorce/Task/UploadData/progressBar.png");
	mClosseBtn = new Mesh(35.0f, 35.0f, 352.0f, 479.0f + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_btn.png");
	mClosseBtn->Update_Uv(
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f / 3, 0.0f),
		D3DXVECTOR2(1.0f / 3, 1.0f)
	);

	mShine = new Mesh(440.0f, 232.0f, 420.0f, 263.0f + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/UploadData/shine.png");
		

	mMiniFileTransX = 528.0f;
	mMiniFileTransY = 378.0f;
	mMiniFile = new Mesh(30.0f, 23.0f, mMiniFileTransX, mMiniFileTransY + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/UploadData/file.png");

	mIsLeftReverse = false;
	mIsRightReverse = false;
	mFolderTime_left = 0.0f;
	mFolderTime_right = 0.0f;
	mCloseTime = 0.7f;
	mPassEstTime = 0.0f;
	 
	mIsTaskStop = true;
	mLeftStop = true;
	mRightStop = true;

	mProgressPercent = 0;

	mEtIndex = 0;

	mIsComplete = false;
	mClickEnd = false;


	mAllMeshMove = -479;

	mIsUp = true;
	mIsDown = false;
}

CafeTeria_UploadData::~CafeTeria_UploadData()
{
	SAFE_DELETE(mDownload);
	SAFE_DELETE(mBase		);
	SAFE_DELETE(mFile		);
	SAFE_DELETE(mProgressBar);
	SAFE_DELETE(mClosseBtn	);
	SAFE_DELETE(mMiniFile);
}

void CafeTeria_UploadData::Update()
{
	mClickEnd = false; // ������ư �ȴ����ɷ� �׻� �ʱ�ȭ
	

	//�ö󰡴� �ִϸ��̼�
	if (mIsUp == true) {
		if (mAllMeshMove < 0) {
			mAllMeshMove += 60;
			//�׽�ũ ���Ʒ��� �̵�
			mDownload->SetTrans(594.0f, 292.0f + mAllMeshMove);
			mBase->SetTrans(390.0f, 197.0f + mAllMeshMove);
			mFile->SetTrans(448.0f, 368.0f + mAllMeshMove);
			mProgressBar->SetTrans(445.0f, 300.0f + mAllMeshMove);
			mClosseBtn->SetTrans(352.0f, 479.0f + mAllMeshMove);
			mShine->SetTrans(420.0f, 263.0f + mAllMeshMove);
			mFolderTop_left.SetTrans(446.0f, 360.0f + mAllMeshMove);
			mFolderTop_right.SetTrans(697.0f, 360.0f + mAllMeshMove);
		}
		else {
			mIsUp = false;
			mAllMeshMove = 0;
		}
	}
	//�������� �ִϸ��̼�
	else if(mIsComplete == true){

		mDownTime += Time::Get()->Delta();

		if (mDownTime > 1.0f) {

			if (mAllMeshMove > -500) {

				mAllMeshMove -= 60;
				//�׽�ũ ���Ʒ��� �̵�
				mDownload->SetTrans(594.0f, 292.0f + mAllMeshMove);
				mBase->SetTrans(390.0f, 197.0f + mAllMeshMove);
				mFile->SetTrans(448.0f, 368.0f + mAllMeshMove);
				mProgressBar->SetTrans(445.0f, 300.0f + mAllMeshMove);
				mClosseBtn->SetTrans(352.0f, 479.0f + mAllMeshMove);
				mShine->SetTrans(420.0f, 263.0f + mAllMeshMove);
				mFolderTop_left.SetTrans(446.0f, 360.0f + mAllMeshMove);
				mFolderTop_right.SetTrans(697.0f, 360.0f + mAllMeshMove);

				mFolderTop_left.UpdateFromCam(false, true);
				mFolderTop_right.UpdateFromCam(true, true);
				mProgressBar->Update_withCam();
			}
			else {
				mClickEnd = true;
			}
		}
	}

	mClosseBtn->Update_withCam();
	
	//�� ������Ʈ�� ī�޶���ǥ���߰��ؼ� ���� ����
	mBase->Update_withCam();
	mFile->Update_withCam();
	
	if (mIsTaskStop == true) {

		mDownload->Update_withCam();
	}

	//�ٿ�ε� �̹����� Ŭ�������� ����
	if (Mouse::Get()->Down(1)) {

		if (mDownload->IsClik() == true) { mIsTaskStop = false; mLeftStop = false; }

		if (mClosseBtn->IsClik() == true) { mClickEnd = true; }
	}

	if (mIsComplete == false) {
		//���� ���� �ִϸ��̼�
		if (mLeftStop == false) {

			if (mIsLeftReverse == false) {

				//�ִ� �����
				mFolderTop_left.UpdateFromCam(false, mIsTaskStop);

				//�������� �������ΰ�
				if (mFolderTop_left.IsFrameMax() == true) mIsLeftReverse = true;
			}
			else if (mIsLeftReverse == true) {

				mMiniFileTransX += 1.8f; // �����̵� ���

				//�ð� �Ŀ� �ϱ�
				if (mFolderTime_left > mCloseTime) {


					//�ִ� �����
					mFolderTop_left.UpdateFromCam(true, mIsTaskStop);

					//�������� ó���ΰ�
					if (mFolderTop_left.IsFrameZero() == true) {

						mRightStop = false;
						mLeftStop = true;
						mIsLeftReverse = false;
						mFolderTime_left = 0.0f;
					}
				}
				else {
					mFolderTime_left += Time::Get()->Delta();
				}
			}
		}
		else {
			mFolderTop_left.UpdateFromCam(true, true);
		}

		//������ ���� �ִ�
		if (mRightStop == false) {

			mMiniFileTransX += 1;

			//�ִ� �����
			if (mIsRightReverse == false) {

				mFolderTop_right.UpdateFromCam(false, mIsTaskStop);

				//�������� �������ΰ�
				if (mFolderTop_right.IsFrameMax() == true) {
					mIsRightReverse = true;
				}
			}
			//�ִ� �����
			else if (mIsRightReverse == true) {

				//�ð� �Ŀ� �ϱ�
				if (mFolderTime_right > mCloseTime) {


					//�ִ� �����
					mFolderTop_right.UpdateFromCam(true, mIsTaskStop);

					//�������� ó���ΰ�
					if (mFolderTop_right.IsFrameZero() == true) {

						mLeftStop = false;
						mRightStop = true;
						mFolderTime_right = 0.0f;
						mIsRightReverse = false;
						mMiniFileTransX = 528.0f;
					}
				}
				else {
					mFolderTime_right += Time::Get()->Delta();
				}
			}
		}
		else {
			mFolderTop_right.UpdateFromCam(false, true);
		}

		//�׽�ũ ���۽ÿ� �ߵ��ϴ� �׸���
		if (mIsTaskStop == false) {

			mMiniFile->SetTrans(mMiniFileTransX, mMiniFileTransY);
			mMiniFile->Update_withCam();

			mPassEstTime += Time::Get()->Delta();


			if (mEtIndex < 5) {

				if (mEtIndex == 0) { mProgressPercent = 0; }
				if (mEtIndex == 1) { mProgressPercent = 14; }
				if (mEtIndex == 2) { mProgressPercent = 28; }
				if (mEtIndex == 3) { mProgressPercent = 42; }
				if (mEtIndex == 4) { mProgressPercent = 56; }


				if (mPassEstTime > 1.0f) {

					mPassEstTime = 0.0f;
					mEtIndex++;
				}
				if (mEtIndex == 5) { mProgressPercent = 70; }
			}
			else if (mProgressPercent < 100) {

				mProgressPercent++;
				if (mProgressPercent % 10 == 0 && mProgressPercent != 100) mEtIndex++;
			}
			else {
				mIsComplete = true;
			}

			mProgressBar->Update_withCam();
			mProgressBar->Update_ps_int(mProgressPercent);
		}
	}

	mShine->Update_withCam();
}

void CafeTeria_UploadData::Render()
{
	mClosseBtn->Render();
	mBase->Render();
	mFile->Render();

	float tempY = WinMaxHeight - mAllMeshMove;

	if (mIsComplete == false) {
		if (mIsTaskStop == true) {

			mDownload->Render();
		}

		if (mIsTaskStop == false) {

			mProgressBar->Render();
			mMiniFile->Render();
			FontManager::Get()->DrawFont(L"Varela", L"Estimated  Time:", 22.0f, 445.0f, 423.0f, 0xffffffff);
			FontManager::Get()->DrawFont(L"Varela", mEstimatedTime[mEtIndex], 22.0f, 625.0f, 423.0f, 0xffffffff);

			wstring tempWstr = to_wstring(mProgressPercent) + L"%";
			WCHAR * tempWchar = _wcsdup(tempWstr.c_str());
			FontManager::Get()->DrawFont(L"Varela", tempWchar, 20.0f, 760.0f, 395.0f, 0xffffffff);
			free(tempWchar);
		}
	}
	else {
		mProgressBar->Render();
		FontManager::Get()->DrawFont(L"Varela", L"100%", 20.0f, 760.0f, 395.0f - mAllMeshMove, 0xffffffff);
		FontManager::Get()->DrawFont(L"Varela", L"Complete", 22.0f, 445.0f, 423.0f - mAllMeshMove, 0xffffffff);
	}


	mFolderTop_left.Render();
	mFolderTop_right.Render();

	mShine->Render();


	
	//��Ʈ�� �� ������ 0�̳� ���� ��ǥ�� ��������� �������� ����
	FontManager::Get()->DrawFont(L"Varela",L"CafeTeria",20.0f, 455.0f, tempY - 360.0f, 0xffffffff); //�� y�� 360
	FontManager::Get()->DrawFont(L"Varela",L"My  Tablet",20.0f, 730.0f, tempY - 360.0f, 0xffffffff);

	
	return;
}