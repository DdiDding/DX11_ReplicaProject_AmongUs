#pragma once
#include "../stdafx.h"

struct SHAPE {
	D3DXVECTOR3 position; //��ġ
	D3DXVECTOR3 scale;//ũ�� 
	float rot;//ȸ���� 
};

class Collision :public SingletonBase<Collision>
{
public:

	friend class SingletonBase<Collision>;

	//�浹�ÿ� true, ���浹�ÿ� false�� ��ȯ�Ѵ�
	bool IsLineCollision(D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 d) {


		//Point 4���� y���� ��� �������� ����ó���ϱ����� ����
		//���ʿ� �ִ°� ������ C�� �ǰԲ�
		if (c.x > d.x) swap(c, d);
		//�̰� true�� �浹���ϴ°�
		if ((a.x < c.x && b.x < c.x) || (a.x > d.x && b.x > d.x)) return false;


		//Point 4���� X���� ��� �������� ����ó���ϱ����� ����
		//���ʿ� �ִ°� ������ C�� �ǰԲ�
		if (c.y < d.y) swap(c, d);
		//�̰� true�� �浹���ϴ°�
		if ((a.y > c.y && b.y > c.y) || (a.y < d.y && b.y < d.y)) return false;

		

		//���� a->b �� �������� c ��  d�� �˻����� ���� ��
		double ab = GetVec3CrossProduct(a, b, c) * GetVec3CrossProduct(a, b, d);
		//���� c->d �� �������� c ��  d�� �˻����� ���� ��
		double cd = GetVec3CrossProduct(c, d, a) * GetVec3CrossProduct(c, d, b);


		if (ab <= 0 && cd <= 0)
			return true;
		else 
			return false;
	};

	//Rect�� left�� top�� ��� ������� ��������ǥ�� ����
	//Rect�� right�� bottom�� ��� �����ϴ� ��������ǥ�� ����
	bool AabbCollision(RECT a, RECT b)
	{

		if (a.left <= b.right &&
			b.left <= a.right &&
			a.top >= b.bottom &&
			b.top >= a.bottom) return true;

		else return false;
	}


	bool PointAndRect(D3DXVECTOR3 mousePos, RECT rect) {

		//true�� �浹�ϴ°���
		if (rect.left <= mousePos.x && mousePos.x <= rect.right &&
			rect.bottom <= mousePos.y && mousePos.y <= rect.top) return true;

		return false;
	}

	bool ObbCollision(SHAPE a, SHAPE b) //�浹 ���� Ȯ�� 
	{
		D3DXVECTOR3 dist = a.position - b.position; //a ���� b �Ÿ�  
		D3DXVECTOR3 vec[4] = { getHeightVector(a),getHeightVector(b),getWidthVector(a),getWidthVector(b) };
		D3DXVECTOR3 unit;
		for (int i = 0; i < 4; i++) {
			double sum = 0;
			unit = getUnitVector(vec[i]);
			for (int j = 0; j < 4; j++) {
				sum += abs(vec[j].x*unit.x + vec[j].y*unit.y);
			}
			if (abs(dist.x*unit.x + dist.y*unit.y) > sum) {
				return false;
			}
		}

		return true;
	}


private:

	//���غ��� pa �� �������� ���� pb�� �ð�������� �ݽð�������� ����Ѵ�
	double GetVec3CrossProduct(D3DXVECTOR3 p, D3DXVECTOR3 a, D3DXVECTOR3 b) {

		//�������� ���� ����
		D3DXVECTOR3 result;

		//���� ����
		D3DXVECTOR3 pa = a - p;

		//�� ����
		D3DXVECTOR3 pb = b - p;


		D3DXVec3Cross(&result, &pa, &pb); //z���� ���� �ƴ� �������� ��

		return result.z;
	}

	Collision() {};
	~Collision() {};


	D3DXVECTOR3 getHeightVector(SHAPE a) //���� ���
	{
		D3DXVECTOR3 ret;
		ret.x = a.scale.y*sinf(a.rot) / 2;
		ret.y = -a.scale.y*cosf(a.rot) / 2;
		return ret;
	}

	D3DXVECTOR3 getWidthVector(SHAPE a) //�ʺ� ���
	{
		D3DXVECTOR3 ret;
		ret.x = a.scale.x*cosf(a.rot) / 2;
		ret.y = -a.scale.x*sinf(a.rot) / 2;
		return ret;
	}

	D3DXVECTOR3 getUnitVector(D3DXVECTOR3 a) //���� 
	{

		D3DXVECTOR3 ret;
		float size;
		size = sqrt(a.x*a.x + a.y*a.y);
		ret.x = a.x / size;
		ret.y = a.y / size;
		return ret;
	}
};