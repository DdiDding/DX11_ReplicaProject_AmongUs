#include "../stdafx.h"
#include "ImageManager.h"

ImageManager::ImageManager()
{
	Init();
}

ImageManager::~ImageManager()
{
	mImageMap.clear();
}

void ImageManager::Init()
{
	createImage(L"Resorce/Player/walk.png");
	createImage(L"Resorce/Player/ghost.png");
	createImage(L"Resorce/Player/ghostOne.png");
	createImage(L"Resorce/Player/stand.png");
	createImage(L"Resorce/Player/DieBody.png");
	createImage(L"Resorce/Player/kill.png");
	createImage(L"Resorce/Player/spawn1.png");
	createImage(L"Resorce/Player/spawn2.png");

	createImage(L"Resorce/Background/FinalMap.png");
	createImage(L"Resorce/Background/lobyFinal.png");
	createImage(L"Resorce/Background/Snow.png");
	createImage(L"Resorce/Background/killBackGround.png");
	createImage(L"Resorce/Background/mainscreenCrew1.png");
	createImage(L"Resorce/Background/mainscreenCrew2.png");
	createImage(L"Resorce/Background/mainscreenCrew3.png");
	createImage(L"Resorce/Background/mainscreenCrew4.png");
	createImage(L"Resorce/Background/mainscreenCrew5.png");
	createImage(L"Resorce/Background/mainscreenCrew6.png");
	createImage(L"Resorce/Background/imposter.png");
	createImage(L"Resorce/Background/crew.png");
	createImage(L"Resorce/Background/fadeOut_left.png");
	createImage(L"Resorce/Background/fadeOut_right.png");
	createImage(L"Resorce/Background/shh/main.png");
	createImage(L"Resorce/Background/shh/pan.png");
	createImage(L"Resorce/Background/shh/son.png");
	createImage(L"Resorce/Background/shh/text.png");
	createImage(L"Resorce/Background/shh/front.png");

	createImage(L"Resorce/MiniMap/miniMap.png");
	createImage(L"Resorce/MiniMap/playerIcon.png");
	createImage(L"Resorce/MiniMap/sabotagi.png"); // -? 이건 테스크에..?

	createImage(L"Resorce/Task/TaskProgress.png");
	createImage(L"Resorce/Task/TaskProgressGage.png");
	createImage(L"Resorce/Task/adminMap.png");
	createImage(L"Resorce/Task/adminIcon.png");

	createImage(L"Resorce/Task/Yellow/obj_EmptyChute.png");
	createImage(L"Resorce/Task/Yellow/obj_uploadData.png");
	createImage(L"Resorce/Task/Yellow/obj_divertPower.png");
	createImage(L"Resorce/Task/Yellow/obj_cleanO2.png");
	createImage(L"Resorce/Task/Yellow/obj_swipeCard.png");

	createImage(L"Resorce/Task/White/obj_admin.png");
	createImage(L"Resorce/Task/White/obj_emergency.png");
	createImage(L"Resorce/Task/White/obj_sequrity.png");


	createImage(L"Resorce/Task/UploadData/base.png");
	createImage(L"Resorce/Task/UploadData/download.png");
	createImage(L"Resorce/Task/UploadData/file.png");
	createImage(L"Resorce/Task/UploadData/folder.png");
	createImage(L"Resorce/Task/UploadData/progressBar.png");
	createImage(L"Resorce/Task/UploadData/uploadButton.png");
	createImage(L"Resorce/Task/UploadData/shine.png");

	createImage(L"Resorce/Task/SwipeCard/admin_bg.png");
	createImage(L"Resorce/Task/SwipeCard/admin_card.png");
	createImage(L"Resorce/Task/SwipeCard/admin_sliderTop.png");
	createImage(L"Resorce/Task/SwipeCard/admin_textBar.png");
	createImage(L"Resorce/Task/SwipeCard/admin_walletFront.png");

	createImage(L"Resorce/Task/CleanFilter/arrowFinishedLeft.png");
	createImage(L"Resorce/Task/CleanFilter/arrowFinishedRight.png");
	createImage(L"Resorce/Task/CleanFilter/leftArrow.png");
	createImage(L"Resorce/Task/CleanFilter/rightArrow.png");
	createImage(L"Resorce/Task/CleanFilter/o2_CleanBack.png");
	createImage(L"Resorce/Task/CleanFilter/o2_CleanFront.png");
	createImage(L"Resorce/Task/CleanFilter/o2_leaf1.png");
	createImage(L"Resorce/Task/CleanFilter/o2_leaf2.png");
	createImage(L"Resorce/Task/CleanFilter/o2_leaf3.png");
	createImage(L"Resorce/Task/CleanFilter/o2_leaf4.png");
	createImage(L"Resorce/Task/CleanFilter/o2_leaf5.png");
	createImage(L"Resorce/Task/CleanFilter/o2_leaf6.png");
	createImage(L"Resorce/Task/CleanFilter/o2_leaf7.png");

	createImage(L"Resorce/Task/Sequrity/Security.png");


	createImage(L"Resorce/Ui/Ui_play.png");
	createImage(L"Resorce/Ui/Ui_btn.png");
	createImage(L"Resorce/Ui/Ui_TaskList.png");
	createImage(L"Resorce/Ui/Ui_naver.png");
	createImage(L"Resorce/Ui/Ui_mainMenu.png");
	createImage(L"Resorce/Ui/Ui_Start.png");
	createImage(L"Resorce/Ui/Logo.png");
	createImage(L"Resorce/Ui/playerIcon.png");


	createImage(L"Resorce/Kill/KillAniCrew.png");
	createImage(L"Resorce/Kill/KillAniImposter.png");
}

void ImageManager::createImage(WCHAR * fileName)
{
	ID3D11ShaderResourceView * srv;
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFile(GETDEVICE, fileName, NULL, NULL, &srv, NULL);
	SUCCEEDED(hr);

	mImageMap.insert(make_pair(fileName, srv));
}
//TODO::map 정상적으로 메모리 해제하기