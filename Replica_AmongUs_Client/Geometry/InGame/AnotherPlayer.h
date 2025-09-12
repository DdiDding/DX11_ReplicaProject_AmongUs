#pragma once
//�ٸ� �÷��̾���� �����͸� ���������� Ŭ����

#include "../AnimationMesh.h"

class AnotherPlayer : public AnimationMesh
{
public:
	AnotherPlayer(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY);
	~AnotherPlayer();

	void Update();

	D3DXVECTOR4 * GetColorBodyP() { return &mColor_body; };
	D3DXVECTOR4 * GetColorBodyShadowP() { return &mColor_body_shadow; };

private:

	

private:

	ConstantStruct_player mConstantData_player;



	//��ġ�� �θ�Ŭ������  mTransX, mTransY�� �ִ�
	//� �ִϸ��̼������� mAnimation�� �����ϸ�ǰ�
	//�����ӵ� ����������

	//������������ �ƴ���
	bool mIsImposter;

	//�׾����� ���׾�����
	bool mIsDie;

	//�÷��̾� ����
	D3DXVECTOR4 mColor_body;
	D3DXVECTOR4 mColor_body_shadow;

	//TODO �г��� ���������ϰ� ����
};

