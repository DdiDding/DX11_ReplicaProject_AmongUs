#include "../stdafx.h"
#include "AnimationMesh.h"

///////////////////////////////////////////////////////////////////////////////////////
//Public function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	함수 : AnimationMesh / [ 생성자 ]
	목적 : 매개변수를 받아 저장하고 init을 실행한다
	매개변수
		1~4.World행렬에 계산될 Scale, translation 상수
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
	함수 : Update
	목적 : AnimationMesh에 관한 변수들을 변경 다만 프레임은 자동으로 안넘겨줌
*********************************************************************************/
void AnimationMesh::Update()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//애니메이션 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps);


	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation);

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


/*********************************************************************************
	함수 : Update_progress
	목적 : 이건자동으로 프레임을 넘겨준다
*********************************************************************************/
void AnimationMesh::Update_progress()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//애니메이션 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps,false);


	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX - mTempSize.x, mTransY + mTempSize.y, mRotation);

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



/*********************************************************************************
	함수 : UpdateFromCam
	목적 : AnimationMesh에 관한 변수들을 변경하고 좌표를 screen좌표계Trans를 사용하고 그곳에 카메라 좌표를 더해주어 월드좌표를 만든다
	매개변수
		1. isReverse - 애니메이션을 정재생할건지 역재생할건지
		2. isStop - 애니메이션이 정지상태인지 재생상태인지 [true면 정지. false면 재생]
		TODO - bool형 좌우봔전 만들기
*********************************************************************************/
void AnimationMesh::UpdateFromCam(bool isFrameReverse, bool isStop)
{
	if (isStop == false) {
		AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, isFrameReverse);
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	D3DXVECTOR2 tempCamPos = GETCAMERA->GetCameraLdPos();

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_matrix cBufferSubResource;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_matrix(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, tempCamPos.x + mTransX, tempCamPos.y + mTransY, mRotation);

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



/*********************************************************************************
	함수 : Update_ps_int
	목적 : int형 자료를 PixelShader에 상수버퍼로 넘긴다
*********************************************************************************/
void AnimationMesh::Update_ps_int(int value)
{
	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_matrix::constantStruct_int cBufferSubResource2;

	//2.Subresource에 매개변수에 따라 데이터를 변경
	cBufferSubResource2.plusData = value;

	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer_ps, &cBufferSubResource2, sizeof(cBufferSubResource2));
}



/*********************************************************************************
	함수 : Render
	목적 : 각 리소스를 파이프라인에 연결한다
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

	//IA에 inputLayout연결, 셰이더각단계에 연결
	mShader->Render();

	//OM stage
	GETDC->OMSetBlendState(mBlendState, nullptr, 0xffffffff);


	//Draw
	mBufferInterface.Draw();
}



/*********************************************************************************
	함수 : IsFrameMax
	목적 : 현재 프레임이 마지막 프레임인지 확인한다
*********************************************************************************/
bool AnimationMesh::IsFrameMax()
{
	if (mFrame == (mAnimation.mMaxFrame-1)) return true;
	else return false;
}



/*********************************************************************************
	함수 : IsFrameZero
	목적 : 현재 프레임이 첫번째 프레임인지 확인한다
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
	mShader = new Shader(mVertexData, mHlslName); //Shader, 상수버퍼 생성
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
	함수 : Init
	목적 : 초기화, 각 Buffer리소스와 State를 생성한다
*********************************************************************************/
void AnimationMesh::init(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY)
{
	//string aniName, LPCWSTR hlslPath ,bool isLookingRight
	//애니메이션 초기화
	mAnimation = AnimationManager::Get()->GetAnimation(aniName);
	mAniName = aniName;
	mFrame = 0;
	mTransX = transX;
	mTransY = transY;
	mIsLookingRight = isLookingRight;
	mHlslName = hlslPath;


	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer 생성
	mBufferInterface.CreateIndexBuffer_rect(&mIndexBuffer); // IndexBuffer 생성
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer, sizeof(ConstantStruct_matrix::constantStruct_matrix));
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer_ps, sizeof(ConstantStruct_matrix::constantStruct_int));
	

	mShader = new Shader(mVertexData, mHlslName); //Shader, 상수버퍼 생성


	createSamplerState(); //SamplerState 생성


	createBlendState(); //BlendState 생성
}

//TODO:: STate 따로 클래스 만들어관리
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

