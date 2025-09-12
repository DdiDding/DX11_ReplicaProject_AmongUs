#pragma once
#include "stdafx.h"
////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////

class Graphic : public SingletonBase<Graphic>
{
private:
	friend class SingletonBase<Graphic>;

	//����̽�
	ID3D11Device * m_device;
	//����̽� ���ؽ�Ʈ
	ID3D11DeviceContext * m_dc;
	//����ü��
	IDXGISwapChain * m_swapChain;
	//����Ÿ�ٺ� 
	ID3D11RenderTargetView * m_rtv;
	//�����Ͷ����� ������Ʈ
	ID3D11RasterizerState * m_rasterState;

	D3D11_VIEWPORT m_viewport;

	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;


	//��������ȭ üũ, true - Ȱ��ȭ, false - ��Ȱ��ȭ
	bool m_vsyncEnabled = false;


public:

	Graphic();
	~Graphic();

	//�ʱ�ȭ
	void Init(HWND hwnd);

	//�׸��� ����
	void Begin();
	//�׸��� ��
	void End();

	void SetBackBufferRenderTarget();

	//��������ȭ ����
	void SetVsync(bool value) { m_vsyncEnabled = value; };

	//device�� dc��������
	ID3D11Device* GetDevice() { return m_device; }
	ID3D11DeviceContext* GetDC() { return m_dc; }

	void SetProjection(D3DXMATRIX value) { m_projectionMatrix = value; };
	D3DXMATRIX GetProjection() { return m_projectionMatrix; };

};

