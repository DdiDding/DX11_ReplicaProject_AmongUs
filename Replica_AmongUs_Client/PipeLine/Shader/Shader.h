#pragma once
#include "../../stdafx.h"


///////////////////////////////////////////////////////////////////////////////////////
// ���� :hlsl������ �������� ���̴� ��ü�� ������ ���������ο� �����ϰ�,
//		inputLayout�� ���� VertexBuffer�� �ؼ������ ���� �ϰ�,
//		������۸� ������ map, unmap���� ������Ʈ�ϴ� ����� ����Ѵ�
///////////////////////////////////////////////////////////////////////////////////////


class Shader
{
public:

	//������ �Ҹ���
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
		//���� : ��������� ������Ʈ
		///////////////////////////////////////////////////////////////////////////////////////


		//3. ���긮�ҽ� ����
		D3D11_MAPPED_SUBRESOURCE subResource;

		//3.1 Map�� �̿��� constantBuffer�� ���긮�ҽ� �����͸� �޾ƿ��� �ش� ���ҽ��� ���� GPU �׼����� ���Ƶд�
		GETDC->Map(
			bufferName, // Map�� Ÿ���� buffer
			0, //���긮�ҽ� �ε��� ��ȣ
			D3D11_MAP_WRITE_DISCARD, // ���ҽ��� ���� ��� �����Ұ��ΰ�, ���������Ѱ� ��������� ���εǰ� ���� ������ ������
			0,
			&subResource
		);


		//3.2 subResource.pData�� ���� �����ϴ� ���긮�ҽ��� �������̴�.
		memcpy(subResource.pData, &structName, sizeof(structName)); //�ڡڡڡڡ� 


		//3.3 Unmap���� �ٽ� �ش� ���ҽ��� GPU ������ Ǯ���ش�
		GETDC->Unmap(bufferName, 0);

		int bufferNumber = 0; // �� ��ȣ�� register (b '?') �� ��ȣ�� ���εȴ�
		GETDC->VSSetConstantBuffers(bufferNumber, 1, &bufferName);

		return;
	}

	void Render();


private:


	void CompileHLSL(LPCWSTR shaderName) {
		HRESULT hr;

		///////////////////////////////////////////////////////////////////////////////////////
		//���� : hlsl ������ �������ؼ� blob�� ������, blob�� �̿��ؼ� ���̴���ü�� �����Ѵ�
		///////////////////////////////////////////////////////////////////////////////////////
		
		//1. �������� �����ʹ� blob�� �ڷ����� ����ȴ�
		hr = D3DX11CompileFromFile(shaderName, NULL, NULL, "VS", "vs_5_0", 0, 0, NULL, &vsBlob, NULL, NULL);
		ASSERT(hr);

		hr = D3DX11CompileFromFile(shaderName, NULL, NULL, "PS", "ps_5_0", 0, 0, NULL, &psBlob, NULL, NULL);
		ASSERT(hr);

		//2. �����͸� �޾ƿ� blob�� �̿��ؼ� ���̴� ��ü�� ����
		hr = GETDEVICE->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_vertexShader);
		ASSERT(hr);

		hr = GETDEVICE->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_pixelShader);
		ASSERT(hr);
	};


	template <class T>
	void CreateInputLayout(T data) {

		///////////////////////////////////////////////////////////////////////////////////////
		//���� : InputLayout�� ���� ( Vertex buffer�� �ؼ���� )
		///////////////////////////////////////////////////////////////////////////////////////

		//1. inputLayout�� DESC�� �Ű������� �޾ƿ�(data) �װ��� ���� InputLayout ����
		GETDEVICE->CreateInputLayout(data.GetDesc(), data.GetDescSize(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_inputLayout);


		//2.��� �� ���̴� �����ʹ� ���� ����� �� ������ ����
		vsBlob->Release(); vsBlob = nullptr;
		psBlob->Release(); psBlob = nullptr;
	};


	//�ʱ�ȭ �Լ�
	template <class T>
	void Init(T data, LPCWSTR shaderName)
	{
		///////////////////////////////////////////////////////////////////////////////////////
		//���� : 1.hlsl������ �������� ���̴� ��ü�� ����.  2.inputLayout ����   3.������� ����
		///////////////////////////////////////////////////////////////////////////////////////

		//1. HLSL ������
		CompileHLSL(shaderName);


		//2. InputLayout ����
		CreateInputLayout(data);


		return;
	}


private:

	//�������� ���̴� �����͸� ���� ������ ���̴� ��ü
	ID3D11VertexShader * m_vertexShader;
	ID3D11PixelShader * m_pixelShader;


	ID3D11InputLayout * m_inputLayout;


	ID3D10Blob * vsBlob;
	ID3D10Blob * psBlob;

};

