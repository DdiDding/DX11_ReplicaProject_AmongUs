#pragma once
class ImageManager : public SingletonBase<ImageManager>
{
public:
	friend class SingletonBase<ImageManager>;

	ImageManager();
	~ImageManager();

	void Init();

	ID3D11ShaderResourceView * GetImage(WCHAR * fileName) { return mImageMap.find(fileName)->second; };

private:

	void createImage(WCHAR * fileName);

private:
	
	//<key , value>
	unordered_map<WCHAR *, ID3D11ShaderResourceView * > mImageMap;
};

