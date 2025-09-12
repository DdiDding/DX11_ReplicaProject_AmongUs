#include "../../stdafx.h"

#include "AnotherPlayer.h"

AnotherPlayer::AnotherPlayer(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY)
	:AnimationMesh(aniName, hlslPath, isLookingRight, transX, transY)
{
	SAFE_RELEASE(mConstantBuffer);
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer, sizeof(ConstantStruct_player::constantStruct_player));
}

AnotherPlayer::~AnotherPlayer()
{
}

void AnotherPlayer::Update()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation, mColor_body, mColor_body_shadow);

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

