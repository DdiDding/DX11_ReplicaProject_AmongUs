#pragma once
#include "../Mesh.h"

class Ui_inGameRect : public Mesh
{
public:
	Ui_inGameRect(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute);
	~Ui_inGameRect();

	//매개변수는 투명한지? 1면 투명 0면 불투명
	void Update(int isAlpha);
	void Render();

	//마우스가 자신을 클릭했는지
	bool IsClick(D3DXVECTOR3 mousePos);

	void SetOriginTrans(D3DXVECTOR2 trans) { mOriginTrans = trans; };

	D3DXVECTOR2 GetOriginTrans() { return mOriginTrans; };

private:

	D3DXVECTOR2 mOriginTrans;
};

