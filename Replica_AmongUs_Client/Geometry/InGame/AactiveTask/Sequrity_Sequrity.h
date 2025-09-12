#pragma once

class Mesh;
class RenderTargetTexture;

class Sequrity_Sequrity
{
public:

	Sequrity_Sequrity();
	~Sequrity_Sequrity();

	void Update();
	void Render();


	//�ʿ���??
	void SetIsClickEnd(bool value) { mClickEnd = value; };
	bool GetIsClickEnd() { return mClickEnd; };

private:

	//��ǻ�� 3�� ���ȭ��
	Mesh * mBackground;
	Mesh * mClosseBtn;

	bool mClickEnd; // X��ư �����°�??

	RenderTargetTexture  * mRenderTargetView1;
	RenderTargetTexture  * mRenderTargetView2;

	Mesh * mCamera1;
	Mesh * mCamera2;

	float test = 0.0f;
};

