#include "BufferResource.h"

BufferResource::BufferResource() {

}


BufferResource::~BufferResource()
{
	vector<UINT>().swap(m_indices);
}


/*********************************************************************************
	�Լ� : SetVertexBuffer
	���� : VertexBuffer IA�ܰ迡 ����
	�Ű�����
		1.bufferName - �� �����͸� ������� IA�ܰ迡 Vertexbuffer�� �����Ѵ�
*********************************************************************************/
void BufferResource::SetVertexBuffer(ID3D11Buffer ** bufferName)
{
	GETDC->IASetVertexBuffers(0, 1, bufferName, &stride, &offset);
}


/*********************************************************************************
�Լ� : CreateIndexBuffer_rect
���� : IndexBuffer�� �簢�� ������� �����Ѵ�
�Ű�����
	1.bufferName - �� �����Ϳ� IndexBuffer�� �����Ѵ�
*********************************************************************************/
void BufferResource::CreateIndexBuffer_rect(ID3D11Buffer ** bufferName)
{
	//0. ������ �մ� ���� ���� / m_indexCnt�� Draw���� ���ȴ�
	m_indices = { 0,1,2,	0,2,3 };
	m_indexCnt = m_indices.size();

	//1.DESC ����
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = sizeof(UINT) * m_indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;


	//2.���긮�ҽ� ����
	D3D11_SUBRESOURCE_DATA indexSubResource;
	indexSubResource.pSysMem = m_indices.data();
	indexSubResource.SysMemPitch = 0;
	indexSubResource.SysMemSlicePitch = 0;


	//3.����̽����� ����
	HRESULT hr = GETDEVICE->CreateBuffer(&indexBufferDesc, &indexSubResource, bufferName);
	assert(SUCCEEDED(hr));
}

void BufferResource::CreateIndexBuffer_line(ID3D11Buffer ** bufferName)
{
	//0. ������ �մ� ���� ���� / m_indexCnt�� Draw���� ���ȴ�
	m_indices = { 0, 1 };
	m_indexCnt = m_indices.size();

	//1.DESC ����
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = sizeof(UINT) * m_indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;


	//2.���긮�ҽ� ����
	D3D11_SUBRESOURCE_DATA indexSubResource;
	indexSubResource.pSysMem = m_indices.data();
	indexSubResource.SysMemPitch = 0;
	indexSubResource.SysMemSlicePitch = 0;


	//3.����̽����� ����
	HRESULT hr = GETDEVICE->CreateBuffer(&indexBufferDesc, &indexSubResource, bufferName);
	assert(SUCCEEDED(hr));
}


/*********************************************************************************
	�Լ� : SetIndexBuffer_rect
	���� : IndexBuffer�� IA�ܰ迡 �����Ѵ�
	�Ű�����
		1.bufferName - �� �������� ������� IA�ܰ迡 IndexBuffer�� �����Ѵ�
*********************************************************************************/
void BufferResource::SetIndexBuffer_rect(ID3D11Buffer * bufferName)
{
	//IndexBuffer IA�ܰ迡 ����
	GETDC->IASetIndexBuffer(bufferName, DXGI_FORMAT_R32_UINT, 0);
}


/*********************************************************************************
	�Լ� : CreateConstantBuffer
	���� : ConstantBuffer�� �����Ѵ�
	�Ű�����
		1.bufferName - �� �������� ������� IA�ܰ迡 IndexBuffer�� �����Ѵ�
		2.structSize - Sub���ҽ��� ũ��
*********************************************************************************/
void BufferResource::CreateConstantBuffer(ID3D11Buffer ** bufferName, int structSize)
{

	//1. ����Desc ����
	D3D11_BUFFER_DESC cBufferDesc;
	ZeroMemory(&cBufferDesc, sizeof(D3D11_BUFFER_DESC));

	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC; //�������� ����Ѵٰ� ����
	cBufferDesc.ByteWidth = structSize;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.StructureByteStride = 0;

	//2. ����DESC�� ���� constant buffer�� �����Ѵ� !
	HRESULT hr = GETDEVICE->CreateBuffer(&cBufferDesc, nullptr, bufferName);
	ASSERT(hr);
}


/*********************************************************************************
	�Լ� : SetConstantBuffer_ps
	���� : ConstantBuffer�� Ps�ܰ迡 �����Ѵ�
	�Ű�����
		1.bufferName - �� �����Ͱ� ����Ű�� ConstantBuffer�� �����Ѵ�
		2.slotNum - ������ ���� ��ȣ ( register : ?<--- �� ��ȣ)
*********************************************************************************/
void BufferResource::SetConstantBuffer_ps(ID3D11Buffer ** bufferName, UINT slotNum)
{
	GETDC->PSSetConstantBuffers(slotNum, 1, bufferName);

}


/*********************************************************************************
	�Լ� : SetConstantBuffer_vs
	���� : ConstantBuffer�� Vs�ܰ迡 �����Ѵ�
	�Ű�����
		1.bufferName - �� �����Ͱ� ����Ű�� ConstantBuffer�� �����Ѵ�
		2.slotNum - ������ ���� ��ȣ ( register : ?<--- �� ��ȣ)
*********************************************************************************/
void BufferResource::SetConstantBuffer_vs(ID3D11Buffer ** bufferName, UINT slotNum)
{
	GETDC->VSSetConstantBuffers(slotNum, 1, bufferName);
}


/*********************************************************************************
	�Լ� : Draw
	���� : �� Ŭ������ �ִ� m_indexCnt�� �Ű������� ����� DrawIndexed�� ȣ���Ѵ�
*********************************************************************************/
void BufferResource::Draw()
{
	GETDC->DrawIndexed(m_indexCnt, 0, 0);
}
