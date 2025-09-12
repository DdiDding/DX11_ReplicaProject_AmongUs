#pragma once
#include "../../Manager/TaskActtiveManager.h"
#include "../../Manager/TaskManager.h"
#include "../InGame/Ui_inGameRect.h"
#include "Mesh_player.h"




//�ΰ��ӿ� ���Ǵ� Ui
class Ui_inGame
{
public:

	Ui_inGame();
	~Ui_inGame();

	void Update(bool isImposter);


	void Render(bool isImposter);

	//Ŭ���� �ߴ��� Ȯ���Ѵ�
	bool GetIsSlot2Click() {return mIsSlot2Click;};

	//2�� �����ϰ� 0, 1���� Ȱ��ȭ�� �ǰ����� Ŭ���� ó���ϱ⶧���� Ŭ���� �ȴٸ� Ȱ��ȭ�� ��٤ô°Ŵ�
	bool GetIsSlot1Click() {return mIsSlot1Click;};

private:

	//�ٸ� �̹����� ��ü ( uv�� ���� )
	void changeImage(Ui_inGameRect * slot, UINT uvNum);

private:

	//�ִϸ��̼������� ��� �׳� ���� �ɰ��� ������ �̹��� ����� �ȸ��� ���°Ŵ�
	Animation mAnimation;


	//Ui ��ư ���� ������ ����������
	//  - ��ȣ��ġ - 
	//		[ 0 ]
	//[ 1 ]	[ 2 ]
	Ui_inGameRect * mUiSlot[3];

	bool mCompleteList[3];


	//ps�� ���� ������� �������� ���������� �������Լ�
	//���콺 ���� ��ȣ�ۿ�
	string mTaskName;


	//�� ������ ��������
	bool mIsSlot0Click = false;
	bool mIsSlot1Click = false;
	bool mIsSlot2Click = false;


	//�������� Ȱ��ȭ �ƴ���
	bool mPossibleSlot0 = false;
	bool mPossibleSlot1 = false;
	//bool mPossibleSlot2 = false; ->�̰� TaskManager���� ������ش�

	//ų����Ÿ���ΰ� true�� ��Ÿ�����ΰŰ� false�� Ȱ��ȭ �ȰŴ� 
	bool mIsKillCoolTime = false;
	float mCoolTime = 0.0f; //��Ÿ�� ��� �ð�
	float mMaxCoolTime = 10.0f; //�ƽ� ��Ÿ��

};


class Ui_miniMap {

public:

	Ui_miniMap();
	~Ui_miniMap();

	void Update();
	void Render();

	void SetColorToIcon(D3DXVECTOR4 body, D3DXVECTOR4 shadow);


private:

	void init();

	//�̴ϸʿ����� ������ǥ�� ��ȯ����
	D3DXVECTOR2 getMiniMapPos();

private:

	Mesh * mMiniMapBtn;
	//�̴ϸ��� Trans��
	D3DXVECTOR2 mMiniMapTrans = { 179.0f, 38.0f };
	D3DXVECTOR2 mMiniMapSize = { 922.0f, 647.0f };


	//�÷��̾��� ������
	Mesh_player * mPlayerIcon;
	//������� ���� ������ ��ü���� �簢�� ������
	D3DXVECTOR2 mOnlyAreaSize = {3540, 2468};
	//�� areaSize������ ��ǥ�� ���ϱ����� ������ ��
	D3DXVECTOR2 mToDoMinValue = { 642, 494 };


	//�ϴ� ���� ����� �˷��ִ� �ؽ�Ʈ

};