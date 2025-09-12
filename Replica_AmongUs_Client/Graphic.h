#pragma once
#include "stdafx.h"
////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////

class Graphic : public SingletonBase<Graphic>
{
private:
	friend class SingletonBase<Graphic>;

	//디바이스
	ID3D11Device * m_device;
	//디바이스 컨텍스트
	ID3D11DeviceContext * m_dc;
	//스왑체인
	IDXGISwapChain * m_swapChain;
	//렌더타겟뷰 
	ID3D11RenderTargetView * m_rtv;
	//레스터라이저 스테이트
	ID3D11RasterizerState * m_rasterState;

	D3D11_VIEWPORT m_viewport;

	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_worldMatrix;


	//수직동기화 체크, true - 활성화, false - 비활성화
	bool m_vsyncEnabled = false;


public:

	Graphic();
	~Graphic();

	//초기화
	void Init(HWND hwnd);

	//그리기 시작
	void Begin();
	//그리기 끝
	void End();

	void SetBackBufferRenderTarget();

	//수직동기화 세팅
	void SetVsync(bool value) { m_vsyncEnabled = value; };

	//device와 dc가져오기
	ID3D11Device* GetDevice() { return m_device; }
	ID3D11DeviceContext* GetDC() { return m_dc; }

	void SetProjection(D3DXMATRIX value) { m_projectionMatrix = value; };
	D3DXMATRIX GetProjection() { return m_projectionMatrix; };

};

