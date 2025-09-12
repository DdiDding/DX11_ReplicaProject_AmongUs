#include "../../stdafx.h"
#include "AnimationPlayerMesh.h"

AnimationPlayerMesh::AnimationPlayerMesh(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY)
	:AnimationMesh(aniName, hlslPath, isLookingRight, transX, transY)
{
	SAFE_RELEASE(mConstantBuffer);
	mConstantBuffer = nullptr;

	//상수버퍼 생성
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer, sizeof(ConstantStruct_player::constantStruct_player));
	
}

AnimationPlayerMesh::~AnimationPlayerMesh()
{
}

void AnimationPlayerMesh::Update(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow)
{

	///////////////////////////////////////////////////////////////////////////////////////
	//애니메이션 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, false);


	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation, colorBody, colorBodyShadow);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));



	///////////////////////////////////////////////////////////////////////////////////////
	//버텍스버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.변경 할 구조체 데이터 변경
	{
		AnimationManager::Get()->SetUvFromAnimationUv(mVertexData.GetData()->at(0).uv, mVertexData.GetData()->at(1).uv, mVertexData.GetData()->at(2).uv, mVertexData.GetData()->at(3).uv, mAnimation.mVecFrame.at(mFrame), mIsLookingRight);
	}

	//2.버텍스버퍼 업데이트 (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());
}



void AnimationPlayerMesh::UpdateFromCam(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow)
{
	
	AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, false);

	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	D3DXVECTOR2 tempCamPos = GETCAMERA->GetCameraLdPos();

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, tempCamPos.x + mTransX, tempCamPos.y + mTransY, mRotation, colorBody, colorBodyShadow);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));



	///////////////////////////////////////////////////////////////////////////////////////
	//버텍스버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.변경 할 구조체 데이터 변경
	{
		AnimationManager::Get()->SetUvFromAnimationUv(mVertexData.GetData()->at(0).uv, mVertexData.GetData()->at(1).uv, mVertexData.GetData()->at(2).uv, mVertexData.GetData()->at(3).uv, mAnimation.mVecFrame.at(mFrame), mIsLookingRight);
	}

	//2.버텍스버퍼 업데이트 (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());
}


//업데이트인데 캠기준 아니다 그리고 매개변수받아서 멈춘다
void AnimationPlayerMesh::Update_tillLast(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow, bool isFrameLast)
{

	///////////////////////////////////////////////////////////////////////////////////////
	//애니메이션 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//마지막이 아니면 계속 프레임 업데이트 
	if (isFrameLast == false) {
		AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, false);
	}


	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation, colorBody, colorBodyShadow);

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));



	///////////////////////////////////////////////////////////////////////////////////////
	//버텍스버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.변경 할 구조체 데이터 변경
	{
		AnimationManager::Get()->SetUvFromAnimationUv(mVertexData.GetData()->at(0).uv, mVertexData.GetData()->at(1).uv, mVertexData.GetData()->at(2).uv, mVertexData.GetData()->at(3).uv, mAnimation.mVecFrame.at(mFrame), mIsLookingRight);
	}

	//2.버텍스버퍼 업데이트 (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());
}



void AnimationPlayerMesh::Render()
{

	//IA stage
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer, 2);
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer, 0);


	//PS stage
	GETDC->PSSetShaderResources(0, 1, &mAnimation.mSrv);
	GETDC->PSSetSamplers(0, 1, &mSamplerState);

	//IA에 inputLayout연결, 셰이더각단계에 연결
	mShader->Render();

	//OM stage
	GETDC->OMSetBlendState(mBlendState, nullptr, 0xffffffff);


	//Draw
	mBufferInterface.Draw();
}
