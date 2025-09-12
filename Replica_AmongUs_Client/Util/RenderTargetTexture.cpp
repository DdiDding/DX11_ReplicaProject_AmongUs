#include "../stdafx.h"
#include "RenderTargetTexture.h"


/*
������ ,�Ҹ���
*/
RenderTargetTexture::RenderTargetTexture()
{
	mRenderTargetTexture = 0;
	mRenderTargetView = 0;
	mShaderResourceView = 0;
}
RenderTargetTexture::~RenderTargetTexture()
{
	Shutdown();
}

/*
���� : ����Ÿ���ؽ�ó, ����Ÿ�ٺ�, ���̴����ҽ� �� �� �����Ѵ�
*/
bool RenderTargetTexture::Initialize(ID3D11Device* device, int textureWidth, int textureHeight)
{

	HRESULT result;

	////////////////////////////////////////////////////////////////////////////////////
	// Create the render target texture.
	//  ����Ÿ�� "�ؽ�ó" �� ���� [ �� �ƴ�] , [����Ÿ�ٺ信 ���� �ؽ�ó���ҽ�]
	////////////////////////////////////////////////////////////////////////////////////

	D3D11_TEXTURE2D_DESC textureDesc;
	// Initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));


	// Setup the render target texture description.
	textureDesc.Width = textureWidth;
	textureDesc.Height = textureHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	result = device->CreateTexture2D(&textureDesc, NULL, &mRenderTargetTexture);




	////////////////////////////////////////////////////////////////////////////////////
	// ����Ÿ�� "��" �� ���� [ �ؽ�ó �ƴ�]
	////////////////////////////////////////////////////////////////////////////////////

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

	// Setup the description of the render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; //���ҽ��� �ؽ�ó2D�� �׼����˴ϴ�
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// ����Ÿ�ٺ� ����
	result = device->CreateRenderTargetView(mRenderTargetTexture, &renderTargetViewDesc, &mRenderTargetView);



	////////////////////////////////////////////////////////////////////////////////////
	// ���̴� ���ҽ� �� ����
	////////////////////////////////////////////////////////////////////////////////////

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource view.
	result = device->CreateShaderResourceView(mRenderTargetTexture, &shaderResourceViewDesc, &mShaderResourceView);


	return true;
}

/*
�ڿ� ����
*/
void RenderTargetTexture::Shutdown()
{
	if (mShaderResourceView)
	{
		mShaderResourceView->Release();
		mShaderResourceView = 0;
	}

	if (mRenderTargetView)
	{
		mRenderTargetView->Release();
		mRenderTargetView = 0;
	}

	if (mRenderTargetTexture)
	{
		mRenderTargetTexture->Release();
		mRenderTargetTexture = 0;
	}

	return;
}


/*
����: OM�������� ���� Ÿ���� �� Ŭ�������ִ� ����Ÿ�ٺ�� �����Ѵ�
*/
void RenderTargetTexture::SetRenderTarget(ID3D11DeviceContext* deviceContext)
{
	// Bind the render target view and depth stencil buffer to the output render pipeline.
	deviceContext->OMSetRenderTargets(1, &mRenderTargetView, NULL);

	return;
}



/*
����: Begin�� ���� �ٸ� ����� �� Ŭ�����Ƿ���Ÿ�ٺ� �ϻ� ! �׸������� �� ȣ������
*/
void RenderTargetTexture::ClearRenderTarget(ID3D11DeviceContext* deviceContext)
{
	// Clear the back buffer.
	deviceContext->ClearRenderTargetView(mRenderTargetView, D3DXCOLOR(1, 1, 1, 1));

	return;
}

/*
����: SRV�� �ش�
*/
ID3D11ShaderResourceView* RenderTargetTexture::GetShaderResourceView()
{
	return mShaderResourceView;
}