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

	//int���� �Ѱ��� ����ü [ int�� �ְ���� �ڷ��� �ֱ� ]
	struct constantStruct_int
	{
		int plusData;
		D3DXVECTOR3 DUMMY; //���̵�����
	};

	struct constantStruct_float {

		float plusData;
		D3DXVECTOR3 DUMMY; //���̵�����
	};

	void UpdateStruct_matrix(constantStruct_matrix * structName, float sizeX, float sizeY, float transX, float transY, float rotation)
	{
		//world�� ���ߵ���, �ڵ����� ȭ���� ������ �� �°� �����ߴ�
		structName->world = GetWorldMatrixToRadian(sizeX, sizeY, transX, transY, rotation);

		structName->view = PublicCamera::Get()->GetCamera()->GetCameraMatrix();
		//D3DXMatrixOrthoOffCenterLH(&structName->projection, 0, (float)WinMaxWidth, 0, (float)WinMaxHeight, 0, 1);
		structName->projection = structName->projection = Graphic::Get()->GetProjection();

		GetTranspositionMatrix(structName);
	};
	/*
	void UpdateMouseStruct(constantStruct_matrix * structName, float sizeX, float sizeY, float transX, float transY, float rotation)
	{
		//world�� ���ߵ���, �ڵ����� ȭ���� ������ �� �°� �����ߴ�
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


		//1. srt�� �����ϰ�
		D3DXMatrixIdentity(&result);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixIdentity(&mTranslation);


		D3DXMatrixScaling(&mScale, sizeX, sizeY, 0.0f); //���� ũ�⸦ ���ϴµ�
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


		//1. srt�� �����ϰ�
		D3DXMatrixIdentity(&result);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixIdentity(&mTranslation);


		D3DXMatrixScaling(&mScale, sizeX, sizeY, 0.0f); //���� ũ�⸦ ���ϴµ�
		D3DXMatrixTranslation(&mTranslation, transX, transY, 0.0f);
		D3DXMatrixRotationZ(&mRotation, (float)D3DXToRadian(rotation));


		result = mScale * mRotation * mTranslation;

		return result;
	}

	void GetTranspositionMatrix(constantStruct_matrix * structName) {

		//2.��ġ����� �Ѵ�
		//��ġ����� �ϴ� ������ DX������ ��켱�̰� hlsl�� ���켱�̱⿡ �ٲ��༭ hlsl�� �ѱ��
		//��켱(Row-Major order) - ����
		//���켱(Column-Major order) - ����
		D3DXMatrixTranspose(&structName->world, &structName->world);
		D3DXMatrixTranspose(&structName->view, &structName->view);
		D3DXMatrixTranspose(&structName->projection, &structName->projection);
	};


	D3DXVECTOR3 GetMousePosToWorld(constantStruct_matrix * structName) {

		D3DXVECTOR3 result; // ���� ��ȯ ��

		D3DXMATRIX inverseView; // View���� -> World���� �� ����ȯ�� ��� �Ǵ� view�� ������� ���� ��Ʈ����
		D3DXMatrixInverse(&inverseView, 0, &structName->view); //������� ������� ���� v�� ��´�


		//�̰� ��ũ��������ǥ(����Ʈ��ǥ)���� ������������ ��ȯ(������ǥ : -1 ~ 1)
		float x = (((2.0f * Mouse::Get()->GetPosition().x) / WinMaxWidth) - 0.0f);
		float y = (((2.0f * Mouse::Get()->GetPosition().y) / WinMaxHeight) - 0.0f);


		//������������ ī�޶� �������� ����ȯ ( �������(projection)�� ������� ����
		x /= structName->projection._11;
		y /= structName->projection._22;


		result.x = x;
		result.y = y;


		D3DXVec3TransformCoord(&result, &result, &inverseView); // ����° �Ű������� View������� result�� ���Ͽ� ���� ī�޶���ǥ -> ������ǥ �� ���ȴ�

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
	
	//int���� �Ѱ��� ����ü [ int�� �ְ���� �ڷ��� �ֱ� ]
	struct constantStruct_int
	{
		int plusData;
		D3DXVECTOR3 DUMMY; //���̵�����
	};


	void UpdateStruct_player(constantStruct_player * structName, float sizeX, float sizeY, float transX, float transY, float rotation, D3DXVECTOR4 color_body, D3DXVECTOR4 color_body_shadow)
	{
		//world�� ���ߵ���, �ڵ����� ȭ���� ������ �� �°� �����ߴ�
		structName->world = GetWorldMatrixToRadian(sizeX, sizeY, transX, transY, rotation);

		//view
		structName->view = PublicCamera::Get()->GetCamera()->GetCameraMatrix();

		//projection
		//D3DXMatrixOrthoOffCenterLH(&structName->projection, 0, (float)WinMaxWidth, 0, (float)WinMaxHeight, 0, 1);
		structName->projection = Graphic::Get()->GetProjection();

		//���̴��� �ѱ������ ��ġ���
		GetTranspositionMatrix(structName);

		//���� ����
		structName->color_body = color_body;

		//���� �׸��� ����
		structName->color_body_shadow = color_body_shadow;
	};
	
	D3DXMATRIX GetWorldMatrix(float sizeX, float sizeY, float transX, float transY, float rotation) {

		D3DXMATRIX result;

		D3DXMATRIX mScale;
		D3DXMATRIX mRotation;
		D3DXMATRIX mTranslation;


		//1. srt�� �����ϰ�
		D3DXMatrixIdentity(&result);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixIdentity(&mTranslation);


		D3DXMatrixScaling(&mScale, sizeX, sizeY, 0.0f); //���� ũ�⸦ ���ϴµ�
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


		//1. srt�� �����ϰ�
		D3DXMatrixIdentity(&result);

		D3DXMatrixIdentity(&mScale);
		D3DXMatrixIdentity(&mRotation);
		D3DXMatrixIdentity(&mTranslation);


		D3DXMatrixScaling(&mScale, sizeX, sizeY, 0.0f); //���� ũ�⸦ ���ϴµ�
		D3DXMatrixTranslation(&mTranslation, transX, transY, 0.0f);
		D3DXMatrixRotationZ(&mRotation, (float)D3DXToRadian(rotation));


		result = mScale * mRotation * mTranslation;

		return result;
	}

	void GetTranspositionMatrix(constantStruct_player * structName) {

		//2.��ġ����� �Ѵ�
		//��ġ����� �ϴ� ������ DX������ ��켱�̰� hlsl�� ���켱�̱⿡ �ٲ��༭ hlsl�� �ѱ��
		//��켱(Row-Major order) - ����
		//���켱(Column-Major order) - ����
		D3DXMatrixTranspose(&structName->world, &structName->world);
		D3DXMatrixTranspose(&structName->view, &structName->view);
		D3DXMatrixTranspose(&structName->projection, &structName->projection);
	};

};

