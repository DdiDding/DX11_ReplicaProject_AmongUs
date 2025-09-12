#pragma once
class Mesh_player : public Mesh
{
public:
	Mesh_player(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute);
	~Mesh_player();

	void Update();
	void Update_withCam();

	void SaveMyColor(D3DXVECTOR4 body, D3DXVECTOR4 shadow);

private:
	void init();

private:

	ConstantStruct_player mConstantData_player;

	//플레이어 색상
	D3DXVECTOR4 mColor_body;
	D3DXVECTOR4 mColor_body_shadow;
};

