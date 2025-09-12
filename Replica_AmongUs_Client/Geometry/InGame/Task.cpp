#include "../../stdafx.h"

#include "Task.h"

//공교롭게도 설계를 개좆같이해서 공용 Task를 이곳에 넣어버렸습니다.
//그래서 마지막 매개변수에 공용인지 개인인지 구분하는 변수가 필요하합니다.
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

	//하얀테스크면 다 업데이트해야하니까 false
	if(mIsYellow == false) mThisBlack = false;
	//노란색은 플레이어 리스트 목록 확인해애ㅑ하니까 일단 true
	else  mThisBlack = true;


	//상수버퍼 생성
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_ps, sizeof(ConstantStruct_matrix::constantStruct_int));
}

Task::~Task()
{
}

void Task::Update()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	/*VS에 들어갈 상수버퍼*************************/
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mSizeX, mSizeY, mTransX, mTransY, mRotation);
	mBufferInterface.UpdateBuffer(mConstantBuffer_vs, &cBufferSubResource, sizeof(cBufferSubResource));

	/*PS에 들어갈 상수버퍼*************************/
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

	//IA에 inputLayout연결, 셰이더각단계에 연결
	mShader->Render();

	//OM stage
	GETDC->OMSetBlendState(mBlendState, nullptr, 0xffffffff);


	//Draw
	mBufferInterface.Draw();
}
