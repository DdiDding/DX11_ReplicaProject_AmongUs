#pragma once
#include "../FW1/FW1FontWrapper.h"

class FontManager : public SingletonBase<FontManager>
{
public:
	friend class SingletonBase<FontManager>;

	//Render사이에 무저건! 껴야함!
	void DrawFont(LPCWSTR fontKey, WCHAR * textValue, float fontSize, float posX, float posY, UINT32 color);
	void DrawFont_border(LPCWSTR fontKey, WCHAR * textValue, float fontSize, float posX, float posY, UINT32 fontColor, UINT32 borderColor,int borderSize);

	void DrawCenter(LPCWSTR fontKey, WCHAR * textValue, float fontSize, float posX, float posY, UINT32 color);
	void DrawCenter_border(LPCWSTR fontKey, WCHAR * textValue, float fontSize, float posX, float posY, UINT32 fontColor, UINT32 borderColor,int borderSize);

	void DrawVcenter(LPCWSTR fontKey, WCHAR * textValue, float fontSize, float posX, float posY, UINT32 color);

	//FW1_VCENTER

private:
	FontManager();
	~FontManager();

	void init();

	void createFont(LPCWSTR fontFamily);

	IFW1Factory * mFW1Factory;
	map<LPCWSTR,IFW1FontWrapper *> mFontMap;
};

