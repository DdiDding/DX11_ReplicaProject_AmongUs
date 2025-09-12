#include "../../stdafx.h"
#include "../Mesh.h"
#include "Mesh_player.h"

Mesh_player::Mesh_player(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR * imageRoute)
	:Mesh(sizeX, sizeY, transX, transY, hlslName, imageRoute)
{
	SAFE_RELEASE(mConstantBuffer_vs);
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_vs, sizeof(ConstantStruct_player::constantStruct_player));
}

Mesh_player::~Mesh_player()
{
}

void Mesh_player::Update()
{
	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation, mColor_body, mColor_body_shadow);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));
}

void Mesh_player::Update_withCam()
{
	D3DXVECTOR3 tempCamPos = GETCAMERA->GetCameraPos();
	tempCamPos.x -= WinMaxWidthHalf;
	tempCamPos.y -= WinMaxHeightHalf;

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mSizeX, mSizeY, tempCamPos.x + mTransX, tempCamPos.y + mTransY, mRotation, mColor_body, mColor_body_shadow);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));
}

void Mesh_player::SaveMyColor(D3DXVECTOR4 body, D3DXVECTOR4 shadow)
{
	mColor_body = body;
	mColor_body_shadow = shadow;

	return;
}



void Mesh_player::init()
{
}
