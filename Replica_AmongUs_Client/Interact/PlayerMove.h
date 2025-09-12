#pragma once
#include "../stdafx.h"

class PlayerMove {

public:

	//ĳ������ ��ǥ��ġ�� ĳ������ ũ�⸦ �Ű������� �޾� �ʰ� �浹�ϴ��� Ȯ��
	//position�� ���� �ϴ��� Point�̴�
	//TODO::���߿� ��������� �� ������ �ܰ������� �浹 üũ�ϰԲ�
	//TRUE�� �浹�ߴٴ� ��, false�� �浹�������� �����̶�� ��
	
	bool MoveDown(D3DXVECTOR2 position, D3DXVECTOR2 size, float guideSize, string areaName) {

		bool result = false;

		//�浹 ������ �� ��������ǥ
		D3DXVECTOR3 lDown = position;
		D3DXVECTOR3 lUp = { position.x , position.y + guideSize , 0};
		D3DXVECTOR3 rDown = { position.x + size.x, position.y, 0};
		D3DXVECTOR3 rUp = { position.x + size.x, position.y + guideSize , 0 };

		//�浹üũ�� ������ Ű������ �Է�
		vector<vector<D3DXVECTOR3>> tempMapBorder = MapManager::Get()->GetMapBorder(areaName);

		//�ѱ����� �浹�˻� ��Ʈ�� ��κ�����
		int tempAreaSize = tempMapBorder.size();
		for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

			int tempLineIndexSize = tempMapBorder.at(areaPart).size();
			for (int lineIndex = 0; lineIndex < (tempLineIndexSize - 1); lineIndex++) { //-1�ϴ� ������ index+1������ ������


				//���������� �����̴ϱ� ������,���(�浹��Ʈ������ ���),�ϴ�(�浹��Ʈ������ �ϴ�) ���� �浹üũ�� �Ѵ�
				D3DXVECTOR3 line1 = tempMapBorder.at(areaPart).at(lineIndex);
				D3DXVECTOR3 line2 = tempMapBorder.at(areaPart).at(lineIndex + 1);


				//���� ���� �˻�
				if (Collision::Get()->IsLineCollision(lUp, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//������ ���� �˻�
				if (Collision::Get()->IsLineCollision(rUp, rDown, line1, line2) == true) {
					result = true;
					break;
				}
				//�ؿ� ���� �˻�
				if (Collision::Get()->IsLineCollision(rDown, lDown, line1, line2) == true) {
					result = true;
					break;
				}
			}
		}

		return result;
	}

	bool MoveUp(D3DXVECTOR2 position, D3DXVECTOR2 size, float guideSize, string areaName) {

		bool result = false;

		//�浹 ������ �� ��������ǥ
		D3DXVECTOR3 lDown = position;
		D3DXVECTOR3 lUp = { position.x , position.y + guideSize , 0 };
		D3DXVECTOR3 rDown = { position.x + size.x, position.y, 0 };
		D3DXVECTOR3 rUp = { position.x + size.x, position.y + guideSize , 0 };

		//�浹üũ�� ������ Ű������ �Է�
		vector<vector<D3DXVECTOR3>> tempMapBorder = MapManager::Get()->GetMapBorder(areaName);

		//�ѱ����� �浹�˻� ��Ʈ�� ��κ�����
		int tempAreaSize = tempMapBorder.size();
		for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

			int tempLineIndexSize = tempMapBorder.at(areaPart).size();
			for (int lineIndex = 0; lineIndex < (tempLineIndexSize - 1); lineIndex++) { //-1�ϴ� ������ index+1������ ������


				//���������� �����̴ϱ� ������,���(�浹��Ʈ������ ���),�ϴ�(�浹��Ʈ������ �ϴ�) ���� �浹üũ�� �Ѵ�
				D3DXVECTOR3 line1 = tempMapBorder.at(areaPart).at(lineIndex);
				D3DXVECTOR3 line2 = tempMapBorder.at(areaPart).at(lineIndex + 1);


				//���� ���� �˻�
				if (Collision::Get()->IsLineCollision(lUp, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//������ ���� �˻�
				if (Collision::Get()->IsLineCollision(rUp, rDown, line1, line2) == true) {
					result = true;
					break;
				}
				//���� ���� �˻�
				if (Collision::Get()->IsLineCollision(rUp, lUp, line1, line2) == true) {
					result = true;
					break;
				}
			}
		}

		return result;
	}
	
	bool MoveLeft(D3DXVECTOR2 position, D3DXVECTOR2 size, float guideSize, string areaName) {

		bool result = false;

		//�浹 ������ �� ��������ǥ
		D3DXVECTOR3 lDown = position;
		D3DXVECTOR3 lUp = { position.x , position.y + guideSize , 0 };
		D3DXVECTOR3 rDown = { position.x + size.x, position.y, 0 };
		D3DXVECTOR3 rUp = { position.x + size.x, position.y + guideSize , 0 };

		//�浹üũ�� ������ Ű������ �Է�
		vector<vector<D3DXVECTOR3>> tempMapBorder = MapManager::Get()->GetMapBorder(areaName);

		//�ѱ����� �浹�˻� ��Ʈ�� ��κ�����
		int tempAreaSize = tempMapBorder.size();
		for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

			int tempLineIndexSize = tempMapBorder.at(areaPart).size();
			for (int lineIndex = 0; lineIndex < (tempLineIndexSize - 1); lineIndex++) { //-1�ϴ� ������ index+1������ ������


				//���������� �����̴ϱ� ������,���(�浹��Ʈ������ ���),�ϴ�(�浹��Ʈ������ �ϴ�) ���� �浹üũ�� �Ѵ�
				D3DXVECTOR3 line1 = tempMapBorder.at(areaPart).at(lineIndex);
				D3DXVECTOR3 line2 = tempMapBorder.at(areaPart).at(lineIndex + 1);


				//���� ���� �˻�
				if (Collision::Get()->IsLineCollision(lUp, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//�ؿ� ���� �˻�
				if (Collision::Get()->IsLineCollision(rDown, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//���� ���� �˻�
				if (Collision::Get()->IsLineCollision(rUp, lUp, line1, line2) == true) {
					result = true;
					break;
				}
			}
		}

		return result;
	}
	
	bool MoveRight(D3DXVECTOR2 position, D3DXVECTOR2 size, float guideSize, string areaName) {

		bool result = false;

		//�浹 ������ �� ��������ǥ
		D3DXVECTOR3 lDown = position;
		D3DXVECTOR3 lUp = { position.x , position.y + guideSize , 0 };
		D3DXVECTOR3 rDown = { position.x + size.x, position.y, 0 };
		D3DXVECTOR3 rUp = { position.x + size.x, position.y + guideSize , 0 };

		//�浹üũ�� ������ Ű������ �Է�
		vector<vector<D3DXVECTOR3>> tempMapBorder = MapManager::Get()->GetMapBorder(areaName);

		//�ѱ����� �浹�˻� ��Ʈ�� ��κ�����
		int tempAreaSize = tempMapBorder.size();
		for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

			int tempLineIndexSize = tempMapBorder.at(areaPart).size();
			for (int lineIndex = 0; lineIndex < (tempLineIndexSize-1); lineIndex++) { //-1�ϴ� ������ index+1������ ������


				//���������� �����̴ϱ� ������,���(�浹��Ʈ������ ���),�ϴ�(�浹��Ʈ������ �ϴ�) ���� �浹üũ�� �Ѵ�
				D3DXVECTOR3 line1 = tempMapBorder.at(areaPart).at(lineIndex);
				D3DXVECTOR3 line2 = tempMapBorder.at(areaPart).at(lineIndex+1);


				//������ ���� �˻�
				if (Collision::Get()->IsLineCollision(rUp, rDown, line1, line2) == true) {
					result = true;
					break;
				}
				//�ؿ� ���� �˻�
				if (Collision::Get()->IsLineCollision(rDown, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//���� ���� �˻�
				if (Collision::Get()->IsLineCollision(rUp, lUp, line1, line2) == true) {
					result = true;
					break;
				}
			}
		}

		return result;
	}

private:


};