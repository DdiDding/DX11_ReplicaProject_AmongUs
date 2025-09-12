#include "../stdafx.h"
#include "../Manager/ImposterManager.h"
#include "../Manager/CrewManager.h"
#include "AnimationRect.h"

///////////////////////////////////////////////////////////////////////////////////////
//Public function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	함수 : AnimationRect / [ 생성자 ]
	목적 : 매개변수를 받아 저장하고 init을 실행한다
	매개변수
		1~4.World행렬에 계산될 Scale, translation 상수
*********************************************************************************/
AnimationRect::AnimationRect( )
{
	init();
}


AnimationRect::~AnimationRect()
{
	SAFE_DELETE(mShader);
}


/*********************************************************************************
	함수 : Update
	목적 : AnimationRect에 관한 변수들을 변경
*********************************************************************************/
void AnimationRect::Update()
{

	//스폰 애니메이션 실행 부분
	if (mIsSpawn == true) {

		//맥스 프레임이면
		if (mFrame == (mAnimation.mMaxFrame - 1)) {

			mSpwanAniCnt++;

			if (mSpwanAniCnt == 3) {

				int a = 0;
				mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
				mAniName = "Player_Stand";
				mFrame = 0;
				mIsSpawn = false;
				mIsMoveOK = true;
				mTransX += 182;
				mTransY -= 6;
			}
			else {

				mAnimation = AnimationManager::Get()->GetAnimation("Player_Spawn2");
				mAniName = "Player_Spawn2";
				mFrame = 0;
			}
		}

	}
	

	//죽이는 애니메이션 실행 부분
	if (mIsKilling == true) {

		mKillTime += Time::Get()->Delta();

		mAnimation = AnimationManager::Get()->GetAnimation("Player_Kill");
		mAniName = "Player_Kill";
		

		if (mKillMaxTime < mKillTime) {

			mKillTime = 0.0f; //시간초기화
			
			mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
			mAniName = "Player_Stand";

			//죽인 상대방의 위치를 가져오는것
			D3DXVECTOR2 tempPos = ClientData::Get()->mAnotherPlayer_inGame[ClientData::Get()->mWhoIKilled].mPos;

			mTransX = tempPos.x;
			mTransY = tempPos.y;

			mIsKilling = false;
		}

		mFrame = 0;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//플레이어 인게임 데이터 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	mMyArea_string = MapManager::Get()->WhereIsPlayer(RECT{ (int)mTransX, (int)mTransY + (int)mGuideSize, (int)mTransX + (int)mTempSize.x, (int)mTransY }, &mMyArea);


	///////////////////////////////////////////////////////////////////////////////////////
	//키조작에 따른 애니메이션 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	
	bool tempPass = false;//필요없는 if문 검사안하기 위해 사용

	mPlayerVector = { 0, 0, 0}; // 이동 벡터값 항상초기화 이동시에 더해줌
	
	//먼저 움직일수있는지 확인 - 죽이는 상태에는 못움직인다 - 죽는 애니메이션이 아닐때 못움직인다
	if (mIsMoveOK == true && mIsKilling == false && CrewManager::Get()->GetStartDieAni() == false) {

		//0번 플레이어 일때
		if (ClientData::Get()->mPlayerNum == 0) {
			if (tempPass == false) {
				if (Keyboard::Get()->Press('W') == true) {

					mTransY += mFast;

					if (mInteract.MoveUp(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
						mTransY -= mFast;
					}
					tempPass = true;

					mPlayerVector.y += mFast;

					//유령상태가 아니면!
					if (mIsGhost == false) {
						mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
						mAniName = "Player_Walk";
					}
				}
				if (Keyboard::Get()->Press('S') == true) {

					mTransY -= mFast;

					if (mInteract.MoveDown(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
						mTransY += mFast;
					}
					tempPass = true;

					mPlayerVector.y -= mFast;

					if (mIsGhost == false) {
						mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
						mAniName = "Player_Walk";
					}
				}

				if (Keyboard::Get()->Press('A') == true) {

					mTransX -= mFast;

					if (mInteract.MoveLeft(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
						mTransX += mFast;
					}
					tempPass = true;
					mIsLookingRight = false;

					mPlayerVector.x -= mFast;

					if (mIsGhost == false) {
						mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
						mAniName = "Player_Walk";
					}
				}
				else if (Keyboard::Get()->Press('D') == true) {

					mTransX += mFast;

					if (mInteract.MoveRight(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
						mTransX -= mFast;
					}
					tempPass = true;
					mIsLookingRight = true;

					mPlayerVector.x += mFast;

					if (mIsGhost == false) {
						mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
						mAniName = "Player_Walk";
					}
				}
			}
			if (tempPass == false) {
				if (Keyboard::Get()->Up('W') == true) {

					if (mIsGhost == false) {
						mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
						mAniName = "Player_Stand";

						mFrame = 0;
					}
				}
				else if (Keyboard::Get()->Up('S') == true) {
					if (mIsGhost == false) {
						mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
						mAniName = "Player_Stand";

						mFrame = 0;
					}
				}
				else if (Keyboard::Get()->Up('A') == true) {
					if (mIsGhost == false) {
						mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
						mAniName = "Player_Stand";

						mFrame = 0;
					}
				}
				else if (Keyboard::Get()->Up('D') == true) {
					if (mIsGhost == false) {
						mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
						mAniName = "Player_Stand";

						mFrame = 0;
					}
				}
			}
		}
		//1번플레이어 일때
		else if (ClientData::Get()->mPlayerNum == 1) {

		if (tempPass == false) {
			if (Keyboard::Get()->Press(VK_UP) == true) {

				mTransY += mFast;

				if (mInteract.MoveUp(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransY -= mFast;
				}
				tempPass = true;

				mPlayerVector.y += mFast;

				//유령상태가 아니면!
				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
					mAniName = "Player_Walk";
				}
			}
			if (Keyboard::Get()->Press(VK_DOWN) == true) {

				mTransY -= mFast;

				if (mInteract.MoveDown(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransY += mFast;
				}
				tempPass = true;

				mPlayerVector.y -= mFast;

				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
					mAniName = "Player_Walk";
				}
			}

			if (Keyboard::Get()->Press(VK_LEFT) == true) {

				mTransX -= mFast;

				if (mInteract.MoveLeft(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransX += mFast;
				}
				tempPass = true;
				mIsLookingRight = false;

				mPlayerVector.x -= mFast;

				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
					mAniName = "Player_Walk";
				}
			}
			else if (Keyboard::Get()->Press(VK_RIGHT) == true) {

				mTransX += mFast;

				if (mInteract.MoveRight(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransX -= mFast;
				}
				tempPass = true;
				mIsLookingRight = true;

				mPlayerVector.x += mFast;

				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
					mAniName = "Player_Walk";
				}
			}
		}
		if (tempPass == false) {
			if (Keyboard::Get()->Up(VK_UP) == true) {

				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
					mAniName = "Player_Stand";

					mFrame = 0;
				}
			}
			else if (Keyboard::Get()->Up(VK_DOWN) == true) {
				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
					mAniName = "Player_Stand";

					mFrame = 0;
				}
			}
			else if (Keyboard::Get()->Up(VK_LEFT) == true) {
				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
					mAniName = "Player_Stand";

					mFrame = 0;
				}
			}
			else if (Keyboard::Get()->Up(VK_RIGHT) == true) {
				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
					mAniName = "Player_Stand";

					mFrame = 0;
				}
			}
		}
		}
		//2번 플레이어 일때
		else if (ClientData::Get()->mPlayerNum == 2) {
		if (tempPass == false) {
			if (Keyboard::Get()->Press(0x38) == true) {

				mTransY += mFast;

				if (mInteract.MoveUp(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransY -= mFast;
				}
				tempPass = true;

				mPlayerVector.y += mFast;

				//유령상태가 아니면!
				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
					mAniName = "Player_Walk";
				}
			}
			if (Keyboard::Get()->Press(0x35) == true) {

				mTransY -= mFast;

				if (mInteract.MoveDown(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransY += mFast;
				}
				tempPass = true;

				mPlayerVector.y -= mFast;

				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
					mAniName = "Player_Walk";
				}
			}

			if (Keyboard::Get()->Press(0x34) == true) {

				mTransX -= mFast;

				if (mInteract.MoveLeft(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransX += mFast;
				}
				tempPass = true;
				mIsLookingRight = false;

				mPlayerVector.x -= mFast;

				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
					mAniName = "Player_Walk";
				}
			}
			else if (Keyboard::Get()->Press(0x36) == true) {

				mTransX += mFast;

				if (mInteract.MoveRight(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransX -= mFast;
				}
				tempPass = true;
				mIsLookingRight = true;

				mPlayerVector.x += mFast;

				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Walk");
					mAniName = "Player_Walk";
				}
			}
		}
		if (tempPass == false) {
			if (Keyboard::Get()->Up(0x38) == true) {

				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
					mAniName = "Player_Stand";

					mFrame = 0;
				}
			}
			else if (Keyboard::Get()->Up(0x35) == true) {
				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
					mAniName = "Player_Stand";

					mFrame = 0;
				}
			}
			else if (Keyboard::Get()->Up(0x34) == true) {
				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
					mAniName = "Player_Stand";

					mFrame = 0;
				}
			}
			else if (Keyboard::Get()->Up(0x36) == true) {
				if (mIsGhost == false) {
					mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
					mAniName = "Player_Stand";

					mFrame = 0;
				}
			}
		}
		}
	}
	

	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//대력 여기쯤 뻑는데
	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_player::constantStruct_player cBufferSubResource;
	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX, mTransY, mRotation, mColor_body, mColor_body_shadow);
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



	///////////////////////////////////////////////////////////////////////////////////////
	//애니메이션 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, false);



	///////////////////////////////////////////////////////////////////////////////////////
	//디버그용 가이드라인 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//mDebug.Update();
}


