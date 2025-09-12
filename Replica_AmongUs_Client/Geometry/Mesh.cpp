#include "../stdafx.h"
#include "Mesh.h"

///////////////////////////////////////////////////////////////////////////////////////
//Public function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	함수 : Mesh / [ 생성자 1]
	목적 : 매개변수를 받아 저장하고 init을 실행한다
	매개변수
		1~4.World행렬에 계산될 Scale, translation 상수
*********************************************************************************/
Mesh::Mesh(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute)
{
	mSizeX = sizeX;
	mSizeY = sizeY;

	mHalfSizeX = mSizeX / 2;
	mHalfSizeY = mSizeY / 2;

	mTransX = transX;
	mTransY = transY;

	mHlslName = hlslName;

	mImageRoute = imageRoute;

	mSrv = ImageManager::Get()->GetImage(mImageRoute); //이미지 세팅 

	init();
}



/*********************************************************************************
	함수 : Mesh / [ 생성자 2]
	목적 : 위의 생성자와 다른점은 SRV를 여기서 연결하지 않는다
*********************************************************************************/
Mesh::Mesh(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName)
{
	mSizeX = sizeX;
	mSizeY = sizeY;

	mHalfSizeX = mSizeX / 2;
	mHalfSizeY = mSizeY / 2;

	mTransX = transX;
	mTransY = transY;

	mHlslName = hlslName;

	init();
}


Mesh::~Mesh()
{
	SAFE_DELETE(mShader);
}


/*********************************************************************************
	함수 : Update
	목적 : Mesh에 관한 변수들을 변경
*********************************************************************************/
void Mesh::Update()
{

	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));
	
}



/*********************************************************************************
	함수 : Update_withCam
	목적 : 월드좌표를 카메라 좌표에 붙여서 좌표를 업데이트한다
*********************************************************************************/
void Mesh::Update_withCam()
{
	D3DXVECTOR3 tempCamPos = GETCAMERA->GetCameraPos();
	tempCamPos.x -= WinMaxWidthHalf;
	tempCamPos.y -= WinMaxHeightHalf;

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, tempCamPos.x + mTransX, tempCamPos.y + mTransY, mRotation);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));
}



/*********************************************************************************
	함수 : Update_Uv
	목적 : VertexData의 Uv를 변경
*********************************************************************************/
void Mesh::Update_Uv(D3DXVECTOR2 uv0, D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3)
{

	//1.변경 할 구조체 데이터 변경
	{
		//좌측하단
		mVertexData.GetData()->at(0).uv = uv0;
		//좌측상단
		mVertexData.GetData()->at(1).uv = uv1;
		//우측상단
		mVertexData.GetData()->at(2).uv = uv2;
		//우측하단						   
		mVertexData.GetData()->at(3).uv = uv3;
	}

	//2.버텍스버퍼 업데이트 (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());
}

/*********************************************************************************
	함수 : SetVertexDataCenter
	목적 : 좌측하단의 정점위치를 (0, 0) 이아닌  (-1, -1)로바꾸어 (0,0)위치가 사각형 중심에 오게 변경
*********************************************************************************/
void Mesh::SetVertexDataCenter()
{
	//1.변경 할 구조체 데이터 변경
	{
		//좌측하단
		mVertexData.GetData()->at(0).position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		//좌측상단
		mVertexData.GetData()->at(1).position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		//우측상단
		mVertexData.GetData()->at(2).position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		//우측하단					
		mVertexData.GetData()->at(3).position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	}

	//2.버텍스버퍼 업데이트 (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());
}

/*********************************************************************************
	함수 : Update_ps_int
	목적 : int형 자료를 PixelShader에 상수버퍼로 넘긴다
*********************************************************************************/
void Mesh::Update_ps_int(int value)
{
	
	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_int cBufferSubResource2;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	cBufferSubResource2.plusData = value;

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_ps, &cBufferSubResource2, sizeof(cBufferSubResource2));
}



/*********************************************************************************
	함수 : Update_player
	목적 : 플레이어종류의 Mesh를 나타내고싶을때 Update하는 함수 - Update는 이거하나만 사용하면 됌
	매개변수
		1.colorBody - 머갈통 색
		2.colorBodyShadow - 몸 그림자색
*********************************************************************************/
void Mesh::Update_player(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow)
{
	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation, colorBody, colorBodyShadow);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_player, &cBufferSubResource, sizeof(cBufferSubResource));
}


/*********************************************************************************
	함수 : Render
	목적 : 각 리소스를 파이프라인에 연결한다
*********************************************************************************/
void Mesh::Render()
{
	//IA stage
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer_vs, 0);
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer_player, 2);
	//PS stage
	mBufferInterface.SetConstantBuffer_ps(&mConstantBuffer_ps, 1);


	//PS stage
	GETDC->PSSetShaderResources(0, 1, &mSrv);
	GETDC->PSSetSamplers(0, 1, &mSamplerState);

	//IA에 inputLayout연결, 셰이더각단계에 연결
	mShader->Render();

	//OM stage
	GETDC->OMSetBlendState(mBlendState, nullptr, 0xffffffff);


	//Draw
	mBufferInterface.Draw();
}

bool Mesh::IsClik()
{
	RECT tempRect = { (int)mTransX, (int)mTransY + (int)mSizeY, (int)mTransX + (int)mSizeX, (int)mTransY};
	return Collision::Get()->PointAndRect(Mouse::Get()->GetPosition(), tempRect);
}

bool Mesh::IsClik_Center()
{
	RECT tempRect = { (int)mTransX - (int)mSizeX, (int)mTransY + (int)mSizeY, (int)mTransX + (int)mSizeX, (int)mTransY - (int)mSizeY };
	return Collision::Get()->PointAndRect(Mouse::Get()->GetPosition(), tempRect);
}


///////////////////////////////////////////////////////////////////////////////////////
//Private function
///////////////////////////////////////////////////////////////////////////////////////



/*********************************************************************************
	함수 : Init
	목적 : 초기화, 각 Buffer리소스와 State를 생성한다
*********************************************************************************/
void Mesh::init()
{
	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer 생성
	mBufferInterface.CreateIndexBuffer_rect(&mIndexBuffer); // IndexBuffer 생성
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_vs, sizeof(ConstantStruct_matrix::constantStruct_matrix));
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_ps, sizeof(ConstantStruct_matrix::constantStruct_int));
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_player, sizeof(ConstantStruct_player::constantStruct_player));

	mShader = new Shader(mVertexData, mHlslName); //Shader, 상수버퍼 생성

	createSamplerState(); //SamplerState 생성
	createBlendState(); //BlendState 생성
}

//TODO:: STate 따로 클래스 만들어관리
void Mesh::createSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc;

	//samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = FLT_MIN;
	samplerDesc.MaxLOD = FLT_MAX;

	GETDEVICE->CreateSamplerState(&samplerDesc, &mSamplerState);
}

void Mesh::createBlendState()
{
	D3D11_BLEND_DESC blendDesc;

	blendDesc.AlphaToCoverageEnable = true;
	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	GETDEVICE->CreateBlendState(&blendDesc, &mBlendState);
}

