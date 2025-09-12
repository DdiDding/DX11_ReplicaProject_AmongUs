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


	//필여함??
	void SetIsClickEnd(bool value) { mClickEnd = value; };
	bool GetIsClickEnd() { return mClickEnd; };

private:

	//컴퓨터 3대 배경화면
	Mesh * mBackground;
	Mesh * mClosseBtn;

	bool mClickEnd; // X버튼 눌렀는가??

	RenderTargetTexture  * mRenderTargetView1;
	RenderTargetTexture  * mRenderTargetView2;

	Mesh * mCamera1;
	Mesh * mCamera2;

	float test = 0.0f;
};

