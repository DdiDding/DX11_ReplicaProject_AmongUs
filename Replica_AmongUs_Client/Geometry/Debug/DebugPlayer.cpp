
#include "DebugPlayer.h"

DebugPlayer::DebugPlayer()
{
}

DebugPlayer::~DebugPlayer()
{
}

void DebugPlayer::Update()
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
	
}

void DebugPlayer::Render(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, float guideSize)
{
	//상단판정위한 가이드 라인 ( 밑변기준 사용
	D3DXVECTOR3 guideDown_left = {playerTrans};
	D3DXVECTOR3 guideDown_right = { playerTrans.x + playerSize.x, playerTrans.y , 0};

	//IA stage
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//IA에 inputLayout연결, 셰이더각단계에 연결
	mShader->Render();

	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer, 0);


	///////////////////////////////////////////////////////////////////////////////////////
	//버텍스버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//플레이어 충돌 라인******************************************

	 
	//1.변경 할 구조체 데이터 변경
	mVertexData.GetData()->at(0).position = guideDown_left;
	mVertexData.GetData()->at(1).position = { guideDown_left.x, guideDown_left.y - guideSize, 0 };

	//2.버텍스버퍼 업데이트 (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());

	//3. 세팅
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);

	//Draw
	mBufferInterface.Draw();
}
