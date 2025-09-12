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

	//��ֹ��ΰ�?
	bool isObstacle;

	//���� ��ο� ���� Ÿ�� �ΰ�?
	bool isRoad;

	//-1 close, 0 �ƹ��͵� �������� ���� , 1 open
	int state;

	//����, ���� ��ġ
	int x, y;


	int G; //Start�������� ��� �Ÿ�
	int H; // End������ ������ �Ÿ�
	int F; //G, H ��

	//�θ��� ����, ���� ��ġ
	int parentX, parentY;
};

//����Ʈ�� F�� �������� ���������� 0���� �����Ѵ�
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

	//false�� ����, true�� ����
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

		//����� �ʱ�ȭ
		isSuccess = false;

		//����Ʈ �ʱ�ȭ
		mOpenList.clear();
		mCloseList.clear();
		mFinalList.clear();
	}


	void SetStartNode(NodeData * startNode, NodeData * endNode) {

		//���� ���۳�带 Open����Ʈ�� ����
		mOpenList.push_back(*startNode);

		//���۳��, �������, ���γ�� ����
		mMainNode = startNode;

		mStartNode = *startNode;
		mEndNode = *endNode;
	}


	//4���� ������ Ž�� (��������)
	bool GetNeighbor(NodeData & mainNode) {

		
		/*
		�̿��� ��尡 �ִ��� Ȯ��
		[5][6][7]
		[3][ ][4]
		[0][1][2]
		�� �ε����� �� ������ �ǹ���
		*/
		bool isMove[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };


		//���γ�尡 �� ���ʿ� �־ ���ʺκ� ���� �������� ����
		if (mainNode.x == 0) {
			isMove[0] = false;
			isMove[3] = false;
			isMove[5] = false;
		}
		//���γ�尡 �� ���� �ִٸ� ���� �κ� ���� �������� ����
		if (mainNode.y == (mColunm - 1)) {
			isMove[5] = false;
			isMove[6] = false;
			isMove[7] = false;
		}
		//���γ�尡 �� �����ʿ� �־ �����ʺκ� ���� �������� ����
		if (mainNode.x == (mRow - 1)) {
			isMove[7] = false;
			isMove[4] = false;
			isMove[2] = false;
		}
		//���γ�尡 �� ���ʿ� �־ ���ʺκ� ���� �������� ����
		if (mainNode.y == 0) {
			isMove[0] = false;
			isMove[1] = false;
			isMove[2] = false;
		}



		//�밢�� ��ȿ���� �˻�(�� �������� �ϳ��� �ȸ������� �ÿ�)
		/*
		[ ][2][ ]
		[1][ ][3]
		[ ][0][ ]
		*/
		bool isAble[4] = { 0, 0, 0, 0 };

		//�ϴ��� �����ϰ� ��ֹ��� �ƴϸ� ����
		if (isMove[1] == true) {
			if( mAllTile[mainNode.x][mainNode.y - 1].isObstacle == false) isAble[0] = true;
		}
		//������ �����ϰ� ��ֹ��� �ƴϸ� ����
		if (isMove[3] == true) {
			if (mAllTile[mainNode.x - 1][mainNode.y].isObstacle == false) isAble[1] = true;
		}
		//����� �����ϰ� ��ֹ��� �ƴϸ� ����
		if (isMove[6] == true) {
			if (mAllTile[mainNode.x][mainNode.y + 1].isObstacle == false) isAble[2] = true;
		}
		//������ �����ϰ� ��ֹ��� �ƴϸ� ����
		if (isMove[4] == true) {
			if (mAllTile[mainNode.x + 1][mainNode.y].isObstacle == false) isAble[3] = true;
		}


		//�����ϴ� Ž�� , ������ �ϴ��� �������� �ʾƾ���
		if (isMove[0] == true && (isAble[1] == true || isAble[0] == true)) {if (DoSearch(mainNode.x - 1, mainNode.y - 1, true) == true) return true;		}
		//���� Ž��
		if (isMove[3] == true) { if (DoSearch(mainNode.x - 1, mainNode.y, false) == true) return true; }


		//������� Ž��
		if (isMove[5] == true && (isAble[1] == true || isAble[2] == true)) { if (DoSearch(mainNode.x - 1, mainNode.y + 1, true) == true) return true; }
		//��� Ž��
		if (isMove[6] == true) { if (DoSearch(mainNode.x, mainNode.y + 1, false) == true) return true; }


		//������� Ž��
		if (isMove[7] == true && (isAble[2] == true || isAble[3] == true)) { if (DoSearch(mainNode.x + 1, mainNode.y + 1, true) == true) return true; }
		//���� Ž��
		if (isMove[4] == true) { if (DoSearch(mainNode.x + 1, mainNode.y, false) == true) return true; }


		//���� �ϴ� Ž��
		if (isMove[2] == true && (isAble[3] == true || isAble[0] == true)) { if (DoSearch(mainNode.x + 1, mainNode.y - 1, true) == true) return true; }
		//�ϴ� Ž��
		if (isMove[1] == true) { if (DoSearch(mainNode.x, mainNode.y - 1, false) == true) return true; }

		return false;
	};

	//������ Ž���Ҷ� ���¿� ���� ��
	//�Ű�����	1,2 - "�˻��� �̿�"�� Ÿ���� ��ǥ�� �޾� ��Ÿ���� ��ǥ���� ���� ����
	//			3 - ���س��κ��� �밢������ �ƴ���
	bool DoSearch(int searchNodeX, int searchNodeY, bool isDiagonal) {

		NodeData & tempNode = mAllTile[searchNodeX][searchNodeY];

		//�̹� EndList�� ���� �ְų� ��ֹ��϶� �н�
		if (tempNode.state == -1 || tempNode.isObstacle == true) return false;


		//�ƹ��͵� �� ���� ���� ��
		else if (tempNode.state == 0) {


			//�θ���ǥ�� ���� ���γ���� ��ǥ�� ����
			tempNode.parentX = mMainNode->x;
			tempNode.parentY = mMainNode->y;


			//Ž����尡 ��������� ��ǥ�� ���ٸ� ���ᦡ�������������������������������������������������������������������������������������������������������������������������������ڡڡ�
			if (tempNode.x == mEndNode.x && tempNode.y == mEndNode.y) { 
				//�����ߴٰ� ����ġ �Ѱ�
				isSuccess = true;
				//������忡 �θ� ������Ʈ�ϰ� ����
				mEndNode = tempNode;
				return true; 
			}


			//������ǥ�κ��� ��濡�������  (�밢��X)
			if (isDiagonal == false) {
				//G����  - ���� ���γ���� G�κ��� ����ġ ���� ����
				tempNode.G = mMainNode->G + 10;
			}
			//������ǥ�κ��� �밢���� ���
			else {
				tempNode.G = mMainNode->G + 14;
			}


			//H ����
			int HsizeX = mEndNode.x - tempNode.x;
			if (HsizeX < 0) HsizeX = -HsizeX; // ���̰� ������ ������ ����� �ٲ��ش�
			int HsizeY = mEndNode.y - tempNode.y;
			if (HsizeY < 0) HsizeY = -HsizeY; // ���̰� ������ ������ ����� �ٲ��ش�
			tempNode.H = (HsizeX + HsizeY) * 10; //�� ���̸�ŭ 10�� ����ġ�� ���Ѵ�(�밢���� ���� ����


			//F����
			tempNode.F = tempNode.G + tempNode.H;


			//��� ���� ������Ʈ ������ ���������� OpenList�� ����
			tempNode.state = 1;
			mOpenList.push_back(tempNode);
		}


		//�̹� open�� ���� ���� ��
		else if (tempNode.state == 1) {


			//�񱳴���� ��濡 ���� ��� (�밢��X)
			if (isDiagonal == false) {

				//G�� ������ �� �����ο����� �� ����ȭ��
				if (tempNode.G > mMainNode->G + 10) {

					//���γ�带 �������� G,F ���� ������Ʈ�Ѵ� [ H���� ���� ���� �ٲ��� �����ϱ� ������ �ʿ� X ]
					tempNode.G = mMainNode->G + 10;
					tempNode.F = tempNode.H + tempNode.G;

					//�θ����� ��ǥ�� ���γ���� ��ǥ�� ������Ʈ
					tempNode.parentX = mMainNode->x;
					tempNode.parentY = mMainNode->y;
				}
			}
			//�񱳴���� �밢���� ���
			else {

				//G�� ������ �� �����ο����� �� ����ȭ��
				if (tempNode.G > mMainNode->G + 14) {

					//���γ�带 �������� G,F ���� ������Ʈ�Ѵ� [ H���� ���� ���� �ٲ��� �����ϱ� ������ �ʿ� X ]
					tempNode.G = mMainNode->G + 14;
					tempNode.F = tempNode.H + tempNode.G;

					//�θ����� ��ǥ�� ���γ���� ��ǥ�� ������Ʈ
					tempNode.parentX = mMainNode->x;
					tempNode.parentY = mMainNode->y;
				}
			}


		}

		return false;
	}
	

	bool StartAstar(int startNodeX, int startNodeY, int endNodeX, int endNodeY) {

		//�� �ʱ�ȭ
		Init();

		//���� Ÿ���̸� ����� �ʿ� ���� ����
		if (startNodeX == endNodeX && startNodeY == endNodeY) return false;

		//1. ����, ������Ʈ ������ ���۳�带 ���γ��� �����Ѵ�
		SetStartNode(&mAllTile[startNodeX][startNodeY], &mAllTile[endNodeX][endNodeY]);

		do {

			//2. �ֺ� �̿��� ��带 Ž���ϰ� ������Ʈ�Ѵ�. [ �˻��� ���� ��峪���� ���� ]�������������������������������������������ڡڡ�
			if (GetNeighbor(*mMainNode) == true) break;

			//3. ���γ�带 Close����Ʈ�� �����Ѵ�
			mMainNode->state = -1;


			//4. open����Ʈ�� �ϳ��� ������ ���γ�带 open���� �����Ѵ� [���γ��� �׻� �� �տ� �ִ�]
			if (mOpenList.size() > 0)
				mOpenList.pop_front();


			//5. open����Ʈ�� F�� ���Ͽ� �����Ѵ�
			if (mOpenList.size() > 0)
			mOpenList.sort(Comping);
			

			//6 open����Ʈ�� �ƹ��͵� ���ٸ� �����Ѵ٦��������������������������������������������������������������������������������������������������������������ڡڡ�
			if (mOpenList.size() == 0) break;
			else 

			//7. open����Ʈ�� ����F�� ���� ��带 ���� ���� ���� �����Ѵ� [ �̹� ���ĵǾ �������� ������ �� ]
			mMainNode = &mOpenList.front();

		} while (1);

		if (isSuccess == true) { 
			PushFinalList(mEndNode.x, mEndNode.y);
			return true; 
		}
		else return false;
	}


	//true�� �����°�, false�� ���
	void PushFinalList(int x, int y) {

		//�ϴ� ��� ����Ʈ�� �ְ�
		mAllTile[x][y].isRoad = true;
		
		//���� ��尡 ���� �����
		if (mAllTile[x][y].x == mStartNode.x && mAllTile[x][y].y == mStartNode.y) {

			return;
		}
		//������ ��尡 �ƴϸ�
		else {
			PushFinalList(mAllTile[x][y].parentX, mAllTile[x][y].parentY);
		}

		return;
	}
	
	//��ֹ� ����ġ �ѱ�
	void SetObstacle(int x, int y) {

		mAllTile[x][y].isObstacle = !mAllTile[x][y].isObstacle;
	}
};

