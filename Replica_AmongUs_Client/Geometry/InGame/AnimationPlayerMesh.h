#pragma once
#include "../AnimationMesh.h"


class AnimationPlayerMesh : public AnimationMesh
{
public:
	AnimationPlayerMesh(string aniName, LPCWSTR hlslPath, bool isLookingRight, float transX, float transY);
	~AnimationPlayerMesh();

	void Update(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow);
	void UpdateFromCam(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow);
	void Update_tillLast(D3DXVECTOR4 colorBody, D3DXVECTOR4 colorBodyShadow, bool isFrameLast);
	void Render();

private:

	ConstantStruct_player mConstantData_player;
};

