#pragma once
#include "../stdafx.h"

struct NodeData {

	NodeData() {

		x = 0;
		y = 0;

		isObstacle = false;
		isRoad = false;
		state = 0;

		G = 0;
		H = 0;
		F = 0;

		parentX = 0;
		parentY = 0;
	}

	//장애물인가?
	bool isObstacle;

	//최종 경로에 들어가는 타일 인가?
	bool isRoad;

	//-1 close, 0 아무것도 속해있지 않음 , 1 open
	int state;

	//가로, 세로 위치
	int x, y;


	int G; //Start에서부터 경로 거리
	int H; // End에서의 일직선 거리
	int F; //G, H 합

	//부모의 가로, 세로 위치
	int parentX, parentY;
};

//리스트를 F를 기준으로 작은순으로 0부터 정렬한다
bool static Comping(const NodeData lhs, const NodeData rhs) {
	return lhs.F < rhs.F;
};

class Astar {

public:

	NodeData mAllTile[16][9];

	list<NodeData> mOpenList;
	list<NodeData> mCloseList;

	list<NodeData> mFinalList;

	NodeData * mMainNode;
	NodeData mStartNode;
	NodeData mEndNode;


	int mRow = 16;
	int mColunm = 9;

	//false면 실패, true면 성공
	bool isSuccess;


public:

	Astar() {

		for (int i = 0; i < mRow; i++) {

			for (int j = 0; j < mColunm; j++) {

				mAllTile[i][j] = NodeData();

				mAllTile[i][j].x = i;
				mAllTile[i][j].y = j;
			}
		}
	}


	void Init() {

		for (int i = 0; i < mRow; i++) {

			for (int j = 0; j < mColunm; j++) {

				if (mAllTile[i][j].isObstacle == true) {

					mAllTile[i][j] = NodeData();

					mAllTile[i][j].x = i;
					mAllTile[i][j].y = j;

					mAllTile[i][j].isObstacle = true;
				}
				else {

					mAllTile[i][j] = NodeData();

					mAllTile[i][j].x = i;
					mAllTile[i][j].y = j;
				}
				
			}
		}

		//결과값 초기화
		isSuccess = false;

		//리스트 초기화
		mOpenList.clear();
		mCloseList.clear();
		mFinalList.clear();
	}


	void SetStartNode(NodeData * startNode, NodeData * endNode) {

		//먼저 시작노드를 Open리스트에 삽입
		mOpenList.push_back(*startNode);

		//시작노드, 도착노드, 메인노드 세팅
		mMainNode = startNode;

		mStartNode = *startNode;
		mEndNode = *endNode;
	}


