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

	//���⼭ �ѹ���??
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

	

	//���������� �����°ɷ�����

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


	//���� ī�޶� ��, �������� ���� ��ú���
	D3DXVECTOR3 tempCamPos = GETCAMERA->GetCameraPos_onlyCam();
	D3DXMATRIX tempLoadProjection = Graphic::Get()->GetProjection();

	////////////////////////////////////////////////////////////////////////
	//ī�޶� 1 ������

	//Camera view, Projection �� ī�޶� �°� ����
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
	//ī�޶� 2 ������

	//Camera view, Projection �� ī�޶� �°� ����
	mRenderTargetView2->SetRenderTarget(GETDC);
	mRenderTargetView2->ClearRenderTarget(GETDC);
	D3DXMatrixOrthoOffCenterLH(&tempProjection, 0, 500.0f, 0, 281.0f, 0, 1);
	Graphic::Get()->SetProjection(tempProjection);


	BackgroundManager::Get()->Update();
	PlayerManager::Get()->Update_noMove();
	BackgroundManager::Get()->Render();
	PlayerManager::Get()->Render();


	////////////////////////////////////////////////////////////////////////
	//���ι���۷� �ٽ� ����Ÿ�� ����
	Graphic::Get()->SetBackBufferRenderTarget();

	GETCAMERA->SetCamera(tempCamPos);
	Graphic::Get()->SetProjection(tempLoadProjection);

	//cctv ������
	mCamera1->Render();
	mCamera2->Render();
}
