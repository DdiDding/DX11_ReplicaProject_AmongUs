#include "../../../stdafx.h"
#include "../../Mesh.h"
#include "../../AnimationMesh.h"
#include "O2_ClienFilter.h"

O2_ClienFilter::O2_ClienFilter()
{
	init();
}

O2_ClienFilter::~O2_ClienFilter()
{
}

void O2_ClienFilter::Update()
{
	
	mClosseBtn->Update_withCam();
	mBackGround->Update_withCam();
	mFront->Update_withCam();

	if (mActtiveArrow == true) {
		mRightArrow->UpdateFromCam(false, false);
		mLeftArrow->UpdateFromCam(false, false);
	}

	updateLeaf();

	if (mIsComplete == true) {
		mRightCompleteArrow->Update_withCam();
		mLeftCompleteArrow->Update_withCam();
	}

	//���콺Ŭ���ߴµ�, �������� �ϳ��� �ȴ����ų� && �簢���� ������������ -> ������
	if (Mouse::Get()->Down(1) == true && isLeafClick() == false && mBackGround->IsClik() == false) {

		mClickEnd = true;
	}


	//////////////////////////////////////////
	//���� �ö󰡰ų� �������� �ִϸ��̼� �κ�
	{

		//�ö󰡴� ���̸� ���� �����ش� [���� ���̳ʽ��̱⿡]
		if (mIsUp == true) {

			mAllMeshMove += mAllMeshMoveFast;

			//�� �ö󰡸� ��ž
			if (0 < mAllMeshMove) {

				mAllMeshMove = 0;
				mIsUp = false;
			}

			mBackGround->SetTransY(111 + mAllMeshMove);
			mFront->SetTransY(111 + mAllMeshMove);
			mClosseBtn->SetTransY(576 + mAllMeshMove);

			for (int index = 0; index < 7; index++) {

				mLeaf[index].mLeafMesh->SetTransY(mLeaf[index].mLeafTrans.y + mAllMeshMove);
			}
		}
		//��������! -> ��������
		else if (mIsComplete == true) {

			if (mDownTime < mDownMaxTime) {

				//�ڵ����� ������������� �ð� ���
				mDownTime += Time::Get()->Delta();
			}
			else {

				mAllMeshMove -= mAllMeshMoveFast;

				mBackGround->SetTransY(111 + mAllMeshMove);
				mFront->SetTransY(111 + mAllMeshMove);
				mClosseBtn->SetTransY(576 + mAllMeshMove);
				mLeftCompleteArrow->SetTransY(337 + mAllMeshMove);
				mRightCompleteArrow->SetTransY(350 + mAllMeshMove);

				//�� �ö󰡸� ��ž
				if (mAllMeshMove <= mAllMeshMoveMin) {

					mAllMeshMove = mAllMeshMoveMin;
					mClickEnd = true;
				}
			}
		}
	}
}

void O2_ClienFilter::Render()
{

	mBackGround->Render();
	if (mActtiveArrow == true) {
		mRightArrow->Render();
	}

	renderLeaf();

	mFront->Render();
	if (mActtiveArrow == true) {
		mLeftArrow->Render();
	}

	mRightCompleteArrow->Render();
	mLeftCompleteArrow->Render();

	mClosseBtn->Render();
}