	//4가지 방향을 탐색 (동서남북)
	bool GetNeighbor(NodeData & mainNode) {

		
		/*
		이웃의 노드가 있는지 확인
		[5][6][7]
		[3][ ][4]
		[0][1][2]
		각 인덱스는 위 방향을 의미함
		*/
		bool isMove[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };


		//메인노드가 맨 왼쪽에 있어서 왼쪽부분 노드는 존재하지 않음
		if (mainNode.x == 0) {
			isMove[0] = false;
			isMove[3] = false;
			isMove[5] = false;
		}
		//메인노드가 맨 위에 있다면 위쪽 부분 노드는 존재하지 않음
		if (mainNode.y == (mColunm - 1)) {
			isMove[5] = false;
			isMove[6] = false;
			isMove[7] = false;
		}
		//메인노드가 맨 오른쪽에 있어서 오른쪽부분 노드는 존재하지 않음
		if (mainNode.x == (mRow - 1)) {
			isMove[7] = false;
			isMove[4] = false;
			isMove[2] = false;
		}
		//메인노드가 맨 밑쪽에 있어서 밑쪽부분 노드는 존재하지 않음
		if (mainNode.y == 0) {
			isMove[0] = false;
			isMove[1] = false;
			isMove[2] = false;
		}



		//대각선 유효한지 검사(양 방향으로 하나라도 안막혀있을 시에)
		/*
		[ ][2][ ]
		[1][ ][3]
		[ ][0][ ]
		*/
		bool isAble[4] = { 0, 0, 0, 0 };

		//하단이 존재하고 장애물이 아니면 가능
		if (isMove[1] == true) {
			if( mAllTile[mainNode.x][mainNode.y - 1].isObstacle == false) isAble[0] = true;
		}
		//좌측이 존재하고 장애물이 아니면 가능
		if (isMove[3] == true) {
			if (mAllTile[mainNode.x - 1][mainNode.y].isObstacle == false) isAble[1] = true;
		}
		//상단이 존재하고 장애물이 아니면 가능
		if (isMove[6] == true) {
			if (mAllTile[mainNode.x][mainNode.y + 1].isObstacle == false) isAble[2] = true;
		}
		//우측이 존재하고 장애물이 아니면 가능
		if (isMove[4] == true) {
			if (mAllTile[mainNode.x + 1][mainNode.y].isObstacle == false) isAble[3] = true;
		}


		//좌측하단 탐색 , 좌측과 하단이 막혀있지 않아야함
		if (isMove[0] == true && (isAble[1] == true || isAble[0] == true)) {if (DoSearch(mainNode.x - 1, mainNode.y - 1, true) == true) return true;		}
		//좌측 탐색
		if (isMove[3] == true) { if (DoSearch(mainNode.x - 1, mainNode.y, false) == true) return true; }


		//좌측상단 탐색
		if (isMove[5] == true && (isAble[1] == true || isAble[2] == true)) { if (DoSearch(mainNode.x - 1, mainNode.y + 1, true) == true) return true; }
		//상단 탐색
		if (isMove[6] == true) { if (DoSearch(mainNode.x, mainNode.y + 1, false) == true) return true; }


		//우측상단 탐색
		if (isMove[7] == true && (isAble[2] == true || isAble[3] == true)) { if (DoSearch(mainNode.x + 1, mainNode.y + 1, true) == true) return true; }
		//우측 탐색
		if (isMove[4] == true) { if (DoSearch(mainNode.x + 1, mainNode.y, false) == true) return true; }


		//우측 하단 탐색
		if (isMove[2] == true && (isAble[3] == true || isAble[0] == true)) { if (DoSearch(mainNode.x + 1, mainNode.y - 1, true) == true) return true; }
		//하단 탐색
		if (isMove[1] == true) { if (DoSearch(mainNode.x, mainNode.y - 1, false) == true) return true; }

		return false;
	};

	//방향을 탐색할때 오픈에 삽입 함
	//매개변수	1,2 - "검색할 이웃"의 타일의 좌표를 받아 총타일의 좌표에들어가 값을 변경
	//			3 - 기준노드로부터 대각선인지 아닌지
	bool DoSearch(int searchNodeX, int searchNodeY, bool isDiagonal) {

		NodeData & tempNode = mAllTile[searchNodeX][searchNodeY];

		//이미 EndList에 속해 있거나 장애물일때 패스
		if (tempNode.state == -1 || tempNode.isObstacle == true) return false;


		//아무것도 안 속해 있을 때
		else if (tempNode.state == 0) {


			//부모좌표를 현재 메인노드의 좌표로 대입
			tempNode.parentX = mMainNode->x;
			tempNode.parentY = mMainNode->y;


			//탐색노드가 도착노드의 좌표와 같다면 종료────────────────────────────────────────────────────────────────★★★
			if (tempNode.x == mEndNode.x && tempNode.y == mEndNode.y) { 
				//성공했다고 스위치 켜고
				isSuccess = true;
				//도착노드에 부모 업데이트하고 종료
				mEndNode = tempNode;
				return true; 
			}


			//기준좌표로부터 사방에있을경우  (대각선X)
			if (isDiagonal == false) {
				//G설정  - 현재 메인노드의 G로부터 가중치 더해 대입
				tempNode.G = mMainNode->G + 10;
			}
			//기준좌표로부터 대각선일 경우
			else {
				tempNode.G = mMainNode->G + 14;
			}


			//H 설정
			int HsizeX = mEndNode.x - tempNode.x;
			if (HsizeX < 0) HsizeX = -HsizeX; // 차이가 음수로 나오면 양수로 바꿔준다
			int HsizeY = mEndNode.y - tempNode.y;
			if (HsizeY < 0) HsizeY = -HsizeY; // 차이가 음수로 나오면 양수로 바꿔준다
			tempNode.H = (HsizeX + HsizeY) * 10; //총 차이만큼 10의 가중치를 곱한다(대각선의 경우는 없음


			//F설정
			tempNode.F = tempNode.G + tempNode.H;


			//모든 수를 업데이트 했으니 마지막으로 OpenList에 삽입
			tempNode.state = 1;
			mOpenList.push_back(tempNode);
		}


		//이미 open에 속해 있을 때
		else if (tempNode.state == 1) {


			//비교대상이 사방에 있을 경우 (대각선X)
			if (isDiagonal == false) {

				//G를 비교했을 때 현재경로에서가 더 최적화면
				if (tempNode.G > mMainNode->G + 10) {

					//메인노드를 기준으로 G,F 값을 업데이트한다 [ H값은 어디든 값이 바뀌지 않으니까 변경할 필요 X ]
					tempNode.G = mMainNode->G + 10;
					tempNode.F = tempNode.H + tempNode.G;

					//부모노드의 좌표를 메인노드의 좌표로 업데이트
					tempNode.parentX = mMainNode->x;
					tempNode.parentY = mMainNode->y;
				}
			}
			//비교대상이 대각선일 경우
			else {

				//G를 비교했을 때 현재경로에서가 더 최적화면
				if (tempNode.G > mMainNode->G + 14) {

					//메인노드를 기준으로 G,F 값을 업데이트한다 [ H값은 어디든 값이 바뀌지 않으니까 변경할 필요 X ]
					tempNode.G = mMainNode->G + 14;
					tempNode.F = tempNode.H + tempNode.G;

					//부모노드의 좌표를 메인노드의 좌표로 업데이트
					tempNode.parentX = mMainNode->x;
					tempNode.parentY = mMainNode->y;
				}
			}


		}

		return false;
	}
	

