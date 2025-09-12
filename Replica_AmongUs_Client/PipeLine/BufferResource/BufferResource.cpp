#include "BufferResource.h"

BufferResource::BufferResource() {

}


BufferResource::~BufferResource()
{
	vector<UINT>().swap(m_indices);
}


/*********************************************************************************
	함수 : SetVertexBuffer
	목적 : VertexBuffer IA단계에 세팅
	매개변수
		1.bufferName - 이 포인터를 기반으로 IA단계에 Vertexbuffer을 세팅한다
*********************************************************************************/
void BufferResource::SetVertexBuffer(ID3D11Buffer ** bufferName)
{
	GETDC->IASetVertexBuffers(0, 1, bufferName, &stride, &offset);
}


/*********************************************************************************
함수 : CreateIndexBuffer_rect
목적 : IndexBuffer을 사각형 기반으로 생성한다
매개변수
	1.bufferName - 이 포인터에 IndexBuffer을 생성한다
*********************************************************************************/
void BufferResource::CreateIndexBuffer_rect(ID3D11Buffer ** bufferName)
{
	//0. 정점을 잇는 정보 생성 / m_indexCnt는 Draw에서 사용된다
	m_indices = { 0,1,2,	0,2,3 };
	m_indexCnt = m_indices.size();

	//1.DESC 생성
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = sizeof(UINT) * m_indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;


	//2.서브리소스 생성
	D3D11_SUBRESOURCE_DATA indexSubResource;
	indexSubResource.pSysMem = m_indices.data();
	indexSubResource.SysMemPitch = 0;
	indexSubResource.SysMemSlicePitch = 0;


	//3.디바이스에서 생성
	HRESULT hr = GETDEVICE->CreateBuffer(&indexBufferDesc, &indexSubResource, bufferName);
	assert(SUCCEEDED(hr));
}

void BufferResource::CreateIndexBuffer_line(ID3D11Buffer ** bufferName)
{
	//0. 정점을 잇는 정보 생성 / m_indexCnt는 Draw에서 사용된다
	m_indices = { 0, 1 };
	m_indexCnt = m_indices.size();

	//1.DESC 생성
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDesc.ByteWidth = sizeof(UINT) * m_indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;


	//2.서브리소스 생성
	D3D11_SUBRESOURCE_DATA indexSubResource;
	indexSubResource.pSysMem = m_indices.data();
	indexSubResource.SysMemPitch = 0;
	indexSubResource.SysMemSlicePitch = 0;


	//3.디바이스에서 생성
	HRESULT hr = GETDEVICE->CreateBuffer(&indexBufferDesc, &indexSubResource, bufferName);
	assert(SUCCEEDED(hr));
}


/*********************************************************************************
	함수 : SetIndexBuffer_rect
	목적 : IndexBuffer을 IA단계에 세팅한다
	매개변수
		1.bufferName - 이 포인터을 기반으로 IA단계에 IndexBuffer을 세팅한다
*********************************************************************************/
void BufferResource::SetIndexBuffer_rect(ID3D11Buffer * bufferName)
{
	//IndexBuffer IA단계에 연결
	GETDC->IASetIndexBuffer(bufferName, DXGI_FORMAT_R32_UINT, 0);
}


/*********************************************************************************
	함수 : CreateConstantBuffer
	목적 : ConstantBuffer을 생성한다
	매개변수
		1.bufferName - 이 포인터을 기반으로 IA단계에 IndexBuffer을 세팅한다
		2.structSize - Sub리소스의 크기
*********************************************************************************/
void BufferResource::CreateConstantBuffer(ID3D11Buffer ** bufferName, int structSize)
{

	//1. 버퍼Desc 생성
	D3D11_BUFFER_DESC cBufferDesc;
	ZeroMemory(&cBufferDesc, sizeof(D3D11_BUFFER_DESC));

	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC; //동적으로 사용한다고 설정
	cBufferDesc.ByteWidth = structSize;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.StructureByteStride = 0;

	//2. 버퍼DESC를 토대로 constant buffer을 생성한다 !
	HRESULT hr = GETDEVICE->CreateBuffer(&cBufferDesc, nullptr, bufferName);
	ASSERT(hr);
}


/*********************************************************************************
	함수 : SetConstantBuffer_ps
	목적 : ConstantBuffer을 Ps단계에 세팅한다
	매개변수
		1.bufferName - 이 포인터가 가르키는 ConstantBuffer을 연결한다
		2.slotNum - 연결할 슬롯 번호 ( register : ?<--- 이 번호)
*********************************************************************************/
void BufferResource::SetConstantBuffer_ps(ID3D11Buffer ** bufferName, UINT slotNum)
{
	GETDC->PSSetConstantBuffers(slotNum, 1, bufferName);

}


/*********************************************************************************
	함수 : SetConstantBuffer_vs
	목적 : ConstantBuffer을 Vs단계에 세팅한다
	매개변수
		1.bufferName - 이 포인터가 가르키는 ConstantBuffer을 연결한다
		2.slotNum - 연결할 슬롯 번호 ( register : ?<--- 이 번호)
*********************************************************************************/
void BufferResource::SetConstantBuffer_vs(ID3D11Buffer ** bufferName, UINT slotNum)
{
	GETDC->VSSetConstantBuffers(slotNum, 1, bufferName);
}


/*********************************************************************************
	함수 : Draw
	목적 : 이 클래스에 있는 m_indexCnt을 매개변수로 사용해 DrawIndexed을 호출한다
*********************************************************************************/
void BufferResource::Draw()
{
	GETDC->DrawIndexed(m_indexCnt, 0, 0);
}
