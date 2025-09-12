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

	//�� ���� ���� ������Ʈ, �������ٸ�
	void endAniUpdate();
	void endAniRender();

private:

	//Scene�ٲٴ� ����
	bool mIsStartChangeAni = false;// Ui���� �����޶�� ��û�� ��������� ����
	bool mIsRenderChangeAni = false;//������ ��� �������ص� �ǳĴ� ��
	bool mIsOkChangeScene = false; //������ �ִϸ��̼� �������� true�� ���� �ٲٰԿ�û�Ѵ�
	ColorMesh * mInGame_allBlack;//�� �տ� ������ ����ȭ��

	float mBlackAlpha = 0.5f; //������ ���İ�

	int mAnimationState; //� �ִϸ��̼��� �ؾ��ϴ°�
};

