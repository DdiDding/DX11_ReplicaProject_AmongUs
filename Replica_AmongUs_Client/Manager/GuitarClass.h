#pragma once

//플레이어 위에 랜더링해야하는 애매한걸 모아두는 클래스

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

	int mProgressBarPercent;//현재 퍼센트를 나타냄


};

