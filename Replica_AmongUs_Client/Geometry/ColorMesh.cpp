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
	�Լ� : ColorMesh / [ ������]
	���� : ���� �����ڿ� �ٸ����� SRV�� ���⼭ �������� �ʴ´�
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
	�Լ� : Update
	���� : ColorMesh�� ���� �������� ����
*********************************************************************************/
void ColorMesh::Update()
{

	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation);

	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));

}

/*********************************************************************************
	�Լ� : Update_ps_float
	���� : int�� �ڷḦ PixelShader�� ������۷� �ѱ��
*********************************************************************************/
void ColorMesh::Update_ps_float(float value)
{

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_float cBufferSubResource2;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	cBufferSubResource2.plusData = value;

	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_ps, &cBufferSubResource2, sizeof(cBufferSubResource2));
}



/*********************************************************************************
	�Լ� : Update_withCam
	���� : ������ǥ�� ī�޶� ��ǥ�� �ٿ��� ��ǥ�� ������Ʈ�Ѵ�
*********************************************************************************/
void ColorMesh::Update_withCam()
{
	D3DXVECTOR3 tempCamPos = GETCAMERA->GetCameraPos();
	tempCamPos.x -= WinMaxWidthHalf;
	tempCamPos.y -= WinMaxHeightHalf;

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, tempCamPos.x + mTransX, tempCamPos.y + mTransY, mRotation);

	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));
}



/*********************************************************************************
	�Լ� : Render
	���� : �� ���ҽ��� ���������ο� �����Ѵ�
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

	//IA�� inputLayout����, ���̴����ܰ迡 ����
	mShader->Render();

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
void ColorMesh::init()
{
	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer ����
	mBufferInterface.CreateIndexBuffer_rect(&mIndexBuffer); // IndexBuffer ����
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_vs, sizeof(ConstantStruct_matrix::constantStruct_matrix));
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_ps, sizeof(ConstantStruct_matrix::constantStruct_int));


	mShader = new Shader(mVertexData, mHlslName); //Shader, ������� ����

}

