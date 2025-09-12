#pragma once
#include "../../stdafx.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GetData�� �������� �����ϱ� , ���ø� �̿� ����
// Ŭ�������� ������ �ִ� ��-
//	1. VertexBuffer�� �� VertexData(����ü)�� �迭 ���� -- GetData() �� �������� ��ȯ
//	2. InputLayOut�� DESC ( VertexData�� ������ �˾ƾ��ؼ� ���⼭ ���� ) -- GetDesc() �� �������� ��ȯ
//	3. InputLayOut�� ���� ���� [ CreateInputLayout �� ��� ] -- GetDescSize() �� UINT�� ��ȯ
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class VertexDatas_color
{
private:
	struct ColorData {

		D3DXVECTOR3 position;
		D3DXVECTOR4  color;
	};

	//Draw�� ��� �� ������ �̾��� ���� ����
	UINT m_vertexCnt = 0;

	//���� �����͸� ������ ����
	vector<ColorData> m_vertices;

	//VertexData(���⼭�� ColorData) �� ������ InputLayoutDesc ������ ����
	D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[2];

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : �����ڿ��� ���� �ʱ�ȭ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexDatas_color() {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� :������ ���� ������ ����
		//		IA�ܰ迡 �� VertexBuffer�� IndexBuffer�� �����Ѵ�
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. ��� ������ ������ ����
		m_vertexCnt = 4;


		//1.���������� ����� ���� �Ҵ��� ���´�
		m_vertices.assign(m_vertexCnt, ColorData());


		//2.�� index�� ���������� �Է�
		//�����ϴ�
		m_vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		m_vertices[0].color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
		//�������
		m_vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		m_vertices[1].color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
		//�������
		m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		m_vertices[2].color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
		//�����ϴ�
		m_vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		m_vertices[3].color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� :InputLayout�� �� Desc ����
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. �� VertexData�� ������ ���̴����� ��� �ؼ����� ����� ����
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		//D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[2];
	//inputLayoutDESC[0].SemanticName = "POSITION";
	//inputLayoutDESC[0].SemanticIndex = 0;
	//inputLayoutDESC[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	//inputLayoutDESC[0].InputSlot = 0; //���� ��ȣ
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
	//���� : ���� ������ ������ �����͸� ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<ColorData> * GetData() { return &m_vertices; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� ������������ ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� size�� ��ȯ
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

	//Draw�� ��� �� ������ �̾��� ���� ����
	UINT m_vertexCnt = 0;

	//���� �����͸� ������ ����
	vector<ColorData> m_vertices;

	//VertexData(���⼭�� ColorData) �� ������ InputLayoutDesc ������ ����
	D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[2];

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : �����ڿ��� ���� �ʱ�ȭ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexDatas_line() {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� :������ ���� ������ ����
		//		IA�ܰ迡 �� VertexBuffer�� IndexBuffer�� �����Ѵ�
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. ��� ������ ������ ����
		m_vertexCnt = 2;


		//1.���������� ����� ���� �Ҵ��� ���´�
		m_vertices.assign(m_vertexCnt, ColorData());


		//2.�� index�� ���������� �Է�
		//ù��° ��
		m_vertices[0].position = D3DXVECTOR3(0, 0, 0.0f);
		m_vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		//�ι�° ��
		m_vertices[1].position = D3DXVECTOR3(1280, 0, 0.0f);
		m_vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, .0f, 1.0f);



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� :InputLayout�� �� Desc ����
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. �� VertexData�� ������ ���̴����� ��� �ؼ����� ����� ����
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : ���� ������ ������ �����͸� ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<ColorData> * GetData() { return &m_vertices; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� ������������ ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� size�� ��ȯ
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

	//Draw�� ��� �� ������ �̾��� ���� ����
	UINT m_vertexCnt = 0;

	//���� �����͸� ������ ����
	vector<ColorData> m_vertices;

	//VertexData(���⼭�� ColorData) �� ������ InputLayoutDesc ������ ����
	D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[3];

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : �����ڿ��� ���� �ʱ�ȭ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexDatas_tileColor() {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� :������ ���� ������ ����
		//		IA�ܰ迡 �� VertexBuffer�� IndexBuffer�� �����Ѵ�
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. ��� ������ ������ ����
		m_vertexCnt = 4;


		//1.���������� ����� ���� �Ҵ��� ���´�
		m_vertices.assign(m_vertexCnt, ColorData());


		//2.�� index�� ���������� �Է�
		//�����ϴ�
		m_vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		m_vertices[0].uv = D3DXVECTOR2(0, 1);
		//�������
		m_vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		m_vertices[1].uv = D3DXVECTOR2(0, 0);
		//�������
		m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		m_vertices[2].uv = D3DXVECTOR2(1, 0);
		//�����ϴ�
		m_vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		m_vertices[3].uv = D3DXVECTOR2(1, 1);



		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� :InputLayout�� �� Desc ����
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. �� VertexData�� ������ ���̴����� ��� �ؼ����� ����� ����
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[2] = { "TEXCOORD", 1, DXGI_FORMAT_R32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : ���� ������ ������ �����͸� ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<ColorData> * GetData() { return &m_vertices; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� ������������ ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� size�� ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UINT GetDescSize() { return ARRAYSIZE(inputLayoutDESC); };
};

class VertexDatas_texture {

public:

	struct TextureData {

		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;
	};


	//������
	VertexDatas_texture() {



		//0. ��� ������ ������ ����
		m_vertexCnt = 4;


		//1.���������� ����� ���� �Ҵ��� ���´�
		m_vertices.assign(m_vertexCnt, TextureData());


		////2.�� index�� ���������� �Է�
		////�����ϴ�
		//m_vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		//m_vertices[0].uv= D3DXVECTOR2(0, 1);

		////�������
		//m_vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		//m_vertices[1].uv = D3DXVECTOR2(0, 0);

		////�������
		//m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		//m_vertices[2].uv = D3DXVECTOR2(1, 0);

		////�����ϴ�
		//m_vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		//m_vertices[3].uv = D3DXVECTOR2(1, 1);

		//---------------------------------------------------------------------------------------------------------
		//�����ϴ�
		m_vertices[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vertices[0].uv = D3DXVECTOR2(0, 1);

		//�������
		m_vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_vertices[1].uv = D3DXVECTOR2(0, 0);

		//�������
		m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		m_vertices[2].uv = D3DXVECTOR2(1, 0);

		//�����ϴ�
		m_vertices[3].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		m_vertices[3].uv = D3DXVECTOR2(1, 1);


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� :InputLayout�� �� Desc ����
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. �� VertexData�� ������ ���̴����� ��� �ؼ����� ����� ����
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };

	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : ���� ������ ������ �����͸� ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<TextureData > * GetData() { return &m_vertices; };


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� ������������ ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� size�� ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	UINT GetDescSize() { return ARRAYSIZE(inputLayoutDESC); };


private:


	//Draw�� ��� �� ������ �̾��� ���� ����
	UINT m_vertexCnt = 0;

	//���� �����͸� ������ ����
	vector<TextureData> m_vertices;


	//VertexData(���⼭�� ColorData) �� ������ InputLayoutDesc ������ ����
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

	//Draw�� ��� �� ������ �̾��� ���� ����
	UINT m_vertexCnt = 0;

	//���� �����͸� ������ ����
	vector<ColorData> m_vertices;

	//VertexData(���⼭�� ColorData) �� ������ InputLayoutDesc ������ ����
	D3D11_INPUT_ELEMENT_DESC  inputLayoutDESC[4];

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : �����ڿ��� ���� �ʱ�ȭ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	VertexData_Tile() {

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� :������ ���� ������ ����
		//		IA�ܰ迡 �� VertexBuffer�� IndexBuffer�� �����Ѵ�
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//0. ��� ������ ������ ����
		m_vertexCnt = 4;


		//1.���������� ����� ���� �Ҵ��� ���´�
		m_vertices.assign(m_vertexCnt, ColorData());


		//2.�� index�� ���������� �Է�
		//�����ϴ�
		m_vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		m_vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		m_vertices[0].uv = D3DXVECTOR2(0, 1);

		//�������
		m_vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		m_vertices[1].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		m_vertices[1].uv = D3DXVECTOR2(0, 0);

		//�������
		m_vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		m_vertices[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		m_vertices[2].uv = D3DXVECTOR2(1, 0);
		//�����ϴ�
		m_vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		m_vertices[3].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
		m_vertices[3].uv = D3DXVECTOR2(1, 1);

		m_vertices[0].test = -5;
		m_vertices[1].test = -5;
		m_vertices[2].test = -5;
		m_vertices[3].test = -5;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���� :InputLayout�� �� Desc ����
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//1. �� VertexData�� ������ ���̴����� ��� �ؼ����� ����� ����
		inputLayoutDESC[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[2] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
		inputLayoutDESC[3] = { "TEXCOORD", 1, DXGI_FORMAT_R32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : ���� ������ ������ �����͸� ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<ColorData> * GetData() { return &m_vertices; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� ������������ ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual D3D11_INPUT_ELEMENT_DESC * GetDesc() { return this->inputLayoutDESC; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���� : InputLayoutDESC�� size�� ��ȯ
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual UINT GetDescSize() { return ARRAYSIZE(inputLayoutDESC); };
};

