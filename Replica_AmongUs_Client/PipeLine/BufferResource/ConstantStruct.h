#pragma once
#include "../../stdafx.h"
#include "../../System/Camera.h"

class ConstantStruct_matrix {

public:

	struct constantStruct_matrix
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	//int형이 한개의 구조체 [ int에 넣고싶은 자료형 넣기 ]
	struct constantStruct_int
	{
		int plusData;
		D3DXVECTOR3 DUMMY; //더미데이터
	};

	struct constantStruct_float {

		float plusData;
		D3DXVECTOR3 DUMMY; //더미데이터
	};

	void UpdateStruct_matrix(constantStruct_matrix * structName, float sizeX, float sizeY, float transX, float transY, float rotation)
	{
		//world를 알잘딱깔센, 자동으로 화면의 구석에 딱 맞게 조절했다
		structName->world = GetWorldMatrixToRadian(sizeX, sizeY, transX, transY, rotation);

		structName->view = PublicCamera::Get()->GetCamera()->GetCameraMatrix();
		//D3DXMatrixOrthoOffCenterLH(&structName->projection, 0, (float)WinMaxWidth, 0, (float)WinMaxHeight, 0, 1);
		structName->projection = structName->projection = Graphic::Get()->GetProjection();

		GetTranspositionMatrix(structName);
	};
	/*
	void UpdateMouseStruct(constantStruct_matrix * structName, float sizeX, float sizeY, float transX, float transY, float rotation)
	{
		//world를 알잘딱깔센, 자동으로 화면의 구석에 딱 맞게 조절했다
		structName->world = GetWorldMatrix(sizeX, sizeY, transX, transY, rotation);

		structName->view = PublicCamera::Get()->GetCamera()->GetCameraMatrix();
		D3DXMatrixOrthoOffCenterLH(&structName->projection, 0, (float)WinMaxWidth, 0, (float)WinMaxHeight, 0, 1);

		structName->mouse = GetMousePosToWorld(structName);

		GetTranspositionMatrix(structName);

		if (Mouse::Get()->Down(1) == true) {
			int a = 0;
		}
	};
	*/


	D3DXMATRIX GetWorldMatrix(float sizeX, float sizeY, float transX, float transY , float rotation) {

		D3DXMATRIX result;

		D3DXMATRIX mScale;
		D3DXMATRIX mRotation;
		D3DXMATRIX mTranslation;


		//1. srt를 결정하고
		D3DXMatrixIdentity(&result);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixIdentity(&mTranslation);


		D3DXMatrixScaling(&mScale, sizeX, sizeY, 0.0f); //반의 크기를 정하는듯
		D3DXMatrixTranslation(&mTranslation, transX, transY, 0.0f);
		D3DXMatrixRotationZ(&mRotation, rotation);


		result = mScale * mRotation * mTranslation;

		return result;
	}

	D3DXMATRIX GetWorldMatrixToRadian(float sizeX, float sizeY, float transX, float transY, float rotation) {

		D3DXMATRIX result;

		D3DXMATRIX mScale;
		D3DXMATRIX mRotation;
		D3DXMATRIX mTranslation;


		//1. srt를 결정하고
		D3DXMatrixIdentity(&result);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixIdentity(&mTranslation);


		D3DXMatrixScaling(&mScale, sizeX, sizeY, 0.0f); //반의 크기를 정하는듯
		D3DXMatrixTranslation(&mTranslation, transX, transY, 0.0f);
		D3DXMatrixRotationZ(&mRotation, (float)D3DXToRadian(rotation));


		result = mScale * mRotation * mTranslation;

		return result;
	}

	void GetTranspositionMatrix(constantStruct_matrix * structName) {

		//2.전치행렬을 한다
		//전치행렬을 하는 이유는 DX에서는 행우선이고 hlsl은 열우선이기에 바꿔줘서 hlsl에 넘긴다
		//행우선(Row-Major order) - 가로
		//열우선(Column-Major order) - 세로
		D3DXMatrixTranspose(&structName->world, &structName->world);
		D3DXMatrixTranspose(&structName->view, &structName->view);
		D3DXMatrixTranspose(&structName->projection, &structName->projection);
	};


