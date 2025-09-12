#include "../stdafx.h"
#include "AnimationMesh.h"

///////////////////////////////////////////////////////////////////////////////////////
//Public function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	�Լ� : AnimationMesh / [ ������ ]
	���� : �Ű������� �޾� �����ϰ� init�� �����Ѵ�
	�Ű�����
		1~4.World��Ŀ� ���� Scale, translation ���
*********************************************************************************/
AnimationMesh::AnimationMesh(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY)
{
	init(aniName, hlslPath, isLookingRight, transX, transY);
}


AnimationMesh::~AnimationMesh()
{
	SAFE_DELETE(mShader);
}


/*********************************************************************************
	�Լ� : Update
	���� : AnimationMesh�� ���� �������� ���� �ٸ� �������� �ڵ����� �ȳѰ���
*********************************************************************************/
void AnimationMesh::Update()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//�ִϸ��̼� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps);


	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation);

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


/*********************************************************************************
	�Լ� : Update_progress
	���� : �̰��ڵ����� �������� �Ѱ��ش�
*********************************************************************************/
void AnimationMesh::Update_progress()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//�ִϸ��̼� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps,false);


	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation);

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



/*********************************************************************************
	�Լ� : UpdateFromCam
	���� : AnimationMesh�� ���� �������� �����ϰ� ��ǥ�� screen��ǥ��Trans�� ����ϰ� �װ��� ī�޶� ��ǥ�� �����־� ������ǥ�� �����
	�Ű�����
		1. isReverse - �ִϸ��̼��� ������Ұ��� ������Ұ���
		2. isStop - �ִϸ��̼��� ������������ ����������� [true�� ����. false�� ���]
		TODO - bool�� �¿���� �����
*********************************************************************************/
void AnimationMesh::UpdateFromCam(bool isFrameReverse, bool isStop)
{
	if (isStop == false) {
		AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, isFrameReverse);
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	D3DXVECTOR2 tempCamPos = GETCAMERA->GetCameraLdPos();

	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, tempCamPos.x + mTransX, tempCamPos.y + mTransY, mRotation);

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



/*********************************************************************************
	�Լ� : Update_ps_int
	���� : int�� �ڷḦ PixelShader�� ������۷� �ѱ��
*********************************************************************************/
void AnimationMesh::Update_ps_int(int value)
{
	//1.������ۿ� �� Subresource ����
	ConstantStruct_matrix::constantStruct_int cBufferSubResource2;

	//2.Subresource�� �Ű������� ���� �����͸� ����
	cBufferSubResource2.plusData = value;

	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_ps, &cBufferSubResource2, sizeof(cBufferSubResource2));
}



/*********************************************************************************
	�Լ� : Render
	���� : �� ���ҽ��� ���������ο� �����Ѵ�
*********************************************************************************/
void AnimationMesh::Render()
{
	//IA stage
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//VS stage
	mBufferInterface.SetConstantBuffer_vs(&mConstantBuffer, 0);


	//PS stage
	mBufferInterface.SetConstantBuffer_ps(&mConstantBuffer_ps, 1);
	GETDC->PSSetShaderResources(0, 1, &mAnimation.mSrv);
	GETDC->PSSetSamplers(0, 1, &mSamplerState);

	//IA�� inputLayout����, ���̴����ܰ迡 ����
	mShader->Render();

	//OM stage
	GETDC->OMSetBlendState(mBlendState, nullptr, 0xffffffff);


	//Draw
	mBufferInterface.Draw();
}



/*********************************************************************************
	�Լ� : IsFrameMax
	���� : ���� �������� ������ ���������� Ȯ���Ѵ�
*********************************************************************************/
bool AnimationMesh::IsFrameMax()
{
	if (mFrame == (mAnimation.mMaxFrame-1)) return true;
	else return false;
}



/*********************************************************************************
	�Լ� : IsFrameZero
	���� : ���� �������� ù��° ���������� Ȯ���Ѵ�
*********************************************************************************/
bool AnimationMesh::IsFrameZero()
{
	if (mFrame == 0) return true;
	else return false;
}

void AnimationMesh::ChangeShader(LPCWSTR hlslPath)
{
	SAFE_DELETE(mShader);
	mHlslName = hlslPath;
	mShader = new Shader(mVertexData, mHlslName); //Shader, ������� ����
}

void AnimationMesh::SetAnimation(string aniName)
{
	mFrame = 0;
	mAnimation = AnimationManager::Get()->GetAnimation(aniName);
}


///////////////////////////////////////////////////////////////////////////////////////
//Private function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	�Լ� : Init
	���� : �ʱ�ȭ, �� Buffer���ҽ��� State�� �����Ѵ�
*********************************************************************************/
void AnimationMesh::init(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY)
{
	//string aniName, LPCWSTR hlslPath ,bool isLookingRight
	//�ִϸ��̼� �ʱ�ȭ
	mAnimation = AnimationManager::Get()->GetAnimation(aniName);
	mAniName = aniName;
	mFrame = 0;
	mTransX = transX;
	mTransY = transY;
	mIsLookingRight = isLookingRight;
	mHlslName = hlslPath;


	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer ����
	mBufferInterface.CreateIndexBuffer_rect(&mIndexBuffer); // IndexBuffer ����
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer, sizeof(ConstantStruct_matrix::constantStruct_matrix));
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_ps, sizeof(ConstantStruct_matrix::constantStruct_int));
	

	mShader = new Shader(mVertexData, mHlslName); //Shader, ������� ����


	createSamplerState(); //SamplerState ����


	createBlendState(); //BlendState ����
}

//TODO:: STate ���� Ŭ���� ��������
void AnimationMesh::createSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc;

	//samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = FLT_MIN;
	samplerDesc.MaxLOD = FLT_MAX;

	GETDEVICE->CreateSamplerState(&samplerDesc, &mSamplerState);
}

void AnimationMesh::createBlendState()
{
	D3D11_BLEND_DESC blendDesc;

	blendDesc.AlphaToCoverageEnable = true;
	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	GETDEVICE->CreateBlendState(&blendDesc, &mBlendState);
}

