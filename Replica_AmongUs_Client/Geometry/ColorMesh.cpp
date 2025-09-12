#include "../stdafx.h"
#include "../PipeLine/BufferResource/BufferResource.h"
#include "../PipeLine/Shader/Shader.h"
#include "../PipeLine/BufferResource/VertexDatas.h"
#include "../PipeLine/BufferResource/ConstantStruct.h"
#include "ColorMesh.h"


///////////////////////////////////////////////////////////////////////////////////////
//Public function
///////////////////////////////////////////////////////////////////////////////////////



/*********************************************************************************
	함수 : ColorMesh / [ 생성자]
	목적 : 위의 생성자와 다른점은 SRV를 여기서 연결하지 않는다
*********************************************************************************/
ColorMesh::ColorMesh(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName)
{
	mSizeX = sizeX;
	mSizeY = sizeY;

	mTransX = transX;
	mTransY = transY;

	mHlslName = hlslName;

	init();
}


ColorMesh::~ColorMesh()
{
	SAFE_DELETE(mShader);
}


/*********************************************************************************
	함수 : Update
	목적 : ColorMesh에 관한 변수들을 변경
*********************************************************************************/
void ColorMesh::Update()
{

	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));

}

/*********************************************************************************
	함수 : Update_ps_float
	목적 : int형 자료를 PixelShader에 상수버퍼로 넘긴다
*********************************************************************************/
void ColorMesh::Update_ps_float(float value)
{

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_float cBufferSubResource2;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	cBufferSubResource2.plusData = value;

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_ps, &cBufferSubResource2, sizeof(cBufferSubResource2));
}



/*********************************************************************************
	함수 : Update_withCam
	목적 : 월드좌표를 카메라 좌표에 붙여서 좌표를 업데이트한다
*********************************************************************************/
void ColorMesh::Update_withCam()
{
	D3DXVECTOR3 tempCamPos = GETCAMERA->GetCameraPos();
	tempCamPos.x -= WinMaxWidthHalf;
	tempCamPos.y -= WinMaxHeightHalf;

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, tempCamPos.x + mTransX, tempCamPos.y + mTransY, mRotation);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));
}



/*********************************************************************************
	함수 : Render
	목적 : 각 리소스를 파이프라인에 연결한다
*********************************************************************************/
void ColorMesh::Render()
{
	//IA stage
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer_vs, 0);

	//PS stage
	mBufferInterface.SetConstantBuffer_ps(&mConstantBuffer_ps, 1);

	//IA에 inputLayout연결, 셰이더각단계에 연결
	mShader->Render();

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
void ColorMesh::init()
{
	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer 생성
	mBufferInterface.CreateIndexBuffer_rect(&mIndexBuffer); // IndexBuffer 생성
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_vs, sizeof(ConstantStruct_matrix::constantStruct_matrix));
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_ps, sizeof(ConstantStruct_matrix::constantStruct_int));


	mShader = new Shader(mVertexData, mHlslName); //Shader, 상수버퍼 생성

}

