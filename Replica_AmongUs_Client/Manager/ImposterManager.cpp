#include "../stdafx.h"
#include "PlayerManager.h"
#include "UiManager.h"
#include "ImposterManager.h"

void ImposterManager::Update_Last()
{
	//Kill�� �ߴ°�?
	if (UiManager::Get()->GetIsSlot1Click() == true) {
		
		//�̰� �����÷��̾� �ε�����
		//mIsPossibleKill

		//ų �ִϸ��̼� ���� �Ѿ
		PlayerManager::Get()->SetMyIsKilling(true);

		ClientData::Get()->mWhoIKilled = GetNearCrewIndex();

		//�׿��ٰ� �˸�
		mIsKill = true;
	}
}

int ImposterManager::GetNearCrewIndex()
{

	//////////////////////////////////////////////////////////////////
	//���� : �ϴ� �÷��̾� �߽����� ���Ѵ�
	//////////////////////////////////////////////////////////////////
	D3DXVECTOR2 tempMyTrans = PlayerManager::Get()->GetMyTrans();
	D3DXVECTOR2 tempMySize = PlayerManager::Get()->GetMySize();
	D3DXVECTOR2 tempMyHalfSize = { tempMySize.x / 2 , tempMySize.y / 2 }; //�� �Ÿ�
	D3DXVECTOR2 tempMyPlayerCenter = { tempMyTrans.x + tempMyHalfSize.x, tempMyTrans.y + tempMyHalfSize.y };

	//�� �ٸ� "ũ��"���� �Ÿ��� ����Ʈ�� ��´�
	float nearList[4];
	bool isNear = false; //����� ũ����� �ִ���?

	//��� �÷��̾ �˻��Ѵ� / 4�� ������ �ο�
	for (UINT index = 0; index < 4; index++) {

		//test
		if (Mouse::Get()->Down(1)) {
			int a = 0;
		}
		
		//�ڴٸ� �ڽŰ��� �Ÿ��� �ʿ���� && �������Ͱ� �ƴϾ���Ѵ� && �����͵� �ƴϾ���Ѵ�
		if (index != ClientData::Get()->mPlayerNum && ClientData::Get()->mImposterList[index] == false
			&& ClientData::Get()->mAnotherPlayer_inGame[index].mIsDieSecond == false) {

			//������ �߽����� ����
			D3DXVECTOR2 tempAnotherPlayerCenter = ClientData::Get()->mAnotherPlayer_inGame[index].mPos;
			tempAnotherPlayerCenter.x += tempMyHalfSize.x;
			tempAnotherPlayerCenter.y += tempMyHalfSize.y;

			//�ڽ��� ������ �ٸ� ũ���[���]�� �ڽ���[����] �Ÿ��� ���Ѵ�
			float tempDestance = GetVectorLength(tempAnotherPlayerCenter, tempMyPlayerCenter);

			//�ذŸ��� �ּ� �Ÿ� �� ������
			if (tempDestance < mMinLegth) {

				nearList[index] = tempDestance;
				isNear = true;
			}
			//�ذŸ��� �ּ� �Ÿ��� ������ ������
			else {

				nearList[index] = 9999;
			}
		}
		//���ڽ��̳� ���������� �Ÿ� ����
		else {
			nearList[index] = 9999;
		}
	}

	//���� ����� ũ����� �ִٸ�
	if (isNear == true) {

		int tempIndex = -1; //�÷��̾� �ε����� ���� ����
		float tempMin = 9999; //�ݺ������ϸ鼭 �ּҰ��� ��Ӵ��� ����
		//����Ʈ�� ����� ���� ���� ���� ����� �÷��̾� �ε����� ã�Ƴ���
		for (int index = 0; index < 4; index++) {

			//�񱳴���� �ּҰ����� �۴ٸ�
			if (nearList[index] < tempMin) {

				//�� ������Ʈ
				tempIndex = index;
				tempMin = nearList[index];
			}
		}

		mIsPossibleKill = tempIndex; //�� ����
		return tempIndex;
	}

	mIsPossibleKill = -1; //�� ����
	return -1;
}

void ImposterManager::Setting()
{

	switch (SceneManager::Get()->GetScene())
	{
	case SCENE_INGAME_END: {

		mIsPossibleKill = -1;
		mIsKill = false;
	} break;
	default:
		break;
	}
	
}

ImposterManager::ImposterManager()
{
	init();
}

ImposterManager::~ImposterManager()
{
}

void ImposterManager::init()
{
	mMinLegth = 220.0f;
	mIsPossibleKill = -1;
	mIsKill = false;
}