	D3DXVECTOR3 GetMousePosToWorld(constantStruct_matrix * structName) {

		D3DXVECTOR3 result; // 최종 반환 값

		D3DXMATRIX inverseView; // View공간 -> World공간 의 역변환에 사용 되는 view의 역행렬을 담을 매트릭스
		D3DXMatrixInverse(&inverseView, 0, &structName->view); //뷰행렬의 역행렬을 구해 v에 담는다


		//이게 스크린공간좌표(뷰포트좌표)에서 투영공간으로 변환(투영좌표 : -1 ~ 1)
		float x = (((2.0f * Mouse::Get()->GetPosition().x) / WinMaxWidth) - 0.0f);
		float y = (((2.0f * Mouse::Get()->GetPosition().y) / WinMaxHeight) - 0.0f);


		//투영공간에서 카메라 공간으로 역변환 ( 투영행렬(projection)의 역행렬을 곱합
		x /= structName->projection._11;
		y /= structName->projection._22;


		result.x = x;
		result.y = y;


		D3DXVec3TransformCoord(&result, &result, &inverseView); // 세번째 매개변수인 View역행렬을 result에 곱하여 값이 카메라좌표 -> 월드좌표 로 계산된다

		return result;
	}
};


class ConstantStruct_player {

public:

	struct constantStruct_player
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
		D3DXVECTOR4 color_body;
		D3DXVECTOR4 color_body_shadow;
	};
	
	//int형이 한개의 구조체 [ int에 넣고싶은 자료형 넣기 ]
	struct constantStruct_int
	{
		int plusData;
		D3DXVECTOR3 DUMMY; //더미데이터
	};


	void UpdateStruct_player(constantStruct_player * structName, float sizeX, float sizeY, float transX, float transY, float rotation, D3DXVECTOR4 color_body, D3DXVECTOR4 color_body_shadow)
	{
		//world를 알잘딱깔센, 자동으로 화면의 구석에 딱 맞게 조절했다
		structName->world = GetWorldMatrixToRadian(sizeX, sizeY, transX, transY, rotation);

		//view
		structName->view = PublicCamera::Get()->GetCamera()->GetCameraMatrix();

		//projection
		//D3DXMatrixOrthoOffCenterLH(&structName->projection, 0, (float)WinMaxWidth, 0, (float)WinMaxHeight, 0, 1);
		structName->projection = Graphic::Get()->GetProjection();

		//쉐이더로 넘기기위해 전치행렬
		GetTranspositionMatrix(structName);

		//몸통 색상
		structName->color_body = color_body;

		//몸통 그림자 색상
		structName->color_body_shadow = color_body_shadow;
	};
	
	D3DXMATRIX GetWorldMatrix(float sizeX, float sizeY, float transX, float transY, float rotation) {

		D3DXMATRIX result;

		D3DXMATRIX mScale;
		D3DXMATRIX mRotation;
		D3DXMATRIX mTranslation;


		//1. srt를 결정하고
		D3DXMatrixIdentity(&result);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixIdentity(&mTranslation);


		D3DXMatrixScaling(&mScale, sizeX, sizeY, 0.0f); //반의 크기를 정하는듯
		D3DXMatrixTranslation(&mTranslation, transX, transY, 0.0f);
		D3DXMatrixRotationZ(&mRotation, rotation);


		result = mScale * mRotation * mTranslation;

		return result;
	}

	D3DXMATRIX GetWorldMatrixToRadian(float sizeX, float sizeY, float transX, float transY, float rotation) {

		D3DXMATRIX result;

		D3DXMATRIX mScale;
		D3DXMATRIX mRotation;
		D3DXMATRIX mTranslation;


		//1. srt를 결정하고
		D3DXMatrixIdentity(&result);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixIdentity(&mTranslation);


		D3DXMatrixScaling(&mScale, sizeX, sizeY, 0.0f); //반의 크기를 정하는듯
		D3DXMatrixTranslation(&mTranslation, transX, transY, 0.0f);
		D3DXMatrixRotationZ(&mRotation, (float)D3DXToRadian(rotation));


		result = mScale * mRotation * mTranslation;

		return result;
	}

	void GetTranspositionMatrix(constantStruct_player * structName) {

		//2.전치행렬을 한다
		//전치행렬을 하는 이유는 DX에서는 행우선이고 hlsl은 열우선이기에 바꿔줘서 hlsl에 넘긴다
		//행우선(Row-Major order) - 가로
		//열우선(Column-Major order) - 세로
		D3DXMatrixTranspose(&structName->world, &structName->world);
		D3DXMatrixTranspose(&structName->view, &structName->view);
		D3DXMatrixTranspose(&structName->projection, &structName->projection);
	};

};