/*********************************************************************************
	함수 : Update_NoMove
	목적 : 업데이트지만 상호작용없이 값만 업데이트 된다
*********************************************************************************/
void AnimationRect::Update_NoMove()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//상수버퍼 업데이트
	///////////////////////////////////////////////////////////////////////////////////////

	//1.상수버퍼에 들어갈 Subresource 생성
	ConstantStruct_player::constantStruct_player cBufferSubResource;
	//2.Subresource에 매개변수에 따라 데이터를 변경
	mConstantData.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX, mTransY, mRotation, mColor_body, mColor_body_shadow);
	//3.상수버퍼 업데이트 (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));

}


/*********************************************************************************
	함수 : Render
	목적 : 각 리소스를 파이프라인에 연결한다
*********************************************************************************/
void AnimationRect::Render()
{
	//IA stage
	mBufferInterface.SetVertexBuffer(&mVertexBuffer);
	mBufferInterface.SetIndexBuffer_rect(mIndexBuffer);
	GETDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//VS stage
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

	//디버그 랜더링
	//mDebug.Render(D3DXVECTOR2(mTransX,mTransY), mTempSize, mGuideSize);
}

void AnimationRect::ChangeAni(string aniName)
{
	//애니메이션 초기화
	mAnimation = AnimationManager::Get()->GetAnimation(aniName);
	mAniName = aniName;
	mFrame = 0;
}

