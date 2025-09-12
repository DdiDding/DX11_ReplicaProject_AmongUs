
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
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;
	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, 1, 1, 0, 0, 0);
	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));
	
}

void DebugPlayer::Render(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, float guideSize)
{
	//����������� ���̵� ���� ( �غ����� ���
	D3DXVECTOR3 guideDown_left = {playerTrans};
	D3DXVECTOR3 guideDown_right = { playerTrans.x + playerSize.x, playerTrans.y , 0};

	//IA stage
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//IA�� inputLayout����, ���̴����ܰ迡 ����
	mShader->Render();

	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer, 0);


	///////////////////////////////////////////////////////////////////////////////////////
	//���ؽ����� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//�÷��̾� �浹 ����******************************************

	 
	//1.���� �� ����ü ������ ����
	mVertexData.GetData()->at(0).position = guideDown_left;
	mVertexData.GetData()->at(1).position = { guideDown_left.x, guideDown_left.y - guideSize, 0 };

	//2.���ؽ����� ������Ʈ (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());

	//3. ����
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);

	//Draw
	mBufferInterface.Draw();
}
