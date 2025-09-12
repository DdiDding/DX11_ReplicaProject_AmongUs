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
	//결과 확인용 변수
	HRESULT hr;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 모니터 주사율 구하기
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//1. 그래픽 카드의 정보들을 가져오기 위해 팩토리 생성
	IDXGIFactory * factory = nullptr;
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);


	//2. 그래픽카드의 정보들을 받기위해 어댑터 생성
	IDXGIAdapter * adapter = nullptr;
	//그래픽카드의 목록중에서 0번째의 그래픽카드 정보를 adapter로 가져온다
	factory->EnumAdapters(0, &adapter);
	//콘솔창에 그래픽카드 모두 출력하기
	//for (int i = 0; ;i++) {
	//	if (factory->EnumAdapters(i, &adapter) == DXGI_ERROR_NOT_FOUND) return;
	//	//받아
	//	DXGI_ADAPTER_DESC adapterDesc;
	//	adapter->GetDesc(&adapterDesc);
	//	wstring text;
	//	text += adapterDesc.Description;
	//	wcout << text << endl;
	//}

	//3.그래픽 출력장치(모니터)의 정보를 받기위해 아웃풋 생성
	IDXGIOutput * adapterOutput = nullptr;
	//출력장치의 목록중에서 0번째의 정보를 어댑터를 통해 받아온다
	adapter->EnumOutputs(0, &adapterOutput);


	//4.GetDisplayModeList에서 마지막을 NULL로 주면 디스플레이 모드의 개수를 알려준다, 포멧이 들어간 이유는 매개변수로 쓴 포맷을 지원하는 디스플레이 모드의 개수를 뜻하는거임
	UINT numModes = 0;
	adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);


	//5.얻어온 개수만큼 동적할당, 가져오는 데이터형식은 DXGI_MODE_DESC 이다
	DXGI_MODE_DESC * displayModeList = new DXGI_MODE_DESC[numModes];


	//6.자세한 정보 가져오기
	adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);


	//7.현재 나의 해상도에 맞는 해상도의 fps구하기
	UINT numerator = 0;
	UINT denominator = 0;

	for (UINT i = 0; i < numModes; i++) {

		if (displayModeList[i].Width == WinMaxWidth && displayModeList[i].Height == WinMaxHeight) {

			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}
	

	//8.사용한 포인터 해제
	delete[] displayModeList;
	adapterOutput->Release();
	adapter->Release();
	factory->Release();



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 디바이스, 디바이스 컨텍스트, 스왑체인 생성
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//1.스왑체인 설명서(DESC) 설정
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1; //만들 버퍼 개수


	swapChainDesc.BufferDesc.Width = WinMaxWidth; //만들 버퍼의 가로크기
	swapChainDesc.BufferDesc.Height = WinMaxHeight; //만들 버퍼의 세로크기
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //만들버퍼의 포캣 형식


	if (m_vsyncEnabled == true) {//수직 동기화 On
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else {//수직 동기화 off
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}


	//멀티샘플링 일단 off
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality= 0;


	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //만드는 버퍼의 용도 설정
	swapChainDesc.OutputWindow = handle; // 어떤 창에서 랜더링이 이루어지는가


	swapChainDesc.Windowed = true; //전체화면 off


	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //이미지가 그려지는 순서( 위에서, 아래서...)
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //해상도에맞게 이미지가 비율적으로 맞춰짐

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; //버퍼가 출력되면 내용을 버린다

	swapChainDesc.Flags = 0; //플래그 사용안함

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_1; //사용할 레벨 수준

	//2.디바이스, DC, 스왑체인 한번에 생성, 아마 여기서 백버퍼도 생성되는거 같은데? 리소스는 무조건 Device에서 생성?
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &level, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_swapChain, &m_device, NULL, &m_dc);
	ASSERT(hr);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 랜더타겟뷰 생성하면서 스왑체인의 버퍼 연결, OM단계에 연결 , 렌더타겟뷰도 하나의텍스처 리소스구나!
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//1.백버퍼 주소를 담을 포인터 생성 (백버퍼도 하나의 텍스처 리소스다)
	ID3D11Texture2D * backBuffer;


	//2.위에서 만든 포인터를 스왑체인에 있는 버퍼에 연결한다
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer);
	ASSERT(hr);



	//3.텍스처리소스는 무조건 뷰를 통해 파이프라인에 연결되기에 그림을 그리는 목적이니까 랜더타겟뷰 생성해서
	m_device->CreateRenderTargetView(backBuffer, NULL, &m_rtv);


	//4.포인터 해제
	backBuffer->Release();
	backBuffer = 0;

	//5.랜더타겟뷰 OutputMerger에 연결
	m_dc->OMSetRenderTargets(1, &m_rtv, NULL);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 레스터 라이저 단계 설정
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//래스터라이저 - 픽셀, 픽셀화 한다! 간단히 사용할 픽셀들의 뷰포트에 매핑한다
	//뷰포트는 래스터라이저에서 그려질 영역이라 생각하고 뷰포트에 나오지않는 데이터는 잘라버린다 ( 클리핑 )
	//앞,뒷면 구분해 뒷면은 그리지 않게 설정

	//1.레스터라이저 설정 세팅
	D3D11_RASTERIZER_DESC rasterDesc;

	rasterDesc.FillMode = D3D11_FILL_SOLID; //렌더링 할 때 채우는 모드? ㅋㅋㅋ모임 ㅅㅂ 평범하게 렌더링이라는딩
	rasterDesc.CullMode = D3D11_CULL_BACK; //설정한 방향의 삼각형은 그려지지 않는다 ( 우리가 설정한건 역방향 )
	rasterDesc.FrontCounterClockwise = false; //어떤게 정방향이고 역방향이냐 ( false면 시계방향이 정방향, true면 그 반대)

	rasterDesc.DepthBias = 0; //깊이바이어스관련
	rasterDesc.DepthBiasClamp = 0.0f; //깊이바이어스관련
	rasterDesc.SlopeScaledDepthBias = 0.0f; //깊이바이어스관련
	rasterDesc.DepthClipEnable = false; //깊이클리핑 없음

	rasterDesc.ScissorEnable = false; //시저테스트 활성 여부
	rasterDesc.MultisampleEnable = false; //멀티샘플링 활성 여부
	rasterDesc.AntialiasedLineEnable = false; //라인앤티 앨리어싱 활성화 여부


	//2.레스터라이저 설정을 기반으로 레스터라이저 생성
	m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);


	//3.래스터라이저단계에 세팅
	m_dc->RSSetState(m_rasterState);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 뷰포트 생성 후 레스터라이저에 연결
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//1.뷰포트 설정
	m_viewport.Width = WinMaxWidth;
	m_viewport.Height = WinMaxHeight;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;


	//2. 래스터라이저에 연결
	m_dc->RSSetViewports(1, &m_viewport); //몇개의 뷰포트를 연결할건지


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 프로젝션 뷰행렬 생성
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
