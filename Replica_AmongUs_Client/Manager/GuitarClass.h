#pragma once

//�÷��̾� ���� �������ؾ��ϴ� �ָ��Ѱ� ��Ƶδ� Ŭ����

class Mesh;

class GuitarClass : public SingletonBase<GuitarClass>
{
public:

	friend class SingletonBase<GuitarClass>;

	void Update();
	void Render();

	void Setting();

private:

	GuitarClass();
	~GuitarClass();

	void init();

private:

	Mesh * mProgressBar;
	Mesh * mProgressBarGage;

	int mProgressBarPercent;//���� �ۼ�Ʈ�� ��Ÿ��


};