	bool StartAstar(int startNodeX, int startNodeY, int endNodeX, int endNodeY) {

		//값 초기화
		Init();

		//같은 타일이면 계산할 필요 없이 종료
		if (startNodeX == endNodeX && startNodeY == endNodeY) return false;

		//1. 시작, 도착노트 세팅후 시작노드를 메인노드로 지정한다
		SetStartNode(&mAllTile[startNodeX][startNodeY], &mAllTile[endNodeX][endNodeY]);

		do {

			//2. 주변 이웃의 노드를 탐색하고 업데이트한다. [ 검색시 도착 노드나오면 종료 ]─────────────────────★★★
			if (GetNeighbor(*mMainNode) == true) break;

			//3. 메인노드를 Close리스트로 세팅한다
			mMainNode->state = -1;


			//4. open리스트에 하나라도 있으면 메인노드를 open에서 제거한다 [메인노드는 항상 맨 앞에 있다]
			if (mOpenList.size() > 0)
				mOpenList.pop_front();


			//5. open리스트를 F를 비교하여 정렬한다
			if (mOpenList.size() > 0)
			mOpenList.sort(Comping);
			

			//6 open리스트에 아무것도 없다면 종료한다───────────────────────────────────────────────────────★★★
			if (mOpenList.size() == 0) break;
			else 

			//7. open리스트중 가장F가 낮은 노드를 꺼내 메인 노드로 지정한다 [ 이미 정렬되어서 마지막걸 꺼내면 됨 ]
			mMainNode = &mOpenList.front();

		} while (1);

		if (isSuccess == true) { 
			PushFinalList(mEndNode.x, mEndNode.y);
			return true; 
		}
		else return false;
	}


	//true면 끝내는것, false면 계속
	void PushFinalList(int x, int y) {

		//일단 노드 리스트에 넣고
		mAllTile[x][y].isRoad = true;
		
		//넣은 노드가 시작 노드라면
		if (mAllTile[x][y].x == mStartNode.x && mAllTile[x][y].y == mStartNode.y) {

			return;
		}
		//시작점 노드가 아니면
		else {
			PushFinalList(mAllTile[x][y].parentX, mAllTile[x][y].parentY);
		}

		return;
	}
	
	//장애물 스위치 켜기
	void SetObstacle(int x, int y) {

		mAllTile[x][y].isObstacle = !mAllTile[x][y].isObstacle;
	}
};

