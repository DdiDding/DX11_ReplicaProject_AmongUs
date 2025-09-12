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

	ID3D11Texture2D* mRenderTargetTexture; //����Ÿ�ٺ�,[�ϳ��� �ؽ�ó���ҽ�]
	ID3D11RenderTargetView* mRenderTargetView; //
	ID3D11ShaderResourceView* mShaderResourceView;//�������� �ؽ�ó�� ������ SRV
};

