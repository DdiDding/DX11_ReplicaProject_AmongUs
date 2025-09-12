#pragma once
#include "../../stdafx.h"

class BufferResource
{
public:

	BufferResource();
	~BufferResource();

	/*********************************************************************************
	�Լ� : CreateVertexBuffer
	���� : VertexBuffer ����
	�Ű�����
		1.bufferName - �� �����Ϳ� VertexBuffer�� �����Ѵ�
		2.data - VertexBuffer�� subResource(����ü����)
		3.isDynaMic - Buffer�� �������� ��������� �ɼ�	
	*********************************************************************************/
	template <class T>
	void CreateVertexBuffer(ID3D11Buffer ** bufferName, T data, bool isDynamic) {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� : VertexBuffer ����
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. stride, offset ����
		stride = sizeof(data.GetData()->front()); //stride - �����ϳ��� ������ ũ�� , ó�� ������ ũ��� ����
		offset = 0; //������ ������ �޸𸮰���


		//1.vertexBufferDesc ����
		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

		if (isDynamic == true) {

			vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			vertexBufferDesc.ByteWidth = sizeof(data.GetData()->front()) * data.GetData()->size(); //�ڡڡڡ�
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			vertexBufferDesc.MiscFlags = 0;
			vertexBufferDesc.StructureByteStride = 0;
		}
		else {

			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth = sizeof(data.GetData()->front()) * data.GetData()->size(); //�ڡڡڡ�
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = 0;
			vertexBufferDesc.MiscFlags = 0;
			vertexBufferDesc.StructureByteStride = 0;
		}

		//2.���긮�ҽ� ���� ( ���긮�ҽ��� ���ҽ��ȿ� ���� �����Ͷ� �����ϸ� �ȴ� ) 
		D3D11_SUBRESOURCE_DATA vertexSubResource;
		ZeroMemory(&vertexSubResource, sizeof(D3D11_SUBRESOURCE_DATA));
		vertexSubResource.pSysMem = data.GetData()->data();
		vertexSubResource.SysMemPitch = 0;
		vertexSubResource.SysMemSlicePitch = 0;

		//3.���� ����
		HRESULT hrr = GETDEVICE->CreateBuffer(&vertexBufferDesc, &vertexSubResource, bufferName);
		assert(SUCCEEDED(hrr));
	};
	void SetVertexBuffer(ID3D11Buffer ** bufferName);


	void CreateIndexBuffer_rect(ID3D11Buffer ** bufferName);
	void CreateIndexBuffer_line(ID3D11Buffer ** bufferName);

	void SetIndexBuffer_rect(ID3D11Buffer * bufferName);


	void CreateConstantBuffer(ID3D11Buffer ** bufferName, int structSize);
	void SetConstantBuffer_ps(ID3D11Buffer ** bufferName, UINT slotNum);
	void SetConstantBuffer_vs(ID3D11Buffer ** bufferName, UINT slotNum);


	/*********************************************************************************
	�Լ� : UpdateBuffer
	���� : ���� Buffer ���ҽ��� Map, Unmap���� ������Ʈ �Ѵ�
	�Ű�����
		1.bufferName - �� �����Ͱ� ����Ű�� Buffer���ҽ��� Sub���ҽ��� �����Ѵ�
		2.data - �ְ���� subResource ������ ( �� �����ͷ� ������Ʈ �� )
	*********************************************************************************/
	template <typename T>
	void UpdateBuffer(ID3D11Buffer * bufferName, T * structName, int structSize) {

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
		memcpy(subResource.pData, structName, structSize); //�ڡڡڡڡ� 


		//3.3 Unmap���� �ٽ� �ش� ���ҽ��� GPU ������ Ǯ���ش�
		GETDC->Unmap(bufferName, 0);

		return;
	};


	void Draw();

private:

	//������ ���� ������ ������ ����
	vector<UINT> m_indices;


	//Draw�� ��� �� ������ �̾��� ���� ����
	UINT m_indexCnt = 0;


	//�����ϳ��� ������ ũ��
	unsigned int stride;
	//������ ������ �޸𸮰���
	unsigned int offset;
};


