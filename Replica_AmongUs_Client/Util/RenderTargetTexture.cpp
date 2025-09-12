#include "../stdafx.h"
#include "RenderTargetTexture.h"


/*
»ý¼ºÀÚ ,¼Ò¸êÀÚ
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
¸ñÀû : ·»´õÅ¸°ÙÅØ½ºÃ³, ·»´õÅ¸°Ùºä, ¼ÎÀÌ´õ¸®¼Ò½º ºä ¸¦ »ý¼ºÇÑ´Ù
*/
bool RenderTargetTexture::Initialize(ID3D11Device* device, int textureWidth, int textureHeight)
{

	HRESULT result;

	////////////////////////////////////////////////////////////////////////////////////
	// Create the render target texture.
	//  ·»´õÅ¸°Ù "ÅØ½ºÃ³" ¸¦ »ý¼º [ ºä ¾Æ´Ô] , [·»´õÅ¸°Ùºä¿¡ ²ÈÀ» ÅØ½ºÃ³¸®¼Ò½º]
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
	// ·»´õÅ¸°Ù "ºä" ¸¦ »ý¼º [ ÅØ½ºÃ³ ¾Æ´Ô]
	////////////////////////////////////////////////////////////////////////////////////

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

	// Setup the description of the render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; //¸®¼Ò½º´Â ÅØ½ºÃ³2D·Î ¾×¼¼½ºµË´Ï´Ù
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// ·»´õÅ¸°Ùºä »ý¼º
	result = device->CreateRenderTargetView(mRenderTargetTexture, &renderTargetViewDesc, &mRenderTargetView);



	////////////////////////////////////////////////////////////////////////////////////
	// ¼ÎÀÌ´õ ¸®¼Ò½º ºä »ý¼º
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
ÀÚ¿ø ÇØÁ¦
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
¸ñÀû: OM¿¡¼³Á¤µÈ ·»´õ Å¸°ÙÀ» ÀÌ Å¬·¡½º¿¡ÀÖ´Â ·»´õÅ¸°Ùºä·Î ¼³Á¤ÇÑ´Ù
*/
void RenderTargetTexture::SetRenderTarget(ID3D11DeviceContext* deviceContext)
{
	// Bind the render target view and depth stencil buffer to the output render pipeline.
	deviceContext->OMSetRenderTargets(1, &mRenderTargetView, NULL);

	return;
}



/*
¸ñÀû: Begin°ú °°´Ù ´Ù¸¸ ´ë»óÀÌ ÀÌ Å¬·¡½ºÀÇ·»´õÅ¸°Ùºä ÀÏ»Ó ! ±×¸®±âÀü¿¡ ²À È£ÃâÇÏÀÚ
*/
void RenderTargetTexture::ClearRenderTarget(ID3D11DeviceContext* deviceContext)
{
	// Clear the back buffer.
	deviceContext->ClearRenderTargetView(mRenderTargetView, D3DXCOLOR(1, 1, 1, 1));

	return;
}

/*
¸ñÀû: SRV¸¦ ÁØ´ç
*/
ID3D11ShaderResourceView* RenderTargetTexture::GetShaderResourceView()
{
	return mShaderResourceView;
}