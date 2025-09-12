#include "Ui_inGameRect.h"

Ui_inGameRect::Ui_inGameRect(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute)
	: Mesh(sizeX, sizeY, transX, transY, hlslName, imageRoute)
{

}

Ui_inGameRect::~Ui_inGameRect()
{
}

void Ui_inGameRect::Update(int isAlpha)
{
	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation);
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));

	ConstantStruct_matrix::constantStruct_int cBufferSubResource2;
	cBufferSubResource2.plusData = isAlpha;
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation);
	mBufferInterface.UpdateBuffer(mConstantBuffer_ps, &cBufferSubResource2, sizeof(cBufferSubResource2));
}

void Ui_inGameRect::Render()
{
	//IA stage
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer_vs, 0);
	mBufferInterface.SetConstantBuffer_ps(&mConstantBuffer_ps, 1);


	//PS stage
	GETDC->PSSetShaderResources(0, 1, &mSrv);
	GETDC->PSSetSamplers(0, 1, &mSamplerState);

	//IA에 inputLayout연결, 셰이더각단계에 연결
	mShader->Render();

	//OM stage
	GETDC->OMSetBlendState(mBlendState, nullptr, 0xffffffff);


	//Draw
	mBufferInterface.Draw();
}

bool Ui_inGameRect::IsClick(D3DXVECTOR3 mousePos)
{
	RECT tempRect = { (int)mOriginTrans.x, (int)mOriginTrans.y + (int)mSizeY, (int)mOriginTrans.x + (int)mSizeX, (int)mOriginTrans.y };
	return Collision::Get()->PointAndRect(mousePos, tempRect);
}
