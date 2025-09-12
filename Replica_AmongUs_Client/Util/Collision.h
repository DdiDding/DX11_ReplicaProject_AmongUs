#pragma once
#include "../stdafx.h"

struct SHAPE {
	D3DXVECTOR3 position; //위치
	D3DXVECTOR3 scale;//크기 
	float rot;//회전값 
};

class Collision :public SingletonBase<Collision>
{
public:

	friend class SingletonBase<Collision>;

	//충돌시에 true, 미충돌시에 false를 반환한다
	bool IsLineCollision(D3DXVECTOR3 a, D3DXVECTOR3 b, D3DXVECTOR3 c, D3DXVECTOR3 d) {


		//Point 4개가 y축이 모두 같을때의 예외처리하기위한 세팅
		//왼쪽에 있는게 무조건 C로 되게끔
		if (c.x > d.x) swap(c, d);
		//이게 true면 충돌안하는것
		if ((a.x < c.x && b.x < c.x) || (a.x > d.x && b.x > d.x)) return false;


		//Point 4개가 X축이 모두 같을때의 예외처리하기위한 세팅
		//왼쪽에 있는게 무조건 C로 되게끔
		if (c.y < d.y) swap(c, d);
		//이게 true면 충돌안하는것
		if ((a.y > c.y && b.y > c.y) || (a.y < d.y && b.y < d.y)) return false;

		

		//벡터 a->b 를 기준으로 c 와  d를 검사했을 때의 값
		double ab = GetVec3CrossProduct(a, b, c) * GetVec3CrossProduct(a, b, d);
		//벡터 c->d 를 기준으로 c 와  d를 검사했을 때의 값
		double cd = GetVec3CrossProduct(c, d, a) * GetVec3CrossProduct(c, d, b);


		if (ab <= 0 && cd <= 0)
			return true;
		else 
			return false;
	};

	//Rect의 left와 top은 모두 좌측상단 꼭짓점좌표를 뜻함
	//Rect의 right와 bottom은 모두 우측하단 꼭짓점좌표를 뜻함
	bool AabbCollision(RECT a, RECT b)
	{

		if (a.left <= b.right &&
			b.left <= a.right &&
			a.top >= b.bottom &&
			b.top >= a.bottom) return true;

		else return false;
	}


	bool PointAndRect(D3DXVECTOR3 mousePos, RECT rect) {

		//true면 충돌하는것임
		if (rect.left <= mousePos.x && mousePos.x <= rect.right &&
			rect.bottom <= mousePos.y && mousePos.y <= rect.top) return true;

		return false;
	}

	bool ObbCollision(SHAPE a, SHAPE b) //충돌 여부 확인 
	{
		D3DXVECTOR3 dist = a.position - b.position; //a 에서 b 거리  
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

	//기준벡터 pa 를 기준으로 벡터 pb를 시계방향인지 반시계방향인지 계산한다
	double GetVec3CrossProduct(D3DXVECTOR3 p, D3DXVECTOR3 a, D3DXVECTOR3 b) {

		//외적값을 담을 벡터
		D3DXVECTOR3 result;

		//기준 벡터
		D3DXVECTOR3 pa = a - p;

		//비교 벡터
		D3DXVECTOR3 pb = b - p;


		D3DXVec3Cross(&result, &pa, &pb); //z값에 내가 아는 외적값이 들어감

		return result.z;
	}

	Collision() {};
	~Collision() {};


	D3DXVECTOR3 getHeightVector(SHAPE a) //높이 계산
	{
		D3DXVECTOR3 ret;
		ret.x = a.scale.y*sinf(a.rot) / 2;
		ret.y = -a.scale.y*cosf(a.rot) / 2;
		return ret;
	}

	D3DXVECTOR3 getWidthVector(SHAPE a) //너비 계산
	{
		D3DXVECTOR3 ret;
		ret.x = a.scale.x*cosf(a.rot) / 2;
		ret.y = -a.scale.x*sinf(a.rot) / 2;
		return ret;
	}

	D3DXVECTOR3 getUnitVector(D3DXVECTOR3 a) //내적 
	{

		D3DXVECTOR3 ret;
		float size;
		size = sqrt(a.x*a.x + a.y*a.y);
		ret.x = a.x / size;
		ret.y = a.y / size;
		return ret;
	}
};