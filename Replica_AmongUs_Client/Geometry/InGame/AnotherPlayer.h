#pragma once
//다른 플레이어들의 데이터를 가지고있을 클래스

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



	//위치는 부모클래스에  mTransX, mTransY가 있다
	//어떤 애니메이션인지도 mAnimation에 저장하면되고
	//프레임도 마찬가지고

	//임포스터인지 아닌지
	bool mIsImposter;

	//죽었는지 안죽었는지
	bool mIsDie;

	//플레이어 색상
	D3DXVECTOR4 mColor_body;
	D3DXVECTOR4 mColor_body_shadow;

	//TODO 닉네임 설저ㅏㅇ하고 띄우기
};

