#include "Graphic.h"

Graphic::Graphic()
{
	m_device = nullptr;
	m_dc = nullptr;
	m_swapChain = nullptr;
	m_rtv = nullptr;
	m_rasterState = nullptr;
}

Graphic::~Graphic()
{
	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_dc);
	SAFE_RELEASE(m_rtv);
	SAFE_RELEASE(m_rasterState);
	SAFE_RELEASE(m_device);

	return;
}

void Graphic::Init(HWND handle)
{
	//��� Ȯ�ο� ����
	HRESULT hr;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : ����� �ֻ��� ���ϱ�
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//1. �׷��� ī���� �������� �������� ���� ���丮 ����
	IDXGIFactory * factory = nullptr;
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);


	//2. �׷���ī���� �������� �ޱ����� ����� ����
	IDXGIAdapter * adapter = nullptr;
	//�׷���ī���� ����߿��� 0��°�� �׷���ī�� ������ adapter�� �����´�
	factory->EnumAdapters(0, &adapter);
	//�ܼ�â�� �׷���ī�� ��� ����ϱ�
	//for (int i = 0; ;i++) {
	//	if (factory->EnumAdapters(i, &adapter) == DXGI_ERROR_NOT_FOUND) return;
	//	//�޾�
	//	DXGI_ADAPTER_DESC adapterDesc;
	//	adapter->GetDesc(&adapterDesc);
	//	wstring text;
	//	text += adapterDesc.Description;
	//	wcout << text << endl;
	//}

	//3.�׷��� �����ġ(�����)�� ������ �ޱ����� �ƿ�ǲ ����
	IDXGIOutput * adapterOutput = nullptr;
	//�����ġ�� ����߿��� 0��°�� ������ ����͸� ���� �޾ƿ´�
	adapter->EnumOutputs(0, &adapterOutput);


	//4.GetDisplayModeList���� �������� NULL�� �ָ� ���÷��� ����� ������ �˷��ش�, ������ �� ������ �Ű������� �� ������ �����ϴ� ���÷��� ����� ������ ���ϴ°���
	UINT numModes = 0;
	adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);


	//5.���� ������ŭ �����Ҵ�, �������� ������������ DXGI_MODE_DESC �̴�
	DXGI_MODE_DESC * displayModeList = new DXGI_MODE_DESC[numModes];


	//6.�ڼ��� ���� ��������
	adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);


	//7.���� ���� �ػ󵵿� �´� �ػ��� fps���ϱ�
	UINT numerator = 0;
	UINT denominator = 0;

	for (UINT i = 0; i < numModes; i++) {

		if (displayModeList[i].Width == WinMaxWidth && displayModeList[i].Height == WinMaxHeight) {

			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}
	

	//8.����� ������ ����
	delete[] displayModeList;
	adapterOutput->Release();
	adapter->Release();
	factory->Release();



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : ����̽�, ����̽� ���ؽ�Ʈ, ����ü�� ����
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//1.����ü�� ����(DESC) ����
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1; //���� ���� ����


	swapChainDesc.BufferDesc.Width = WinMaxWidth; //���� ������ ����ũ��
	swapChainDesc.BufferDesc.Height = WinMaxHeight; //���� ������ ����ũ��
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //��������� ��Ĺ ����


	if (m_vsyncEnabled == true) {//���� ����ȭ On
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else {//���� ����ȭ off
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}


	//��Ƽ���ø� �ϴ� off
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality= 0;


	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //����� ������ �뵵 ����
	swapChainDesc.OutputWindow = handle; // � â���� �������� �̷�����°�


	swapChainDesc.Windowed = true; //��üȭ�� off


	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //�̹����� �׷����� ����( ������, �Ʒ���...)
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //�ػ󵵿��°� �̹����� ���������� ������

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //���۰� ��µǸ� ������ ������

	swapChainDesc.Flags = 0; //�÷��� ������

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_1; //����� ���� ����

	//2.����̽�, DC, ����ü�� �ѹ��� ����, �Ƹ� ���⼭ ����۵� �����Ǵ°� ������? ���ҽ��� ������ Device���� ����?
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &level, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_dc);
	ASSERT(hr);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : ����Ÿ�ٺ� �����ϸ鼭 ����ü���� ���� ����, OM�ܰ迡 ���� , ����Ÿ�ٺ䵵 �ϳ����ؽ�ó ���ҽ�����!
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//1.����� �ּҸ� ���� ������ ���� (����۵� �ϳ��� �ؽ�ó ���ҽ���)
	ID3D11Texture2D * backBuffer;


	//2.������ ���� �����͸� ����ü�ο� �ִ� ���ۿ� �����Ѵ�
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer);
	ASSERT(hr);



	//3.�ؽ�ó���ҽ��� ������ �並 ���� ���������ο� ����Ǳ⿡ �׸��� �׸��� �����̴ϱ� ����Ÿ�ٺ� �����ؼ�
	m_device->CreateRenderTargetView(backBuffer, NULL, &m_rtv);


	//4.������ ����
	backBuffer->Release();
	backBuffer = 0;

	//5.����Ÿ�ٺ� OutputMerger�� ����
	m_dc->OMSetRenderTargets(1, &m_rtv, NULL);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : ������ ������ �ܰ� ����
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//�����Ͷ����� - �ȼ�, �ȼ�ȭ �Ѵ�! ������ ����� �ȼ����� ����Ʈ�� �����Ѵ�
	//����Ʈ�� �����Ͷ��������� �׷��� �����̶� �����ϰ� ����Ʈ�� �������ʴ� �����ʹ� �߶������ ( Ŭ���� )
	//��,�޸� ������ �޸��� �׸��� �ʰ� ����

	//1.�����Ͷ����� ���� ����
	D3D11_RASTERIZER_DESC rasterDesc;

	rasterDesc.FillMode = D3D11_FILL_SOLID; //������ �� �� ä��� ���? ���������� ���� ����ϰ� �������̶�µ�
	rasterDesc.CullMode = D3D11_CULL_BACK; //������ ������ �ﰢ���� �׷����� �ʴ´� ( �츮�� �����Ѱ� ������ )
	rasterDesc.FrontCounterClockwise = false; //��� �������̰� �������̳� ( false�� �ð������ ������, true�� �� �ݴ�)

	rasterDesc.DepthBias = 0; //���̹��̾����
	rasterDesc.DepthBiasClamp = 0.0f; //���̹��̾����
	rasterDesc.SlopeScaledDepthBias = 0.0f; //���̹��̾����
	rasterDesc.DepthClipEnable = false; //����Ŭ���� ����

	rasterDesc.ScissorEnable = false; //�����׽�Ʈ Ȱ�� ����
	rasterDesc.MultisampleEnable = false; //��Ƽ���ø� Ȱ�� ����
	rasterDesc.AntialiasedLineEnable = false; //���ξ�Ƽ �ٸ���� Ȱ��ȭ ����


	//2.�����Ͷ����� ������ ������� �����Ͷ����� ����
	m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);


	//3.�����Ͷ������ܰ迡 ����
	m_dc->RSSetState(m_rasterState);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : ����Ʈ ���� �� �����Ͷ������� ����
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//1.����Ʈ ����
	m_viewport.Width = WinMaxWidth;
	m_viewport.Height = WinMaxHeight;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;


	//2. �����Ͷ������� ����
	m_dc->RSSetViewports(1, &m_viewport); //��� ����Ʈ�� �����Ұ���


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : �������� ����� ����
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	D3DXMatrixOrthoOffCenterLH(&m_projectionMatrix, 0, (float)WinMaxWidth, 0, (float)WinMaxHeight, 0, 1);
}

void Graphic::Begin()
{
	m_dc->OMSetRenderTargets(1, &m_rtv, nullptr);
	m_dc->ClearRenderTargetView(m_rtv, D3DXCOLOR(0.0f, 0.0f, 0.0f,1));
	return;
}

void Graphic::End()
{
	m_swapChain->Present(1, 0);
	/*if (m_vsyncEnabled == true) { m_swapChain->Present(1, 0); }
	else				{ m_swapChain->Present(0, 0); }*/
	return;
}

void Graphic::SetBackBufferRenderTarget()
{
	m_dc->OMSetRenderTargets(1, &m_rtv, NULL);
}
