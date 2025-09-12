#include "../stdafx.h"
#include "Line.h"

///////////////////////////////////////////////////////////////////////////////////////
//Public function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	�Լ� : Line / [ ������ ]
	���� : �Ű������� �޾� �����ϰ� init�� �����Ѵ�
	�Ű�����
		1~4.World��Ŀ� ���� Scale, translation ���
*********************************************************************************/
Line::Line()
{
	init();
}


Line::~Line()
{
	SAFE_DELETE(mShader);
}


/*********************************************************************************
	�Լ� : Update
	���� : Line�� ���� �������� ����
*********************************************************************************/
void Line::Update()
{
	
	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;
	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, 1, 1, 0, 0, 0);
	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));

	///////////////////////////////////////////////////////////////////////////////////////
	//���ؽ����� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.���� �� ����ü ������ ����
	{
		/*mVertexData.GetData()->at(0).position = MapManager::Get()->GetTest().at(i);
		mVertexData.GetData()->at(1).position = MapManager::Get()->GetTest().at(i + 1);*/
	}

	//2.���ؽ����� ������Ʈ (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());

}


/*********************************************************************************
	�Լ� : Render
	���� : �� ���ҽ��� ���������ο� �����Ѵ�
*********************************************************************************/
void Line::Render()
{
	//IA stage
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//IA�� inputLayout����, ���̴����ܰ迡 ����
	mShader->Render();

	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer, 0);

	//Draw
	mBufferInterface.Draw();

}


///////////////////////////////////////////////////////////////////////////////////////
//Private function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	�Լ� : Init
	���� : �ʱ�ȭ, �� Buffer���ҽ��� State�� �����Ѵ�
*********************************************************************************/
void Line::init()
{
	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer ����
	mBufferInterface.CreateIndexBuffer_line(&mIndexBuffer); // IndexBuffer ����
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer, sizeof(ConstantStruct_matrix::constantStruct_matrix));


	mShader = new Shader(mVertexData, mHlslName); //Shader, ������� ����
}