#pragma once
#include "../Mesh.h"

class Ui_inGameRect : public Mesh
{
public:
	Ui_inGameRect(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute);
	~Ui_inGameRect();

	//�Ű������� ��������? 1�� ���� 0�� ������
	void Update(int isAlpha);
	void Render();

	//���콺�� �ڽ��� Ŭ���ߴ���
	bool IsClick(D3DXVECTOR3 mousePos);

	void SetOriginTrans(D3DXVECTOR2 trans) { mOriginTrans = trans; };

	D3DXVECTOR2 GetOriginTrans() { return mOriginTrans; };

private:

	D3DXVECTOR2 mOriginTrans;
};