void O2_ClienFilter::init()
{
	//���� ------
	mIsComplete = false;
	mClickEnd = false;

	//�Ž��� ����------
	mClosseBtn = new Mesh(35.0f, 35.0f, 352.0f, 576.0f + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Ui/Ui_btn.png");
	mClosseBtn->Update_Uv(
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f / 3, 0.0f),
		D3DXVECTOR2(1.0f / 3, 1.0f)
	);

	initLeaf();

	mBackGround = new Mesh(500, 500, 391, 111 + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/CleanFilter/o2_CleanBack.png");
	mFront = new Mesh(49, 500, 391, 111 + mAllMeshMove, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/CleanFilter/o2_CleanFront.png");
	 
	
	mLeftArrow = new AnimationMesh("Task_CleanFilter_leftArrow", L"./Hlsl/TextureShader.hlsl", true, 405, 337);
	mRightArrow = new AnimationMesh("Task_CleanFilter_rightArrow", L"./Hlsl/TextureShader.hlsl", true, 470, 350);
	

	//�̰�  �Ϸ�ǰ� �����⋚���� mAllMeshMove �� �Ⱥٿ��ش�
	mLeftCompleteArrow = new Mesh(30, 48, 405, 337, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/CleanFilter/arrowFinishedLeft.png");
	mRightCompleteArrow = new Mesh(11, 21, 470, 350, L"./Hlsl/TextureShader.hlsl", L"Resorce/Task/CleanFilter/arrowFinishedRight.png");
}

void O2_ClienFilter::initLeaf()
{
	uniform_int_distribution<int> randPosX(558, 829);
	uniform_int_distribution<int> randPosY(233, 484);
	
	
	mLeaf[0].mLeafMesh = new Mesh(22, 61, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf1.png");
	mLeaf[1].mLeafMesh = new Mesh(22, 71, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf2.png");
	mLeaf[2].mLeafMesh = new Mesh(24, 80, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf3.png");
	mLeaf[3].mLeafMesh = new Mesh(23, 54, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf4.png");
	mLeaf[4].mLeafMesh = new Mesh(22, 74, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf5.png");
	mLeaf[5].mLeafMesh = new Mesh(60, 73, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf6.png");
	mLeaf[6].mLeafMesh = new Mesh(32, 47, (float)randPosX(gen), (float)randPosY(gen) + mAllMeshMove, L"./Hlsl/LeafShader.hlsl", L"Resorce/Task/CleanFilter/o2_leaf7.png");


	for (int index = 0; index < 7; index++) {

		mLeaf[index].mLeafMesh->SetVertexDataCenter();
		mLeaf[index].mIsComplete = false;
		mLeaf[index].mIsMove = false;
		mLeaf[index].mUintTrans = { 0,0 };
		mLeaf[index].mLeafMinFast = { 0,0 };
		mLeaf[index].mIsOuting = false;
		mLeaf[index].mLeafTrans = mLeaf[index].mLeafMesh->GetTrans();
		mLeaf[index].mLeafTrans.y = mLeaf[index].mLeafTrans.y - mAllMeshMove;
	}
}

void O2_ClienFilter::updateLeaf()
{

	for (int index = 0; index < 7; index++) {

		//�Ϸ���� ���� �����ٸ� ������Ʈ�Ѵ�
		if (mLeaf[index].mIsComplete == false) {

			//���콺�� ���� �������� Ȯ�� && �������� �������� �ȵȴ�
			if (Mouse::Get()->Down(1) && mLeaf[index].mLeafMesh->IsClik_Center() == true && mLeaf[index].mIsComplete == false) {

				//�ٸ� �������� �̹� ���������� �׳� �д�
				for (int i = 0; i < 7; i++) {

					//�ڱ��ڽ��� �ƴҶ��� �˻�
					if (mLeaf[i].mIsMove == true && i != index) {

						//������ ���������� false�ϰ� Ż��
						mLeaf[index].mIsMove = false;
						break;
					}
					//������ ������ ������������ true��
					mLeaf[index].mIsMove = true;
				}
				
				mActtiveArrow = true; //ȭ��ǥ �ִ� �Ҵ�
			}


			//���콺�̵����̸� ���콺 ���󰣴�! 
			if (mLeaf[index].mIsMove == true) {
				

				D3DXVECTOR2 tempPos = Mouse::Get()->GetPosition();

				float tempScala = GetVectorLength(tempPos, mLeaf[index].mLeafMesh->GetTrans());

				D3DXVECTOR2 tempMove;

				//�Ÿ��� �ּҰ� ���ϸ� 0,0���� �ʱ�ȭ
				if (tempScala < 1) {

					tempMove = { 0,0 };
				}
				else {

					//���� ���� ���ϱ�
					tempMove = tempPos - mLeaf[index].mLeafMesh->GetTrans();
					tempMove /= tempScala;
					tempMove *= 2;
				}

				//�������� �����ϰ� �ֱٲ� ��� �����ְ�
				mLeaf[index].mUintTrans = tempMove;
				mLeaf[index].mLeafMinFast = tempMove / 150;
			}
			//�̵����� �ƴϸ� �ӵ��� ���� ���δ�
			else {

				//�������� ���ؼ����� �����ʿ� ������
				if (mLeafOutX < mLeaf[index].mLeafMesh->GetTrans().x) {

					mLeaf[index].mIsOuting = false; //������Ծ��Ѵ�

					//��ȣ����, true�� ���, false�� ����
					bool tempBuhoBeforeX;
					bool tempBuhoBeforeY;
					bool tempBuhoAffterX;
					bool tempBuhoAffterY;

					//0���� ������
					if (mLeaf[index].mUintTrans.x < 0) tempBuhoBeforeX = false; else tempBuhoBeforeX = true;
					if (mLeaf[index].mUintTrans.y < 0) tempBuhoBeforeY = false; else tempBuhoBeforeY = true;

					//�ϴ� ����ϰ�
					mLeaf[index].mUintTrans -= mLeaf[index].mLeafMinFast;

					//����� ��ȣ ����
					if (mLeaf[index].mUintTrans.x < 0) tempBuhoAffterX = false; else tempBuhoAffterX = true;
					if (mLeaf[index].mUintTrans.y < 0) tempBuhoAffterY = false; else tempBuhoAffterY = true;


					//��ȣ �ٸ��� ���¹��� 0���� ����
					if ((tempBuhoBeforeX != tempBuhoAffterX) || (tempBuhoBeforeY != tempBuhoAffterY)) {
						mLeaf[index].mLeafMinFast.x = 0;
						mLeaf[index].mLeafMinFast.y = 0;
					}
				}
				//�������� �ѹ��� �� ���س��´�
				else if (mLeaf[index].mIsOuting == false){

					//�������� ���������� �������ͱ��Ѵ�
					float tempScala = GetVectorLength(mLeatOutPoint, mLeaf[index].mLeafMesh->GetTrans());

					D3DXVECTOR2 tempMove;


					//���� ���� ���ϱ�
					tempMove = mLeatOutPoint - mLeaf[index].mLeafMesh->GetTrans();
					tempMove /= tempScala;
					tempMove *= 2;
					

					//�������� �����ϰ� �ֱٲ� ��� �����ְ�
					mLeaf[index].mUintTrans = tempMove;
					mLeaf[index].mLeafMinFast += (tempMove / 10);

					mLeaf[index].mIsOuting = true;
				}
				//�÷��̾Ŭ�����ϰ� �������� ���϶�
				else {
					//�������� �����ش�
					mLeaf[index].mUintTrans += mLeaf[index].mLeafMinFast;

					//x���� 300 ���ϸ� 0,0���� �ʱ�ȭ - 300�� ���� ���� ���������ѰŴ�~
					if (mLeaf[index].mLeafMesh->GetTrans().x < 300) {

						mLeaf[index].mIsComplete = true;//���ٰ� �˸�
						mLeatOutCnt++;//���� ī��Ʈ
						mLeaf[index].mLeafMesh->SetTransX(300);
						mLeaf[index].mUintTrans = D3DXVECTOR2(0, 0);
						mLeaf[index].mLeafMinFast = D3DXVECTOR2(0, 0);
					}
				}
			}


			//Ŭ���� ������!
			if (Mouse::Get()->Up(1) && mLeaf[index].mIsMove == true) {
				mLeaf[index].mIsMove = false;
				mActtiveArrow = false; //ȭ��ǥ �ִ� ����
			}

			if (index == 6) {
				int a = 0;
			}

			//�̵� ���
			mLeaf[index].mLeafMesh->SetPlusTrans(mLeaf[index].mUintTrans); //�������� ����

			//�ε����� ��� ����
			int tempResult = isOut(mLeaf[index].mLeafMesh->GetTrans(), mLeaf[index].mLeafMesh->GetSize());

			//�ε����ٸ� [ 0 �� �ƴ�]
			if (tempResult != 0) {

				//�ϴ� �� ���ְ� �� ����� ��ȣ �ٲ��ش�
				mLeaf[index].mLeafMesh->SetMinTrans(mLeaf[index].mUintTrans);

				//��ȣ �ٲܰǵ� �߿��Ѱ� ������ �پ��� ���� ���� 2���� �ݴ�� �ؾ��� ����������
				//��,�Ʒ� �ε��� -> Y�� ��ȣ �ݴ�
				if (tempResult == 1 || tempResult == 3) {
					mLeaf[index].mUintTrans.y = -mLeaf[index].mUintTrans.y;
					mLeaf[index].mLeafMinFast.y = -mLeaf[index].mLeafMinFast.y;
				}
				//������ �ε��� x�� ��ȣ �ݴ�
				else if (tempResult == 2) {
					mLeaf[index].mUintTrans.x = -mLeaf[index].mUintTrans.x;
					mLeaf[index].mLeafMinFast.x = -mLeaf[index].mLeafMinFast.x;
				}

				//�ٽ��ѹ� �ٲ� ��ȣ�� �̵� ���
				mLeaf[index].mLeafMesh->SetPlusTrans(mLeaf[index].mUintTrans); //�������� ����
			}

			//���� ������Ʈ

			mLeaf[index].mLeafMesh->Update_withCam();
		}


	}

	//7�� ��� ���� ��
	if (mLeatOutCnt == 7) {

		mIsComplete = true;
	}
}

void O2_ClienFilter::renderLeaf()
{
	for (int index = 0; index < 7; index++) {

		//�Ϸ���� ���� �����ٸ� ������Ʈ�Ѵ�
		if (mLeaf[index].mIsComplete == false) {

			mLeaf[index].mLeafMesh->Render();
		}
	}
}

int O2_ClienFilter::isOut(D3DXVECTOR2 leafTrans, D3DXVECTOR2 leafSize)
{
	//���������� �ε����� 2
	if (891 < leafTrans.x + leafSize.x) return 2;

	//�Ʒ��� ������ 3
	else if ((leafTrans.y - leafSize.y) < 111) return 3;

	//���� �ε����� 1
	else if( 611 < (leafTrans.y + leafSize.y)) return 1;

	//�Ⱥε����� 0
	return 0;
}

bool O2_ClienFilter::isLeafClick()
{

	for (int index = 0; index < 7; index++) {

		if (mLeaf[index].mLeafMesh->IsClik_Center() == true) return true;
	}
	return false;
}


