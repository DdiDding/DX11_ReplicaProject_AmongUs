#include "../../stdafx.h"

#include "Task.h"

//�����ӰԵ� ���踦 ���������ؼ� ���� Task�� �̰��� �־���Ƚ��ϴ�.
//�׷��� ������ �Ű������� �������� �������� �����ϴ� ������ �ʿ����մϴ�.
Task::Task(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR * imageRoute, int area, int icon, string taskName, bool isYellow)
	:Mesh(sizeX, sizeY, transX, transY, hlslName, imageRoute)
{

	mRect = {(int)mTransX, (int)(mTransY + mSizeX), (int)(mTransX + mSizeX), (int)mTransY};

	mCenterPosX = mTransX + mHalfSizeX;
	mCenterPosY = mTransY + mHalfSizeY;

	mArea = area;

	mIcon = icon;

	mTaskName = taskName;

	mIsYellow = isYellow;

	//�Ͼ��׽�ũ�� �� ������Ʈ�ؾ��ϴϱ� false
	if(mIsYellow == false) mThisBlack = false;
	//������� �÷��̾� ����Ʈ ��� Ȯ���ؾ֤��ϴϱ� �ϴ� true
	else  mThisBlack = true;


	//������� ����
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_ps, sizeof(ConstantStruct_matrix::constantStruct_int));
}

Task::~Task()
{
}

void Task::Update()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	/*VS�� �� �������*************************/
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation);
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));

	/*PS�� �� �������*************************/
	ConstantStruct_matrix::constantStruct_int cBufferSubResource_2;
	cBufferSubResource_2.plusData = mNearToPlayer;
	mBufferInterface.UpdateBuffer(mConstantBuffer_ps, &cBufferSubResource_2, sizeof(cBufferSubResource_2));
}

void Task::Render()
{
	//IA stage
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer_vs, 0);


	//PS stage
	mBufferInterface.SetConstantBuffer_ps(&mConstantBuffer_ps, 1);
	GETDC->PSSetShaderResources(0, 1, &mSrv);
	GETDC->PSSetSamplers(0, 1, &mSamplerState);

	//IA�� inputLayout����, ���̴����ܰ迡 ����
	mShader->Render();

	//OM stage
	GETDC->OMSetBlendState(mBlendState, nullptr, 0xffffffff);


	//Draw
	mBufferInterface.Draw();
}
