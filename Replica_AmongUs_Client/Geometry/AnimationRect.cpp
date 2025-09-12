#include "../stdafx.h"
#include "../Manager/ImposterManager.h"
#include "../Manager/CrewManager.h"
#include "AnimationRect.h"

///////////////////////////////////////////////////////////////////////////////////////
//Public function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	�Լ� : AnimationRect / [ ������ ]
	���� : �Ű������� �޾� �����ϰ� init�� �����Ѵ�
	�Ű�����
		1~4.World��Ŀ� ���� Scale, translation ���
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
	�Լ� : Update
	���� : AnimationRect�� ���� �������� ����
*********************************************************************************/
void AnimationRect::Update()
{

	//���� �ִϸ��̼� ���� �κ�
	if (mIsSpawn == true) {

		//�ƽ� �������̸�
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
	

	//���̴� �ִϸ��̼� ���� �κ�
	if (mIsKilling == true) {

		mKillTime += Time::Get()->Delta();

		mAnimation = AnimationManager::Get()->GetAnimation("Player_Kill");
		mAniName = "Player_Kill";
		

		if (mKillMaxTime < mKillTime) {

			mKillTime = 0.0f; //�ð��ʱ�ȭ
			
			mAnimation = AnimationManager::Get()->GetAnimation("Player_Stand");
			mAniName = "Player_Stand";

			//���� ������ ��ġ�� �������°�
			D3DXVECTOR2 tempPos = ClientData::Get()->mAnotherPlayer_inGame[ClientData::Get()->mWhoIKilled].mPos;

			mTransX = tempPos.x;
			mTransY = tempPos.y;

			mIsKilling = false;
		}

		mFrame = 0;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	//�÷��̾� �ΰ��� ������ ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	mMyArea_string = MapManager::Get()->WhereIsPlayer(RECT{ (int)mTransX, (int)mTransY + (int)mGuideSize, (int)mTransX + (int)mTempSize.x, (int)mTransY }, &mMyArea);


	///////////////////////////////////////////////////////////////////////////////////////
	//Ű���ۿ� ���� �ִϸ��̼� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	
	bool tempPass = false;//�ʿ���� if�� �˻���ϱ� ���� ���

	mPlayerVector = { 0, 0, 0}; // �̵� ���Ͱ� �׻��ʱ�ȭ �̵��ÿ� ������
	
	//���� �����ϼ��ִ��� Ȯ�� - ���̴� ���¿��� �������δ� - �״� �ִϸ��̼��� �ƴҶ� �������δ�
	if (mIsMoveOK == true && mIsKilling == false && CrewManager::Get()->GetStartDieAni() == false) {

		//0�� �÷��̾� �϶�
		if (ClientData::Get()->mPlayerNum == 0) {
			if (tempPass == false) {
				if (Keyboard::Get()->Press('W') == true) {

					mTransY += mFast;

					if (mInteract.MoveUp(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
						mTransY -= mFast;
					}
					tempPass = true;

					mPlayerVector.y += mFast;

					//���ɻ��°� �ƴϸ�!
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
		//1���÷��̾� �϶�
		else if (ClientData::Get()->mPlayerNum == 1) {

		if (tempPass == false) {
			if (Keyboard::Get()->Press(VK_UP) == true) {

				mTransY += mFast;

				if (mInteract.MoveUp(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransY -= mFast;
				}
				tempPass = true;

				mPlayerVector.y += mFast;

				//���ɻ��°� �ƴϸ�!
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
		//2�� �÷��̾� �϶�
		else if (ClientData::Get()->mPlayerNum == 2) {
		if (tempPass == false) {
			if (Keyboard::Get()->Press(0x38) == true) {

				mTransY += mFast;

				if (mInteract.MoveUp(D3DXVECTOR2(mTransX, mTransY), mTempSize, mGuideSize, mMyArea_string) == true) {
					mTransY -= mFast;
				}
				tempPass = true;

				mPlayerVector.y += mFast;

				//���ɻ��°� �ƴϸ�!
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
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//��� ������ ���µ�
	//1.������ۿ� �� Subresource ����
	ConstantStruct_player::constantStruct_player cBufferSubResource;
	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX, mTransY, mRotation, mColor_body, mColor_body_shadow);
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



	///////////////////////////////////////////////////////////////////////////////////////
	//�ִϸ��̼� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	AnimationManager::Get()->DoCountFrame(&mFrame, mAnimation.mMaxFrame, &mFps, mAnimation.mFps, false);



	///////////////////////////////////////////////////////////////////////////////////////
	//����׿� ���̵���� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//mDebug.Update();
}


/*********************************************************************************
	�Լ� : Update_NoMove
	���� : ������Ʈ���� ��ȣ�ۿ���� ���� ������Ʈ �ȴ�
*********************************************************************************/
void AnimationRect::Update_NoMove()
{
	///////////////////////////////////////////////////////////////////////////////////////
	//������� ������Ʈ
	///////////////////////////////////////////////////////////////////////////////////////

	//1.������ۿ� �� Subresource ����
	ConstantStruct_player::constantStruct_player cBufferSubResource;
	//2.Subresource�� �Ű������� ���� �����͸� ����
	mConstantData.UpdateStruct_player(&cBufferSubResource, mAnimation.mWidth, mAnimation.mHeight, mTransX, mTransY, mRotation, mColor_body, mColor_body_shadow);
	//3.������� ������Ʈ (mpa ,unmap)
	mBufferInterface.UpdateBuffer(mConstantBuffer, &cBufferSubResource, sizeof(cBufferSubResource));

}


/*********************************************************************************
	�Լ� : Render
	���� : �� ���ҽ��� ���������ο� �����Ѵ�
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

	//IA�� inputLayout����, ���̴����ܰ迡 ����
	mShader->Render();

	//OM stage
	GETDC->OMSetBlendState(mBlendState, nullptr, 0xffffffff);


	//Draw
	mBufferInterface.Draw();

	//����� ������
	//mDebug.Render(D3DXVECTOR2(mTransX,mTransY), mTempSize, mGuideSize);
}

void AnimationRect::ChangeAni(string aniName)
{
	//�ִϸ��̼� �ʱ�ȭ
	mAnimation = AnimationManager::Get()->GetAnimation(aniName);
	mAniName = aniName;
	mFrame = 0;
}

void AnimationRect::ChangeShader(LPCWSTR hlslPath)
{
	SAFE_DELETE(mShader);
	mHlslName = hlslPath;
	mShader = new Shader(mVertexData, mHlslName); //Shader, ������� ����
}



///////////////////////////////////////////////////////////////////////////////////////
//Private function
///////////////////////////////////////////////////////////////////////////////////////


/*********************************************************************************
	�Լ� : Init
	���� : �ʱ�ȭ, �� Buffer���ҽ��� State�� �����Ѵ�
*********************************************************************************/
void AnimationRect::init()
{
	//�ִϸ��̼� �ʱ�ȭ
	mAnimation = AnimationManager::Get()->GetAnimation("Player_Spawn1");
	mAniName = "Player_Spawn1";
	mFrame = 0;
	
	mTransX = 2940;// == �÷��̾��� �����ϴ� ������X ��ǥ�̴�
	mTransY = 2500;// == �÷��̾��� �����ϴ� ������y ��ǥ�̴�
	mIsLookingRight = true;
	mHlslName = L"./Hlsl/NewPlayerShader.hlsl";

	mOriginSize = AnimationManager::Get()->GetOriginSize_player();
	mTempSize = AnimationManager::Get()->GetOriginSize_player();

	
	mBufferInterface.CreateVertexBuffer(&mVertexBuffer, mVertexData, true); // VertexBuffer ����
	mBufferInterface.CreateIndexBuffer_rect(&mIndexBuffer); // IndexBuffer ����
	mBufferInterface.CreateConstantBuffer(&mConstantBuffer, sizeof(ConstantStruct_player::constantStruct_player));


	mShader = new Shader(mVertexData, mHlslName); //Shader, ������� ����
	

	createSamplerState(); //SamplerState ����
	createBlendState(); //BlendState ����

	
	mTaskCompleted = 0;

	//���� �ִϸ��̼� �κ� -----
	mIsSpawn = true;
	mSpwanAniCnt = 1;

	//�÷��̾��� ���ݰ�����������----------
	mFast = 5;

	mIsMoveOK = false; //ó���� �������̰� ����
}


//TODO:: STate ���� Ŭ���� ��������
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

