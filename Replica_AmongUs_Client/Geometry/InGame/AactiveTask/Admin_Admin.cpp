#include "../../../stdafx.h"
#include "../../Mesh.h"
#include "Admin_Admin.h"

Admin_Admin::Admin_Admin()
{
	mMap = new Mesh(922.0f, 647.0f, 179, 38, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/adminMap.png");
	mIcon = new Mesh(36, 30.0f, 179, 38, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/adminIcon.png");
	mClosseBtn = new Mesh(72.0f, 72.0f, 179, 600, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_btn.png");
	mClosseBtn->Update_Uv(
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f / 3, 0.0f),
		D3DXVECTOR2(1.0f / 3, 1.0f)
	);

	mClickEnd = false;
}

Admin_Admin::~Admin_Admin()
{

}

void Admin_Admin::Update()
{
	mClosseBtn->Update_withCam();
	mMap->Update_withCam();

	if (Mouse::Get()->Down(1) == true && mClosseBtn->IsClik() == true) {
		mClickEnd = true;
	}
}

void Admin_Admin::Render()
{
	//한명나올떄마다 카운트 ++
	int cafeCnt = 0;
	int o2Cnt = 0;
	int adminCnt = 0;
	int securityCnt = 0;


	for (int index = 0; index < 4; index++) {

		//일단 존재해야하고
		if (ClientData::Get()->mAnotherPlayer_inGame[index].mExist == true) {

			//살아있어야함
			if (ClientData::Get()->mAnotherPlayer_inGame[index].mIsDieSecond == false) {

				int pArea = ClientData::Get()->mAnotherPlayer_inGame[index].mPlayerWhere;


				if (pArea == 4) cafeCnt++;
				else if (pArea == 5) o2Cnt++;
				else if (pArea == 6) securityCnt++;
				else if (pArea == 7) adminCnt++;
			}
		}
	}

	mMap->Render();

	if (0 < cafeCnt) {
		mIcon->SetTrans({ 602, 521 });
		for (int i = 0; i < cafeCnt; i++) {

			mIcon->Update_withCam();
			mIcon->SetPlusTransX(40.0f);
			mIcon->Render();
		}
	}

	if (0 < o2Cnt) {
		mIcon->SetTrans({ 184, 421});
		for (int i = 0; i < o2Cnt; i++) {

			mIcon->Update_withCam();
			mIcon->SetPlusTransX(40.0f);
			mIcon->Render();
		}
	}

	if (0 < adminCnt) {
		mIcon->SetTrans({ 429,103});
		for (int i = 0; i < adminCnt; i++) {

			mIcon->Update_withCam();
			mIcon->SetPlusTransX(40.0f);
			mIcon->Render();
		}
	}

	if (0 < securityCnt) {
		mIcon->SetTrans({ 1008, 410 });
		for (int i = 0; i < securityCnt; i++) {

			mIcon->Update_withCam();
			mIcon->SetPlusTransX(40.0f);
			mIcon->Render();
		}
	}

	mClosseBtn->Render();
}
