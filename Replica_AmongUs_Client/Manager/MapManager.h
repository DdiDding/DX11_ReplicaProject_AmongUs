#pragma once

//��Ʈ�������� ���� ��ġ�� �˾Ƴ���.
//�κ� ���ƴ��� �Ȱ��ƴ����� ���� ���� �����δ� 
enum {
	SECURITY_LOBY = 1,
	O2_LOBY,
	ADMIN_LOBY,
	CAFETERIA,
	O2,
	SECURITY,
	ADMIN,
	LOBY
};

class MapManager : public SingletonBase<MapManager>
{
public:
	friend class SingletonBase<MapManager>;

	MapManager();
	~MapManager();

	//�÷��̾ ����ִ��� �������� �� ��ȯ����(��Ʈ����)
	//�׸��� int�� �����Ϳ� ��ġ�� ������(enum)
	string WhereIsPlayer(RECT playerRect , int * playerArea);


	vector<vector<D3DXVECTOR3>> GetMapBorder(string keyName) { return mMapBorder.find(keyName)->second; };

private:
	void init();

	void insertMap();

	void setLoby(); //���Ӵ���

	void setCafeTeria();

	void setO2();
	void setO2Loby();

	void setSecurity();
	void setSecurityLoby();

	void setAdmin();
	void setAdminLoby();



private:

	//TODO::���߿� ����ȭ �غ���.. ���;��� ���� ���⼭�� �� ����� �������� ū��..
	//�پ��ִ� ������ ���� �������			�� Ű��
	vector<vector<D3DXVECTOR3>> mLoby;	//Loby - ���� ����

	vector<vector<D3DXVECTOR3>> mCafeTeriaBorder;	//CafeTeria

	vector<vector<D3DXVECTOR3>> mO2Border;			//O2
	vector<vector<D3DXVECTOR3>> mO2LobyBorder;		//O2Loby

	vector<vector<D3DXVECTOR3>> mSecurityBorder;	//Security
	vector<vector<D3DXVECTOR3>> mSecurityLobyBorder;//SecurityLoby


	vector<vector<D3DXVECTOR3>> mAdminBorder;		//Admin
	vector<vector<D3DXVECTOR3>> mAdminLobyBorder;	//AdminLoby



	//�� ���� ���� RECT l -t -r -b ��
	RECT mCafeTeriaRect = {1879, 2848, 3501, 1355};

	RECT mO2Rect = {699, 2218, 1188, 1896};
	RECT mO2LobyRect = {1188,2216,1879,2056};

	RECT mSecurityRect = {3773, 2497, 4195, 1886};
	RECT mSecurityLobyRect = {3501, 2214, 3774, 2057};

	RECT mAdminRect = { 1587, 1047, 2302, 516 };
	RECT mAdminLobyRect = {2303, 1354, 2791,881};

	//[]�� �غ��� ����
	unordered_map<string, vector<vector<D3DXVECTOR3>>> mMapBorder;
};

