#include "../../../stdafx.h"
#include "../../Mesh.h"
#include "../../../Util/RenderTargetTexture.h"
#include "../../../Manager/PlayerManager.h"
#include "../../../Manager/BackgroundManager.h"
#include "Sequrity_Sequrity.h"


Sequrity_Sequrity::Sequrity_Sequrity()
{
	mBackground = new Mesh(1280.0f, 720.0f, 0.0f, 0.0f, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/Sequrity/Security.png");
	mClosseBtn = new Mesh(72.0f, 72.0f, 207, 623, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_btn.png");
	mClosseBtn->Update_Uv(
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f / 3, 0.0f),
		D3DXVECTOR2(1.0f / 3, 1.0f)
	);

	mClickEnd = false;

	mRenderTargetView1 = new RenderTargetTexture();
	mRenderTargetView1->Initialize(GETDEVICE, WinMaxWidth, WinMaxHeight);
	mRenderTargetView2 = new RenderTargetTexture();
	mRenderTargetView2->Initialize(GETDEVICE, WinMaxWidth, WinMaxHeight);

	mCamera1 = new Mesh(636, 358, 323.0f, 231.0f, L"./Hlsl/TextureShader.hlsl");
	mCamera1->SetSrv(mRenderTargetView1->GetShaderResourceView());
	mCamera2 = new Mesh(259, 146.0f, 1029.0f, 479.0f, L"./Hlsl/TextureShader.hlsl");
	mCamera2->SetSrv(mRenderTargetView2->GetShaderResourceView());
	mCamera2->SetRotation(-8.13999676f);

	//여기서 한번만??
	mCamera1->Update_withCam();
	mCamera2->Update_withCam();
}

Sequrity_Sequrity::~Sequrity_Sequrity()
{
}

void Sequrity_Sequrity::Update()
{
	
	mBackground->Update_withCam();
	mClosseBtn->Update_withCam();

	

	//엑스누르면 꺼지는걸로하자

	if (Mouse::Get()->Down(1) == true) {
		if (mClosseBtn->IsClik() == true) {
			mClickEnd = true;
		}
	}
}

void Sequrity_Sequrity::Render()
{
	mBackground->Render();
	mClosseBtn->Render();


	//원본 카메라 값, 프로젝션 값을 잠시보관
	D3DXVECTOR3 tempCamPos = GETCAMERA->GetCameraPos_onlyCam();
	D3DXMATRIX tempLoadProjection = Graphic::Get()->GetProjection();

	////////////////////////////////////////////////////////////////////////
	//카메라 1 렌더링

	//Camera view, Projection 각 카메라에 맞게 세팅
	GETCAMERA->SetCamera(D3DXVECTOR3(2230, 874, 0));
	GETCAMERA->Update();
	D3DXMATRIX tempProjection;
	D3DXMatrixOrthoOffCenterLH(&tempProjection, 0, (float)WinMaxWidth/2, 0, (float)WinMaxHeight/2, 0, 1);
	Graphic::Get()->SetProjection(tempProjection);


	mRenderTargetView1->SetRenderTarget(GETDC);
	mRenderTargetView1->ClearRenderTarget(GETDC);


	BackgroundManager::Get()->Update();
	PlayerManager::Get()->Update_noMove();
	BackgroundManager::Get()->Render();
	PlayerManager::Get()->Render();

	GETCAMERA->SetCamera(D3DXVECTOR3(3461, 2054, 0));
	GETCAMERA->Update();


	////////////////////////////////////////////////////////////////////////
	//카메라 2 렌더링

	//Camera view, Projection 각 카메라에 맞게 세팅
	mRenderTargetView2->SetRenderTarget(GETDC);
	mRenderTargetView2->ClearRenderTarget(GETDC);
	D3DXMatrixOrthoOffCenterLH(&tempProjection, 0, 500.0f, 0, 281.0f, 0, 1);
	Graphic::Get()->SetProjection(tempProjection);


	BackgroundManager::Get()->Update();
	PlayerManager::Get()->Update_noMove();
	BackgroundManager::Get()->Render();
	PlayerManager::Get()->Render();


	////////////////////////////////////////////////////////////////////////
	//메인백버퍼로 다시 렌더타겟 세팅
	Graphic::Get()->SetBackBufferRenderTarget();

	GETCAMERA->SetCamera(tempCamPos);
	Graphic::Get()->SetProjection(tempLoadProjection);

	//cctv 렌더링
	mCamera1->Render();
	mCamera2->Render();
}
