#pragma once
#include "../../stdafx.h"


///////////////////////////////////////////////////////////////////////////////////////
// 목적 :hlsl파일을 컴파일해 셰이더 객체를 생성해 파이프라인에 연결하고,
//		inputLayout을 통해 VertexBuffer의 해석방법을 정의 하고,
//		상수버퍼를 생성해 map, unmap으로 업데이트하는 기능을 담당한다
///////////////////////////////////////////////////////////////////////////////////////


class Shader
{
public:

	//생성자 소멸자
	Shader();
	~Shader();


	template <class T>
	Shader(T data, LPCWSTR shaderName) {

		m_vertexShader = nullptr;
		m_pixelShader = nullptr;
		m_inputLayout = nullptr;

		Init(data, shaderName);
	};



	template <typename T>
	void UpdateCbuffer(ID3D11Buffer * bufferName, T structName)
	{
		///////////////////////////////////////////////////////////////////////////////////////
		//목적 : 상수버퍼의 업데이트
		///////////////////////////////////////////////////////////////////////////////////////


		//3. 서브리소스 생성
		D3D11_MAPPED_SUBRESOURCE subResource;

		//3.1 Map을 이용해 constantBuffer의 서브리소스 포인터를 받아오고 해당 리소스에 대한 GPU 액세스를 막아둔다
		GETDC->Map(
			bufferName, // Map의 타겟인 buffer
			0, //서브리소스 인덱스 번호
			D3D11_MAP_WRITE_DISCARD, // 리소스에 대해 어떻게 접근할것인가, 내가세팅한건 쓰기용으로 매핑되고 이전 내용은 버린다
			0,
			&subResource
		);


		//3.2 subResource.pData가 현재 참조하는 서브리소스의 포인터이다.
		memcpy(subResource.pData, &structName, sizeof(structName)); //★★★★★ 


		//3.3 Unmap으로 다시 해당 리소스의 GPU 접근을 풀어준다
		GETDC->Unmap(bufferName, 0);

		int bufferNumber = 0; // 이 번호가 register (b '?') 의 번호와 매핑된다
		GETDC->VSSetConstantBuffers(bufferNumber, 1, &bufferName);

		return;
	}

	void Render();


private:


	void CompileHLSL(LPCWSTR shaderName) {
		HRESULT hr;

		///////////////////////////////////////////////////////////////////////////////////////
		//목적 : hlsl 파일을 컴파일해서 blob에 저장후, blob을 이용해서 쉐이더객체를 생성한다
		///////////////////////////////////////////////////////////////////////////////////////
		
		//1. 컴파일한 데이터는 blob의 자료형에 저장된다
		hr = D3DX11CompileFromFile(shaderName, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &vsBlob, NULL, NULL);
		ASSERT(hr);

		hr = D3DX11CompileFromFile(shaderName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &psBlob, NULL, NULL);
		ASSERT(hr);

		//2. 데이터를 받아온 blob을 이용해서 쉐이더 객체를 생성
		hr = GETDEVICE->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_vertexShader);
		ASSERT(hr);

		hr = GETDEVICE->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_pixelShader);
		ASSERT(hr);
	};


	template <class T>
	void CreateInputLayout(T data) {

		///////////////////////////////////////////////////////////////////////////////////////
		//목적 : InputLayout을 생성 ( Vertex buffer의 해석방법 )
		///////////////////////////////////////////////////////////////////////////////////////

		//1. inputLayout의 DESC를 매개변수로 받아와(data) 그것을 토대로 InputLayout 생성
		GETDEVICE->CreateInputLayout(data.GetDesc(), data.GetDescSize(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_inputLayout);


		//2.사용 한 셰이더 포인터는 이제 사용할 일 없으니 해제
		vsBlob->Release(); vsBlob = nullptr;
		psBlob->Release(); psBlob = nullptr;
	};


	//초기화 함수
	template <class T>
	void Init(T data, LPCWSTR shaderName)
	{
		///////////////////////////////////////////////////////////////////////////////////////
		//목적 : 1.hlsl파일을 컴파일해 쉐이더 객체를 생성.  2.inputLayout 생성   3.상수버퍼 생성
		///////////////////////////////////////////////////////////////////////////////////////

		//1. HLSL 컴파일
		CompileHLSL(shaderName);


		//2. InputLayout 생성
		CreateInputLayout(data);


		return;
	}


private:

	//컴파일한 셰이더 데이터를 통해 저장할 셰이더 객체
	ID3D11VertexShader * m_vertexShader;
	ID3D11PixelShader * m_pixelShader;


	ID3D11InputLayout * m_inputLayout;


	ID3D10Blob * vsBlob;
	ID3D10Blob * psBlob;

};

