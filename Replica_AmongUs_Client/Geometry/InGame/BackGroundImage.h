#pragma once
class BackGroundImage : public Mesh
{
public:

	BackGroundImage(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute);
	~BackGroundImage();


private:


};

//Mesh(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR* imageRoute)