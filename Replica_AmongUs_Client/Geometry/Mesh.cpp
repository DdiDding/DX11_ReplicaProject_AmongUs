#include "../stdafx.h"
#include "Mesh.h"

///////////////////////////////////////////////////////////////////////////////////////
//Public function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	�Լ� : Mesh / [ ������ 1]
	���� : �Ű������� �޾� �����ϰ� init�� �����Ѵ�
	�Ű�����
		1~4.World��Ŀ� ���� Scale, translation ���
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

	mSrv = ImageManager::Get()->GetImage(mImageRoute); //�̹��� ���� 

	init();
}



/*********************************************************************************
	�Լ� : Mesh / [ ������ 2]
	���� : ���� �����ڿ� �ٸ����� SRV�� ���⼭ �������� �ʴ´�
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
	�Լ� : Update
	���� : Mesh�� ���� �������� ����
*********************************************************************************/
void Mesh::Update()
{

	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation);

	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));
	
}



/*********************************************************************************
	�Լ� : Update_withCam
	���� : ������ǥ�� ī�޶� ��ǥ�� �ٿ��� ��ǥ�� ������Ʈ�Ѵ�
*********************************************************************************/
void Mesh::Update_withCam()
{
	D3DXVECTOR3 tempCamPos = GETCAMERA->GetCameraPos();
	tempCamPos.x -= WinMaxWidthHalf;
	tempCamPos.y -= WinMaxHeightHalf;

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, tempCamPos.x + mTransX, tempCamPos.y + mTransY, mRotation);

	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));
}



/*********************************************************************************
	�Լ� : Update_Uv
	���� : VertexData�� Uv�� ����
*********************************************************************************/
void Mesh::Update_Uv(D3DXVECTOR2 uv0, D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3)
{

	//1.���� �� ����ü ������ ����
	{
		//�����ϴ�
		mVertexData.GetData()->at(0).uv = uv0;
		//�������
		mVertexData.GetData()->at(1).uv = uv1;
		//�������
		mVertexData.GetData()->at(2).uv = uv2;
		//�����ϴ�						   
		mVertexData.GetData()->at(3).uv = uv3;
	}

	//2.���ؽ����� ������Ʈ (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());
}

/*********************************************************************************
	�Լ� : SetVertexDataCenter
	���� : �����ϴ��� ������ġ�� (0, 0) �̾ƴ�  (-1, -1)�ιٲپ� (0,0)��ġ�� �簢�� �߽ɿ� ���� ����
*********************************************************************************/
void Mesh::SetVertexDataCenter()
{
	//1.���� �� ����ü ������ ����
	{
		//�����ϴ�
		mVertexData.GetData()->at(0).position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		//�������
		mVertexData.GetData()->at(1).position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		//�������
		mVertexData.GetData()->at(2).position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		//�����ϴ�					
		mVertexData.GetData()->at(3).position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	}

	//2.���ؽ����� ������Ʈ (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());
}

/*********************************************************************************
	�Լ� : Update_ps_int
	���� : int�� �ڷḦ PixelShader�� ������۷� �ѱ��
*********************************************************************************/
void Mesh::Update_ps_int(int value)
{
	
	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_int cBufferSubResource2;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	cBufferSubResource2.plusData = value;

	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_ps, &cBufferSubResource2, sizeof(cBufferSubResource2));
}



/*********************************************************************************
	�Լ� : Update_player
	���� : �÷��̾������� Mesh�� ��Ÿ��������� Update�ϴ� �Լ� - Update�� �̰��ϳ��� ����ϸ� ��
	�Ű�����
		1.colorBody - �Ӱ��� ��
		2.colorBodyShadow - �� �׸��ڻ�
*********************************************************************************/
void Mesh::Update_player(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow)
{
	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation, colorBody, colorBodyShadow);

	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_player, &cBufferSubResource, sizeof(cBufferSubResource));
}


/*********************************************************************************
	�Լ� : Render
	���� : �� ���ҽ��� ���������ο� �����Ѵ�
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

	//IA�� inputLayout����, ���̴����ܰ迡 ����
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
	�Լ� : Init
	���� : �ʱ�ȭ, �� Buffer���ҽ��� State�� �����Ѵ�
*********************************************************************************/
void Mesh::init()
{
	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer ����
	mBufferInterface.CreateIndexBuffer_rect(&mIndexBuffer); // IndexBuffer ����
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_vs, sizeof(ConstantStruct_matrix::constantStruct_matrix));
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_ps, sizeof(ConstantStruct_matrix::constantStruct_int));
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_player, sizeof(ConstantStruct_player::constantStruct_player));

	mShader = new Shader(mVertexData, mHlslName); //Shader, ������� ����

	createSamplerState(); //SamplerState ����
	createBlendState(); //BlendState ����
}

//TODO:: STate ���� Ŭ���� ��������
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

