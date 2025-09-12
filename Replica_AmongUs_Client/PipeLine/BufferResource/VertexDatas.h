#pragma once
#include "../../stdafx.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GetData는 공통으로 생성하기 , 템플릿 이용 때문
// 클래스마다 가지고 있는 것-
//	1. VertexBuffer에 들어갈 VertexData(구조체)의 배열 정보 -- GetData() 로 포인터형 반환
//	2. InputLayOut의 DESC ( VertexData의 구조를 알아야해서 여기서 정의 ) -- GetDesc() 로 포인터형 반환
//	3. InputLayOut의 원소 개수 [ CreateInputLayout 에 사용 ] -- GetDescSize() 로 UINT형 반환
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class VertexDatas_color
{
private:
	struct ColorData {

		D3DXVECTOR3 position;
		D3DXVECTOR4  color;
	};

	//Draw에 사용 될 정점이 이어질 순서 개수
	UINT m_vertexCnt = 0;

	//정점 데이터를 저장할 벡터
	vector<ColorData> m_vertices;

	//VertexData(여기서는 ColorData) 를 토대로한 InputLayoutDesc 데이터 변수
	D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[2];

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 생성자에서 정보 초기화
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexDatas_color() {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 :정점에 관한 데이터 세팅
		//		IA단계에 들어갈 VertexBuffer와 IndexBuffer을 세팅한다
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. 몇개의 정점을 만들지 정의
		m_vertexCnt = 4;


		//1.정점데이터 사이즈를 마리 할당해 놓는다
		m_vertices.assign(m_vertexCnt, ColorData());


		//2.각 index에 정점데이터 입력
		//좌측하단
		m_vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		m_vertices[0].color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
		//좌측상단
		m_vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		m_vertices[1].color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
		//우측상단
		m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		m_vertices[2].color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
		//우측하단
		m_vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		m_vertices[3].color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 :InputLayout에 들어갈 Desc 정의
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. 각 VertexData의 정보를 셰이더에서 어떻게 해석할지 방법을 정의
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		//D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[2];
	//inputLayoutDESC[0].SemanticName = "POSITION";
	//inputLayoutDESC[0].SemanticIndex = 0;
	//inputLayoutDESC[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	//inputLayoutDESC[0].InputSlot = 0; //슬롯 번호
	//inputLayoutDESC[0].AlignedByteOffset = 0;
	//inputLayoutDESC[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//inputLayoutDESC[0].InstanceDataStepRate = 0;
	//inputLayoutDESC[1].SemanticName = "COLOR";
	//inputLayoutDESC[1].SemanticIndex = 0;
	//inputLayoutDESC[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//inputLayoutDESC[1].InputSlot = 0;
	//inputLayoutDESC[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	//inputLayoutDESC[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//inputLayoutDESC[1].InstanceDataStepRate = 0;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 정점 데이터 벡터의 포인터를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<ColorData> * GetData() { return &m_vertices; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC를 포인터형으로 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC의 size를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UINT GetDescSize() { return ARRAYSIZE(inputLayoutDESC); };
};

class VertexDatas_line
{
private:
	struct ColorData {

		D3DXVECTOR3 position;
		D3DXVECTOR4  color;
	};

	//Draw에 사용 될 정점이 이어질 순서 개수
	UINT m_vertexCnt = 0;

	//정점 데이터를 저장할 벡터
	vector<ColorData> m_vertices;

	//VertexData(여기서는 ColorData) 를 토대로한 InputLayoutDesc 데이터 변수
	D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[2];

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 생성자에서 정보 초기화
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexDatas_line() {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 :정점에 관한 데이터 세팅
		//		IA단계에 들어갈 VertexBuffer와 IndexBuffer을 세팅한다
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. 몇개의 정점을 만들지 정의
		m_vertexCnt = 2;


		//1.정점데이터 사이즈를 마리 할당해 놓는다
		m_vertices.assign(m_vertexCnt, ColorData());


		//2.각 index에 정점데이터 입력
		//첫번째 점
		m_vertices[0].position = D3DXVECTOR3(0, 0, 0.0f);
		m_vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		//두번째 점
		m_vertices[1].position = D3DXVECTOR3(1280, 0, 0.0f);
		m_vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, .0f, 1.0f);



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 :InputLayout에 들어갈 Desc 정의
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. 각 VertexData의 정보를 셰이더에서 어떻게 해석할지 방법을 정의
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 정점 데이터 벡터의 포인터를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<ColorData> * GetData() { return &m_vertices; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC를 포인터형으로 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC의 size를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UINT GetDescSize() { return ARRAYSIZE(inputLayoutDESC); };
};

class VertexDatas_tileColor
{
private:
	struct ColorData {

		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;
		int result;
	};

	//Draw에 사용 될 정점이 이어질 순서 개수
	UINT m_vertexCnt = 0;

	//정점 데이터를 저장할 벡터
	vector<ColorData> m_vertices;

	//VertexData(여기서는 ColorData) 를 토대로한 InputLayoutDesc 데이터 변수
	D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[3];

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 생성자에서 정보 초기화
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexDatas_tileColor() {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 :정점에 관한 데이터 세팅
		//		IA단계에 들어갈 VertexBuffer와 IndexBuffer을 세팅한다
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. 몇개의 정점을 만들지 정의
		m_vertexCnt = 4;


		//1.정점데이터 사이즈를 마리 할당해 놓는다
		m_vertices.assign(m_vertexCnt, ColorData());


		//2.각 index에 정점데이터 입력
		//좌측하단
		m_vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		m_vertices[0].uv = D3DXVECTOR2(0, 1);
		//좌측상단
		m_vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		m_vertices[1].uv = D3DXVECTOR2(0, 0);
		//우측상단
		m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		m_vertices[2].uv = D3DXVECTOR2(1, 0);
		//우측하단
		m_vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		m_vertices[3].uv = D3DXVECTOR2(1, 1);



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 :InputLayout에 들어갈 Desc 정의
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. 각 VertexData의 정보를 셰이더에서 어떻게 해석할지 방법을 정의
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[2] = { "TEXCOORD", 1, DXGI_FORMAT_R32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 정점 데이터 벡터의 포인터를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<ColorData> * GetData() { return &m_vertices; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC를 포인터형으로 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC의 size를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UINT GetDescSize() { return ARRAYSIZE(inputLayoutDESC); };
};

class VertexDatas_texture {

public:

	struct TextureData {

		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;
	};


	//생성자
	VertexDatas_texture() {



		//0. 몇개의 정점을 만들지 정의
		m_vertexCnt = 4;


		//1.정점데이터 사이즈를 마리 할당해 놓는다
		m_vertices.assign(m_vertexCnt, TextureData());


		////2.각 index에 정점데이터 입력
		////좌측하단
		//m_vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		//m_vertices[0].uv= D3DXVECTOR2(0, 1);

		////좌측상단
		//m_vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		//m_vertices[1].uv = D3DXVECTOR2(0, 0);

		////우측상단
		//m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		//m_vertices[2].uv = D3DXVECTOR2(1, 0);

		////우측하단
		//m_vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		//m_vertices[3].uv = D3DXVECTOR2(1, 1);

		//---------------------------------------------------------------------------------------------------------
		//좌측하단
		m_vertices[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertices[0].uv = D3DXVECTOR2(0, 1);

		//좌측상단
		m_vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_vertices[1].uv = D3DXVECTOR2(0, 0);

		//우측상단
		m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		m_vertices[2].uv = D3DXVECTOR2(1, 0);

		//우측하단
		m_vertices[3].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_vertices[3].uv = D3DXVECTOR2(1, 1);


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 :InputLayout에 들어갈 Desc 정의
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. 각 VertexData의 정보를 셰이더에서 어떻게 해석할지 방법을 정의
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };

	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 정점 데이터 벡터의 포인터를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<TextureData > * GetData() { return &m_vertices; };


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC를 포인터형으로 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC의 size를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UINT GetDescSize() { return ARRAYSIZE(inputLayoutDESC); };


private:


	//Draw에 사용 될 정점이 이어질 순서 개수
	UINT m_vertexCnt = 0;

	//정점 데이터를 저장할 벡터
	vector<TextureData> m_vertices;


	//VertexData(여기서는 ColorData) 를 토대로한 InputLayoutDesc 데이터 변수
	D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[2];
};

class VertexData_Tile {

private:
	struct ColorData {

		D3DXVECTOR3 position;
		D3DXVECTOR4  color;
		D3DXVECTOR2 uv;
		int test;
	};

	//Draw에 사용 될 정점이 이어질 순서 개수
	UINT m_vertexCnt = 0;

	//정점 데이터를 저장할 벡터
	vector<ColorData> m_vertices;

	//VertexData(여기서는 ColorData) 를 토대로한 InputLayoutDesc 데이터 변수
	D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[4];

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 생성자에서 정보 초기화
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexData_Tile() {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 :정점에 관한 데이터 세팅
		//		IA단계에 들어갈 VertexBuffer와 IndexBuffer을 세팅한다
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. 몇개의 정점을 만들지 정의
		m_vertexCnt = 4;


		//1.정점데이터 사이즈를 마리 할당해 놓는다
		m_vertices.assign(m_vertexCnt, ColorData());


		//2.각 index에 정점데이터 입력
		//좌측하단
		m_vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		m_vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		m_vertices[0].uv = D3DXVECTOR2(0, 1);

		//좌측상단
		m_vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		m_vertices[1].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		m_vertices[1].uv = D3DXVECTOR2(0, 0);

		//우측상단
		m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		m_vertices[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		m_vertices[2].uv = D3DXVECTOR2(1, 0);
		//우측하단
		m_vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		m_vertices[3].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		m_vertices[3].uv = D3DXVECTOR2(1, 1);

		m_vertices[0].test = -5;
		m_vertices[1].test = -5;
		m_vertices[2].test = -5;
		m_vertices[3].test = -5;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//목적 :InputLayout에 들어갈 Desc 정의
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. 각 VertexData의 정보를 셰이더에서 어떻게 해석할지 방법을 정의
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[2] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[3] = { "TEXCOORD", 1, DXGI_FORMAT_R32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : 정점 데이터 벡터의 포인터를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<ColorData> * GetData() { return &m_vertices; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC를 포인터형으로 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//목적 : InputLayoutDESC의 size를 반환
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual UINT GetDescSize() { return ARRAYSIZE(inputLayoutDESC); };
};

