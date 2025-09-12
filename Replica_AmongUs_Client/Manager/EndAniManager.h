#pragma once


class EndAniManager : public SingletonBase<EndAniManager>
{
public:
	friend class EndAniManager;

	void SetIsStartChangeAni(bool value) { mIsStartChangeAni = value; };

	void SetIsOkChangeScene(bool value) { this->mIsOkChangeScene = value; };
	bool GetIsOkChangeScene() { return mIsOkChangeScene; };

	void Update();
	void Render();

	EndAniManager();
	~EndAniManager();

private:

	void init();

	//각 씬에 따라 업데이트, 렌더가다름
	void endAniUpdate();
	void endAniRender();

private:

	//Scene바꾸는 목적
	bool mIsStartChangeAni = false;// Ui에서 끝내달라는 요청이 들어왔을경우 시작
	bool mIsRenderChangeAni = false;//끝나는 장면 렌더링해도 되냐는 뜻
	bool mIsOkChangeScene = false; //끝나는 애니메이션 끝났을때 true면 씬을 바꾸게요청한다
	ColorMesh * mInGame_allBlack;//맨 앞에 나오는 검은화면

	float mBlackAlpha = 0.5f; //검은색 알파값

	int mAnimationState; //어떤 애니메이션을 해야하는가
};

