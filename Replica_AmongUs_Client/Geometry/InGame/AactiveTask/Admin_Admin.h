#pragma once

class Mesh;

class Admin_Admin
{
public:

	Admin_Admin();
	~Admin_Admin();

	void Update();
	void Render();


	//�ʿ���??
	void SetIsClickEnd(bool value) { mClickEnd = value; };
	bool GetIsClickEnd() { return mClickEnd; };

private:

	Mesh * mMap;
	Mesh * mIcon;

	Mesh * mClosseBtn;


	bool mClickEnd; // X��ư �����°�??
};