void AnimationRect::ChangeShader(LPCWSTR hlslPath)
{
	SAFE_DELETE(mShader);
	mHlslName = hlslPath;
	mShader = new Shader(mVertexData, mHlslName); //Shader, 상수버퍼 생성
}



///////////////////////////////////////////////////////////////////////////////////////
//Private function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	함수 : Init
	목적 : 초기화, 각 Buffer리소스와 State를 생성한다
*********************************************************************************/
void AnimationRect::init()
{
	//애니메이션 초기화
	mAnimation = AnimationManager::Get()->GetAnimation("Player_Spawn1");
	mAniName = "Player_Spawn1";
	mFrame = 0;
	
	mTransX = 2940;// == 플레이어의 좌측하단 꼭짓점X 좌표이당
	mTransY = 2500;// == 플레이어의 좌측하단 꼭짓점y 좌표이당
	mIsLookingRight = true;
	mHlslName = L"./Hlsl/NewPlayerShader.hlsl";

	mOriginSize = AnimationManager::Get()->GetOriginSize_player();
	mTempSize = AnimationManager::Get()->GetOriginSize_player();

	
	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer 생성
	mBufferInterface.CreateIndexBuffer_rect(&mIndexBuffer); // IndexBuffer 생성
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer, sizeof(ConstantStruct_player::constantStruct_player));


	mShader = new Shader(mVertexData, mHlslName); //Shader, 상수버퍼 생성
	

	createSamplerState(); //SamplerState 생성
	createBlendState(); //BlendState 생성

	
	mTaskCompleted = 0;

	//스폰 애니메이션 부분 -----
	mIsSpawn = true;
	mSpwanAniCnt = 1;

	//플레이어의 스텟같은느낌ㅋㅋ----------
	mFast = 5;

	mIsMoveOK = false; //처음은 못움직이게 막음
}


//TODO:: STate 따로 클래스 만들어관리
void AnimationRect::createSamplerState()
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

void AnimationRect::createBlendState()
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

