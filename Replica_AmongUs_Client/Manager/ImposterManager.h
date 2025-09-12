#pragma once

//���������� ��ɵ��� ����ϰ� �ȴ�!!

class ImposterManager : public SingletonBase<ImposterManager>
{
public:

	friend class SingletonBase<ImposterManager>;

	//LAst�������Ŵ� ������ ���ϰ� ������Ʈ�Ѵ� �Ҹ���~
	void Update_Last();

	//���� ����� ����Ѹ� �������°�, �׷� �ε����� ���������� �ΰ��� ��߰ڴµ�
	//���� ����� ũ����� �ε����� ��ȯ�Ѵ�, ���ٸ� -1�� ��ȯ�ȴ�
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

	//�÷��̾� �Ÿ� ���ϴ� �κ�

	float mMinLegth; //�ٸ� �÷��̾�� ��ȣ�ۿ�Ǵ� �ּ� �Ÿ�

	//ų�� �����Ѱ�?? - �̴� PlayerManager���� GetNearCrewIndex�� ȣ��Ǿ� ���� ����ȴ�
	//-1�� ���� 0�̻��� �����ϴٰ� ���� �ȴ�
	//�׸��� � �÷��̾ ������ ���� �ǹ��ϰԵȴ�
	int mIsPossibleKill; 

	bool mIsKill; //�������׿�����
};

