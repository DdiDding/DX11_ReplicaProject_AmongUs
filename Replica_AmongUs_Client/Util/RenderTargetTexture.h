#pragma once
class RenderTargetTexture
{
public:

	RenderTargetTexture();
	~RenderTargetTexture();
	void Shutdown();




	bool Initialize(ID3D11Device*, int, int);

	void SetRenderTarget(ID3D11DeviceContext*);
	void ClearRenderTarget(ID3D11DeviceContext*);
	ID3D11ShaderResourceView* GetShaderResourceView();

private:

	ID3D11Texture2D* mRenderTargetTexture; //·»´õÅ¸°Ùºä,[ÇÏ³ªÀÇ ÅØ½ºÃ³¸®¼Ò½º]
	ID3D11RenderTargetView* mRenderTargetView; //
	ID3D11ShaderResourceView* mShaderResourceView;//·»´õ¸µµÈ ÅØ½ºÃ³¸¦ º¸³»ÁÙ SRV
};

