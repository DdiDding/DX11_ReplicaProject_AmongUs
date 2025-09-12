#pragma once
#include "../../stdafx.h"

class BufferResource
{
public:

	BufferResource();
	~BufferResource();

	/*********************************************************************************
	함수 : CreateVertexBuffer
	목적 : VertexBuffer 생성
	매개변수
		1.bufferName - 이 포인터에 VertexBuffer을 생성한다
		2.data - VertexBuffer의 subResource(구조체형식)
		3.isDynaMic - Buffer을 동적으로 만들것인지 옵션	
	*********************************************************************************/
	template <class T>
	void CreateVertexBuffer(ID3D11Buffer ** bufferName, T data, bool isDynamic) {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 : VertexBuffer 생성
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. stride, offset 세팅
		stride = sizeof(data.GetData()->front()); //stride - 정점하나의 데이터 크기 , 처음 원소의 크기로 세팅
		offset = 0; //정점과 정점의 메모리간격


		//1.vertexBufferDesc 생성
		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

		if (isDynamic == true) {

			vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			vertexBufferDesc.ByteWidth = sizeof(data.GetData()->front()) * data.GetData()->size(); //★★★★
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			vertexBufferDesc.MiscFlags = 0;
			vertexBufferDesc.StructureByteStride = 0;
		}
		else {

			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth = sizeof(data.GetData()->front()) * data.GetData()->size(); //★★★★
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertexBufferDesc.CPUAccessFlags = 0;
			vertexBufferDesc.MiscFlags = 0;
			vertexBufferDesc.StructureByteStride = 0;
		}

		//2.서브리소스 생성 ( 서브리소스는 리소스안에 실제 데이터라 생각하면 된당 ) 
		D3D11_SUBRESOURCE_DATA vertexSubResource;
		ZeroMemory(&vertexSubResource, sizeof(D3D11_SUBRESOURCE_DATA));
		vertexSubResource.pSysMem = data.GetData()->data();
		vertexSubResource.SysMemPitch = 0;
		vertexSubResource.SysMemSlicePitch = 0;

		//3.버퍼 생성
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
	함수 : UpdateBuffer
	목적 : 동적 Buffer 리소스를 Map, Unmap으로 업데이트 한다
	매개변수
		1.bufferName - 이 포인터가 가르키는 Buffer리소스의 Sub리소스를 변경한다
		2.data - 넣고싶은 subResource 데이터 ( 이 데이터로 업데이트 됨 )
	*********************************************************************************/
	template <typename T>
	void UpdateBuffer(ID3D11Buffer * bufferName, T * structName, int structSize) {

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
		memcpy(subResource.pData, structName, structSize); //★★★★★ 


		//3.3 Unmap으로 다시 해당 리소스의 GPU 접근을 풀어준다
		GETDC->Unmap(bufferName, 0);

		return;
	};


	void Draw();

private:

	//정점을 이을 순서를 저장할 벡터
	vector<UINT> m_indices;


	//Draw에 사용 될 정점이 이어질 순서 개수
	UINT m_indexCnt = 0;


	//정점하나의 데이터 크기
	unsigned int stride;
	//정점과 정점의 메모리간격
	unsigned int offset;
};


