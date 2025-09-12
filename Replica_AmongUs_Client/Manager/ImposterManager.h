#pragma once

//임포스터의 기능들을 담당하게 된다!!

class ImposterManager : public SingletonBase<ImposterManager>
{
public:

	friend class SingletonBase<ImposterManager>;

	//LAst가붙은거는 렌더링 다하고 업데이트한단 소리임~
	void Update_Last();

	//가장 가까운 사람한명만 빨개지는것, 그럼 인덱스랑 빨개지는지 두개를 줘야겠는뎅
	//가장 가까운 크우원의 인덱스를 반환한다, 없다면 -1이 반환된다
	int GetNearCrewIndex();

	int GetPossibleKill() { return mIsPossibleKill; };

	void SetIsKill(bool value) { mIsKill = value; };
	bool GetIsKill() { return mIsKill; };

	void Setting();

private:
	ImposterManager();
	~ImposterManager();

	void init();

private:

	//플레이어 거리 구하는 부분

	float mMinLegth; //다른 플레이어와 상호작용되는 최소 거리

	//킬이 가능한가?? - 이는 PlayerManager에서 GetNearCrewIndex가 호출되어 값이 저장된다
	//-1은 없고 0이상은 가능하다고 보면 된다
	//그리고 어떤 플레이어를 죽일지 값도 의미하게된다
	int mIsPossibleKill; 

	bool mIsKill; //누군가죽였는지
};

