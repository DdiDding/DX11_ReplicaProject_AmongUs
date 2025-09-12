#include "../stdafx.h"
#include "FontManager.h"

void FontManager::DrawFont(LPCWSTR fontKey, WCHAR * textValue , float fontSize, float posX, float posY, UINT32 color)
{
	mFontMap.find(fontKey)->second->DrawString(
		GETDC,
		textValue,// String
		fontSize,// Font size
		posX,// X position
		posY,// Y position
		color,// Text color, 0xAaBbGgRr
		FW1_RESTORESTATE// Flags
	);
}

void FontManager::DrawFont_border(LPCWSTR fontKey, WCHAR * textValue, float fontSize, float posX, float posY, UINT32 fontColor, UINT32 borderColor, int borderSize)
{
	//¿Ü°û¼±
	mFontMap.find(fontKey)->second->DrawString(GETDC, textValue, fontSize, posX - borderSize, posY - borderSize, borderColor, FW1_RESTORESTATE);
	mFontMap.find(fontKey)->second->DrawString(GETDC, textValue, fontSize, posX + borderSize, posY - borderSize, borderColor, FW1_RESTORESTATE);
	mFontMap.find(fontKey)->second->DrawString(GETDC, textValue, fontSize, posX + borderSize, posY + borderSize, borderColor, FW1_RESTORESTATE);
	mFontMap.find(fontKey)->second->DrawString(GETDC, textValue, fontSize, posX - borderSize, posY + borderSize, borderColor, FW1_RESTORESTATE);

	//Áß¾Ó
	mFontMap.find(fontKey)->second->DrawString(GETDC, textValue, fontSize, posX, posY, fontColor, FW1_RESTORESTATE);
}

void FontManager::DrawCenter(LPCWSTR fontKey, WCHAR * textValue, float fontSize, float posX, float posY, UINT32 color)
{
	mFontMap.find(fontKey)->second->DrawString(
		GETDC,
		textValue,// String
		fontSize,// Font size
		posX,// X position
		posY,// Y position
		color,// Text color, 0xAaBbGgRr
		FW1_RESTORESTATE |FW1_CENTER// Flags
	);
}

void FontManager::DrawCenter_border(LPCWSTR fontKey, WCHAR * textValue, float fontSize, float posX, float posY, UINT32 color, UINT32 borderColor, int borderSize)
{

	//¿Ü°û¼±
	mFontMap.find(fontKey)->second->DrawString(GETDC,textValue,fontSize,posX - borderSize,posY - borderSize,borderColor,FW1_RESTORESTATE | FW1_CENTER );
	mFontMap.find(fontKey)->second->DrawString(GETDC,textValue,fontSize,posX + borderSize,posY - borderSize,borderColor,FW1_RESTORESTATE | FW1_CENTER );
	mFontMap.find(fontKey)->second->DrawString(GETDC,textValue,fontSize,posX + borderSize,posY + borderSize,borderColor,FW1_RESTORESTATE | FW1_CENTER );
	mFontMap.find(fontKey)->second->DrawString(GETDC,textValue,fontSize,posX - borderSize,posY + borderSize,borderColor,FW1_RESTORESTATE | FW1_CENTER );

	//Áß¾Ó
	mFontMap.find(fontKey)->second->DrawString(GETDC,textValue,fontSize,posX,posY,color,FW1_RESTORESTATE | FW1_CENTER );

}

void FontManager::DrawVcenter(LPCWSTR fontKey, WCHAR * textValue, float fontSize, float posX, float posY, UINT32 color)
{
	mFontMap.find(fontKey)->second->DrawString(GETDC, textValue, fontSize, posX, posY, color, FW1_RESTORESTATE | FW1_VCENTER);
}

FontManager::FontManager()
{
	init();
}

FontManager::~FontManager()
{
	SAFE_DELETE(mFW1Factory);
	//TODO:map ÇØÁ¦ÇÏ±â
}

void FontManager::init()
{
	HRESULT hr = FW1CreateFactory(FW1_VERSION, &mFW1Factory);
	ASSERT(hr);

	createFont(L"VCR OSD Mono");
	createFont(L"Varela");
	createFont(L"Arial");
	createFont(L"HYHeadLine");
	createFont(L"LABµðÁöÅÐ");
}

void FontManager::createFont(LPCWSTR fontFamily)
{
	IFW1FontWrapper * mFontWrapper;
	mFW1Factory->CreateFontWrapper(GETDEVICE, fontFamily, &mFontWrapper);

	mFontMap.insert(make_pair(fontFamily, mFontWrapper));
}
