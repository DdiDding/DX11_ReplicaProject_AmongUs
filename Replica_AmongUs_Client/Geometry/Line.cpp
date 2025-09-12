#include "../stdafx.h"
#include "Line.h"

///////////////////////////////////////////////////////////////////////////////////////
//Public function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	함수 : Line / [ 생성자 ]
	목적 : 매개변수를 받아 저장하고 init을 실행한다
	매개변수
		1~4.World행렬에 계산될 Scale, translation 상수
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
	함수 : Update
	목적 : Line에 관한 변수들을 변경
*********************************************************************************/
void Line::Update()
{
	
	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;
	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, 1, 1, 0, 0, 0);
	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));

	///////////////////////////////////////////////////////////////////////////////////////
	//버텍스버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.변경 할 구조체 데이터 변경
	{
		/*mVertexData.GetData()->at(0).position = MapManager::Get()->GetTest().at(i);
		mVertexData.GetData()->at(1).position = MapManager::Get()->GetTest().at(i + 1);*/
	}

	//2.버텍스버퍼 업데이트 (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());

}


/*********************************************************************************
	함수 : Render
	목적 : 각 리소스를 파이프라인에 연결한다
*********************************************************************************/
void Line::Render()
{
	//IA stage
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//IA에 inputLayout연결, 셰이더각단계에 연결
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
	함수 : Init
	목적 : 초기화, 각 Buffer리소스와 State를 생성한다
*********************************************************************************/
void Line::init()
{
	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer 생성
	mBufferInterface.CreateIndexBuffer_line(&mIndexBuffer); // IndexBuffer 생성
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer, sizeof(ConstantStruct_matrix::constantStruct_matrix));


	mShader = new Shader(mVertexData, mHlslName); //Shader, 상수버퍼 생성
}