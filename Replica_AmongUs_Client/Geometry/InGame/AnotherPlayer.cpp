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
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation, mColor_body, mColor_body_shadow);

	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));



	///////////////////////////////////////////////////////////////////////////////////////
	//���ؽ����� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.���� �� ����ü ������ ����
	{
		AnimationManager::Get()->SetUvFromAnimationUv(mVertexData.GetData()->at(0).uv, mVertexData.GetData()->at(1).uv, mVertexData.GetData()->at(2).uv, mVertexData.GetData()->at(3).uv, mAnimation.mVecFrame.at(mFrame), mIsLookingRight);
	}

	//2.���ؽ����� ������Ʈ (map, unmap)
	mBufferInterface.UpdateBuffer(mVertexBuffer, mVertexData.GetData()->data(), sizeof(mVertexData.GetData()->front()) * mVertexData.GetData()->size());

}

