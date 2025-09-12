#include "../../stdafx.h"
#include "AnimationPlayerMesh.h"

AnimationPlayerMesh::AnimationPlayerMesh(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY)
	:AnimationMesh(aniName, hlslPath, isLookingRight, transX, transY)
{
	SAFE_RELEASE(mConstantBuffer);
	mConstantBuffer = nullptr;

	//������� ����
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer, sizeof(ConstantStruct_player::constantStruct_player));
	
}

AnimationPlayerMesh::~AnimationPlayerMesh()
{
}

void AnimationPlayerMesh::Update(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow)
{

	///////////////////////////////////////////////////////////////////////////////////////
	//�ִϸ��̼� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, false);


	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation, colorBody, colorBodyShadow);

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



void AnimationPlayerMesh::UpdateFromCam(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow)
{
	
	AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, false);

	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	D3DXVECTOR2 tempCamPos = GETCAMERA->GetCameraLdPos();

	//1.������ۿ� �� Subresource ����
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, tempCamPos.x + mTransX, tempCamPos.y + mTransY, mRotation, colorBody, colorBodyShadow);

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


//������Ʈ�ε� ķ���� �ƴϴ� �׸��� �Ű������޾Ƽ� �����
void AnimationPlayerMesh::Update_tillLast(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow, bool isFrameLast)
{

	///////////////////////////////////////////////////////////////////////////////////////
	//�ִϸ��̼� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//�������� �ƴϸ� ��� ������ ������Ʈ 
	if (isFrameLast == false) {
		AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, false);
	}


	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_player::constantStruct_player cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData_player.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation, colorBody, colorBodyShadow);

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

	//IA�� inputLayout����, ���̴����ܰ迡 ����
	mShader->Render();

	//OM stage
	GETDC->OMSetBlendState(mBlendState, nullptr, 0xffffffff);


	//Draw
	mBufferInterface.Draw();
}
