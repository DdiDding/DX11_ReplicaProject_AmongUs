#include "../../stdafx.h"
#include "../Mesh.h"
#include "BackGroundImage.h"

BackGroundImage::BackGroundImage(float sizeX, float sizeY, float transX, float transY, LPCWSTR hlslName, WCHAR * imageRoute)
	:Mesh(sizeX, sizeY, transX, transY, hlslName, imageRoute)
{
}

BackGroundImage::~BackGroundImage()
{
}
