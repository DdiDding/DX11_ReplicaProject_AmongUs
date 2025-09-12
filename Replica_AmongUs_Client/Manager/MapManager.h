#pragma once

//비트연산으로 현재 위치를 알아낸다.
//로비에 걸쳤는지 안걸쳤는지는 기준 숫자 밑으로는 
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

	//플레이어가 어디있는지 이진수로 값 반환해줌(비트연산)
	//그리고 int형 포인터에 위치를 저장함(enum)
	string WhereIsPlayer(RECT playerRect , int * playerArea);


	vector<vector<D3DXVECTOR3>> GetMapBorder(string keyName) { return mMapBorder.find(keyName)->second; };

private:
	void init();

	void insertMap();

	void setLoby(); //게임대기실

	void setCafeTeria();

	void setO2();
	void setO2Loby();

	void setSecurity();
	void setSecurityLoby();

	void setAdmin();
	void setAdminLoby();



private:

	//TODO::나중에 최적화 해보기.. 벡터안의 벡터 여기서는 좀 비용이 쓸때없이 큰듯..
	//붙어있는 복도와 같이 들어있음			각 키값
	vector<vector<D3DXVECTOR3>> mLoby;	//Loby - 게임 대기실

	vector<vector<D3DXVECTOR3>> mCafeTeriaBorder;	//CafeTeria

	vector<vector<D3DXVECTOR3>> mO2Border;			//O2
	vector<vector<D3DXVECTOR3>> mO2LobyBorder;		//O2Loby

	vector<vector<D3DXVECTOR3>> mSecurityBorder;	//Security
	vector<vector<D3DXVECTOR3>> mSecurityLobyBorder;//SecurityLoby


	vector<vector<D3DXVECTOR3>> mAdminBorder;		//Admin
	vector<vector<D3DXVECTOR3>> mAdminLobyBorder;	//AdminLoby



	//각 구역 영역 RECT l -t -r -b 순
	RECT mCafeTeriaRect = {1879, 2848, 3501, 1355};

	RECT mO2Rect = {699, 2218, 1188, 1896};
	RECT mO2LobyRect = {1188,2216,1879,2056};

	RECT mSecurityRect = {3773, 2497, 4195, 1886};
	RECT mSecurityLobyRect = {3501, 2214, 3774, 2057};

	RECT mAdminRect = { 1587, 1047, 2302, 516 };
	RECT mAdminLobyRect = {2303, 1354, 2791,881};

	//[]로 해보기 ㅋㅋ
	unordered_map<string, vector<vector<D3DXVECTOR3>>> mMapBorder;
};

