#pragma once
#include "../stdafx.h"

class PlayerMove {

public:

	//캐릭터의 좌표위치와 캐릭터의 크기를 매개변수로 받아 맵과 충돌하는지 확인
	//position은 좌측 하단의 Point이다
	//TODO::나중에 구역나누어서 그 영역의 외곽선에만 충돌 체크하게끔
	//TRUE면 충돌했다는 것, false면 충돌안했으니 정상이라는 뜻
	
	bool MoveDown(D3DXVECTOR2 position, D3DXVECTOR2 size, float guideSize, string areaName) {

		bool result = false;

		//충돌 선분의 각 꼭짓점좌표
		D3DXVECTOR3 lDown = position;
		D3DXVECTOR3 lUp = { position.x , position.y + guideSize , 0};
		D3DXVECTOR3 rDown = { position.x + size.x, position.y, 0};
		D3DXVECTOR3 rUp = { position.x + size.x, position.y + guideSize , 0 };

		//충돌체크할 영역을 키값으로 입력
		vector<vector<D3DXVECTOR3>> tempMapBorder = MapManager::Get()->GetMapBorder(areaName);

		//한구역의 충돌검사 파트가 몇부분인지
		int tempAreaSize = tempMapBorder.size();
		for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

			int tempLineIndexSize = tempMapBorder.at(areaPart).size();
			for (int lineIndex = 0; lineIndex < (tempLineIndexSize - 1); lineIndex++) { //-1하는 이유는 index+1연산이 들어가서임


				//오른쪽으로 움직이니까 오른쪽,상단(충돌렉트에서의 상단),하단(충돌렉트에서의 하단) 에서 충돌체크를 한다
				D3DXVECTOR3 line1 = tempMapBorder.at(areaPart).at(lineIndex);
				D3DXVECTOR3 line2 = tempMapBorder.at(areaPart).at(lineIndex + 1);


				//왼쪽 선분 검사
				if (Collision::Get()->IsLineCollision(lUp, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//오른쪽 선분 검사
				if (Collision::Get()->IsLineCollision(rUp, rDown, line1, line2) == true) {
					result = true;
					break;
				}
				//밑에 선분 검사
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

		//충돌 선분의 각 꼭짓점좌표
		D3DXVECTOR3 lDown = position;
		D3DXVECTOR3 lUp = { position.x , position.y + guideSize , 0 };
		D3DXVECTOR3 rDown = { position.x + size.x, position.y, 0 };
		D3DXVECTOR3 rUp = { position.x + size.x, position.y + guideSize , 0 };

		//충돌체크할 영역을 키값으로 입력
		vector<vector<D3DXVECTOR3>> tempMapBorder = MapManager::Get()->GetMapBorder(areaName);

		//한구역의 충돌검사 파트가 몇부분인지
		int tempAreaSize = tempMapBorder.size();
		for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

			int tempLineIndexSize = tempMapBorder.at(areaPart).size();
			for (int lineIndex = 0; lineIndex < (tempLineIndexSize - 1); lineIndex++) { //-1하는 이유는 index+1연산이 들어가서임


				//오른쪽으로 움직이니까 오른쪽,상단(충돌렉트에서의 상단),하단(충돌렉트에서의 하단) 에서 충돌체크를 한다
				D3DXVECTOR3 line1 = tempMapBorder.at(areaPart).at(lineIndex);
				D3DXVECTOR3 line2 = tempMapBorder.at(areaPart).at(lineIndex + 1);


				//왼쪽 선분 검사
				if (Collision::Get()->IsLineCollision(lUp, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//오른쪽 선분 검사
				if (Collision::Get()->IsLineCollision(rUp, rDown, line1, line2) == true) {
					result = true;
					break;
				}
				//위에 선분 검사
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

		//충돌 선분의 각 꼭짓점좌표
		D3DXVECTOR3 lDown = position;
		D3DXVECTOR3 lUp = { position.x , position.y + guideSize , 0 };
		D3DXVECTOR3 rDown = { position.x + size.x, position.y, 0 };
		D3DXVECTOR3 rUp = { position.x + size.x, position.y + guideSize , 0 };

		//충돌체크할 영역을 키값으로 입력
		vector<vector<D3DXVECTOR3>> tempMapBorder = MapManager::Get()->GetMapBorder(areaName);

		//한구역의 충돌검사 파트가 몇부분인지
		int tempAreaSize = tempMapBorder.size();
		for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

			int tempLineIndexSize = tempMapBorder.at(areaPart).size();
			for (int lineIndex = 0; lineIndex < (tempLineIndexSize - 1); lineIndex++) { //-1하는 이유는 index+1연산이 들어가서임


				//오른쪽으로 움직이니까 오른쪽,상단(충돌렉트에서의 상단),하단(충돌렉트에서의 하단) 에서 충돌체크를 한다
				D3DXVECTOR3 line1 = tempMapBorder.at(areaPart).at(lineIndex);
				D3DXVECTOR3 line2 = tempMapBorder.at(areaPart).at(lineIndex + 1);


				//왼쪽 선분 검사
				if (Collision::Get()->IsLineCollision(lUp, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//밑에 선분 검사
				if (Collision::Get()->IsLineCollision(rDown, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//위에 선분 검사
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

		//충돌 선분의 각 꼭짓점좌표
		D3DXVECTOR3 lDown = position;
		D3DXVECTOR3 lUp = { position.x , position.y + guideSize , 0 };
		D3DXVECTOR3 rDown = { position.x + size.x, position.y, 0 };
		D3DXVECTOR3 rUp = { position.x + size.x, position.y + guideSize , 0 };

		//충돌체크할 영역을 키값으로 입력
		vector<vector<D3DXVECTOR3>> tempMapBorder = MapManager::Get()->GetMapBorder(areaName);

		//한구역의 충돌검사 파트가 몇부분인지
		int tempAreaSize = tempMapBorder.size();
		for (int areaPart = 0; areaPart < tempAreaSize; areaPart++) {

			int tempLineIndexSize = tempMapBorder.at(areaPart).size();
			for (int lineIndex = 0; lineIndex < (tempLineIndexSize-1); lineIndex++) { //-1하는 이유는 index+1연산이 들어가서임


				//오른쪽으로 움직이니까 오른쪽,상단(충돌렉트에서의 상단),하단(충돌렉트에서의 하단) 에서 충돌체크를 한다
				D3DXVECTOR3 line1 = tempMapBorder.at(areaPart).at(lineIndex);
				D3DXVECTOR3 line2 = tempMapBorder.at(areaPart).at(lineIndex+1);


				//오른쪽 선분 검사
				if (Collision::Get()->IsLineCollision(rUp, rDown, line1, line2) == true) {
					result = true;
					break;
				}
				//밑에 선분 검사
				if (Collision::Get()->IsLineCollision(rDown, lDown, line1, line2) == true) {
					result = true;
					break;
				}
				//위에 선분 검사
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