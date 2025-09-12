#include "../stdafx.h"
#include "MapManager.h"

MapManager::MapManager()
{
	init();
}

MapManager::~MapManager()
{
}

string MapManager::WhereIsPlayer(RECT playerRect, int * playerArea)
{
	if (SceneManager::Get()->GetScene() == SCENE_LOBY) { 
		*(playerArea) = LOBY;		
		int a = 0;
		string loby = "Loby";
		return loby;
	}

	if (Collision::Get()->AabbCollision(playerRect, mSecurityLobyRect) == true)	{ *(playerArea) = SECURITY_LOBY;return "SecurityLoby";}
	if (Collision::Get()->AabbCollision(playerRect, mO2LobyRect) == true)		{ *(playerArea) = O2_LOBY;		return "O2Loby";	}
	if (Collision::Get()->AabbCollision(playerRect, mAdminLobyRect) == true)	{ *(playerArea) = ADMIN_LOBY;	return "AdminLoby";	}
	if (Collision::Get()->AabbCollision(playerRect, mCafeTeriaRect) == true)	{ *(playerArea) = CAFETERIA;	return "CafeTeria";	}
	if (Collision::Get()->AabbCollision(playerRect, mO2Rect) == true)			{ *(playerArea) = O2;			return "O2";		}
	if (Collision::Get()->AabbCollision(playerRect, mSecurityRect) == true)		{ *(playerArea) = SECURITY;		return "Security";	}
	if (Collision::Get()->AabbCollision(playerRect, mAdminRect) == true)		{ *(playerArea) = ADMIN;		return "Admin";		}
	
	
	return NULL;
}

void MapManager::init()
{
	setLoby();

	setCafeTeria();

	setO2();
	setO2Loby();

	setSecurity();
	setSecurityLoby();

	setAdmin();
	setAdminLoby();

	insertMap();
}

void MapManager::insertMap()
{
	mMapBorder.insert(make_pair("Loby", mLoby));

	mMapBorder.insert(make_pair("Admin", mAdminBorder));
	mMapBorder.insert(make_pair("AdminLoby", mAdminLobyBorder));
	mMapBorder.insert(make_pair("CafeTeria", mCafeTeriaBorder));
	mMapBorder.insert(make_pair("O2", mO2Border));
	mMapBorder.insert(make_pair("O2Loby", mO2LobyBorder));
	mMapBorder.insert(make_pair("Security", mSecurityBorder));
	mMapBorder.insert(make_pair("SecurityLoby", mSecurityLobyBorder));
}

void MapManager::setLoby()
{
	vector<D3DXVECTOR3> tempVector;

	tempVector.push_back(D3DXVECTOR3(1010, 726, 0));
	tempVector.push_back(D3DXVECTOR3(1694, 726, 0));
	tempVector.push_back(D3DXVECTOR3(1749, 801, 0));
	tempVector.push_back(D3DXVECTOR3(1749, 1159, 0));
	tempVector.push_back(D3DXVECTOR3(1500, 1250, 0));
	tempVector.push_back(D3DXVECTOR3(1206, 1250, 0));
	tempVector.push_back(D3DXVECTOR3(962, 1161, 0));
	tempVector.push_back(D3DXVECTOR3(962, 791, 0));
	tempVector.push_back(D3DXVECTOR3(1010, 726, 0));


	mLoby.push_back(tempVector);
}

void MapManager::setCafeTeria()
{
	vector<D3DXVECTOR3> tempVector[3];

	tempVector[0].push_back(D3DXVECTOR3(2591, 1355, 0));
	tempVector[0].push_back(D3DXVECTOR3(2251, 1355, 0));
	tempVector[0].push_back(D3DXVECTOR3(1894, 1712, 0));
	tempVector[0].push_back(D3DXVECTOR3(1894, 2056, 0));
	
	mCafeTeriaBorder.push_back(tempVector[0]);

	tempVector[1].push_back(D3DXVECTOR3(1894, 2216, 0));
	tempVector[1].push_back(D3DXVECTOR3(1894, 2567, 0));
	tempVector[1].push_back(D3DXVECTOR3(2173, 2847, 0));
	tempVector[1].push_back(D3DXVECTOR3(3078, 2847, 0));
	tempVector[1].push_back(D3DXVECTOR3(3488, 2436, 0));
	tempVector[1].push_back(D3DXVECTOR3(3488, 2214, 0));
	tempVector[1].push_back(D3DXVECTOR3(3502, 2214, 0));

	mCafeTeriaBorder.push_back(tempVector[1]);


	tempVector[2].push_back(D3DXVECTOR3(3501, 2057, 0));
	tempVector[2].push_back(D3DXVECTOR3(3491, 2057, 0));
	tempVector[2].push_back(D3DXVECTOR3(3491, 1720, 0));
	tempVector[2].push_back(D3DXVECTOR3(3126, 1355, 0));
	tempVector[2].push_back(D3DXVECTOR3(2772, 1355, 0));

	mCafeTeriaBorder.push_back(tempVector[2]);
}

void MapManager::setO2()
{
	vector<D3DXVECTOR3> tempVector;

	tempVector.push_back(D3DXVECTOR3(1188, 2216, 0));
	tempVector.push_back(D3DXVECTOR3(1092, 2216, 0));
	tempVector.push_back(D3DXVECTOR3(1056, 2199, 0));
	tempVector.push_back(D3DXVECTOR3(933, 2199, 0));
	tempVector.push_back(D3DXVECTOR3(872, 2138, 0));
	tempVector.push_back(D3DXVECTOR3(811, 2138, 0));
	tempVector.push_back(D3DXVECTOR3(701, 2028, 0));
	tempVector.push_back(D3DXVECTOR3(735, 2028, 0));
	tempVector.push_back(D3DXVECTOR3(767, 1996, 0));
	tempVector.push_back(D3DXVECTOR3(767, 1898, 0));
	tempVector.push_back(D3DXVECTOR3(869, 1898, 0));
	tempVector.push_back(D3DXVECTOR3(869, 1995, 0));
	tempVector.push_back(D3DXVECTOR3(895, 2027, 0));
	tempVector.push_back(D3DXVECTOR3(941, 2027, 0));
	tempVector.push_back(D3DXVECTOR3(966, 1998, 0));
	tempVector.push_back(D3DXVECTOR3(966, 1898, 0));
	tempVector.push_back(D3DXVECTOR3(1075, 1898, 0));
	tempVector.push_back(D3DXVECTOR3(1075, 1993, 0));
	tempVector.push_back(D3DXVECTOR3(1098, 2026, 0));
	tempVector.push_back(D3DXVECTOR3(1178, 2026, 0));
	tempVector.push_back(D3DXVECTOR3(1178, 2056, 0));
	tempVector.push_back(D3DXVECTOR3(1188, 2056, 0));

	mO2Border.push_back(tempVector);
}

void MapManager::setO2Loby()
{
	vector<D3DXVECTOR3> tempVector[2];

	tempVector[0].push_back(D3DXVECTOR3(1188, 2216, 0));
	tempVector[0].push_back(D3DXVECTOR3(1879, 2216, 0));

	mO2LobyBorder.push_back(tempVector[0]);

	tempVector[1].push_back(D3DXVECTOR3(1188, 2056, 0));
	tempVector[1].push_back(D3DXVECTOR3(1879, 2056, 0));

	mO2LobyBorder.push_back(tempVector[1]);
}

void MapManager::setSecurity()
{
	vector<D3DXVECTOR3> tempVector;

	tempVector.push_back(D3DXVECTOR3(3774, 2057, 0));
	tempVector.push_back(D3DXVECTOR3(3803, 2057, 0));
	tempVector.push_back(D3DXVECTOR3(3803, 2009, 0));
	tempVector.push_back(D3DXVECTOR3(3822, 2009, 0));

	tempVector.push_back(D3DXVECTOR3(3822, 1891, 0));
	tempVector.push_back(D3DXVECTOR3(4139, 1891, 0));
	tempVector.push_back(D3DXVECTOR3(4139, 2009, 0));

	tempVector.push_back(D3DXVECTOR3(4158, 2009, 0));
	tempVector.push_back(D3DXVECTOR3(4158, 2076, 0));
	tempVector.push_back(D3DXVECTOR3(4089, 2076, 0));
	tempVector.push_back(D3DXVECTOR3(4089, 2111, 0));
	tempVector.push_back(D3DXVECTOR3(4017, 2111, 0));

	tempVector.push_back(D3DXVECTOR3(4017, 2261, 0));
	tempVector.push_back(D3DXVECTOR3(4157, 2261, 0));

	tempVector.push_back(D3DXVECTOR3(4157, 2417, 0));
	tempVector.push_back(D3DXVECTOR3(4079, 2495, 0));
	tempVector.push_back(D3DXVECTOR3(3926, 2495, 0));
	tempVector.push_back(D3DXVECTOR3(3803, 2372, 0));

	tempVector.push_back(D3DXVECTOR3(3803, 2205, 0));
	tempVector.push_back(D3DXVECTOR3(3774, 2205, 0));

	mSecurityBorder.push_back(tempVector);
}

void MapManager::setSecurityLoby()
{
	vector<D3DXVECTOR3> tempVector[2];

	tempVector[0].push_back(D3DXVECTOR3(3501, 2214, 0));
	tempVector[0].push_back(D3DXVECTOR3(3733,2214, 0));
	tempVector[0].push_back(D3DXVECTOR3(3733, 2205, 0));
	tempVector[0].push_back(D3DXVECTOR3(3774, 2205, 0));

	mSecurityLobyBorder.push_back(tempVector[0]);


	tempVector[1].push_back(D3DXVECTOR3(3501, 2057, 0));
	tempVector[1].push_back(D3DXVECTOR3(3774, 2057, 0));

	mSecurityLobyBorder.push_back(tempVector[1]);
}

void MapManager::setAdmin()
{
	vector<D3DXVECTOR3> tempVector[2];

	tempVector[0].push_back(D3DXVECTOR3(2302, 1019, 0));
	tempVector[0].push_back(D3DXVECTOR3(2152, 1019, 0));
	tempVector[0].push_back(D3DXVECTOR3(2133, 974, 0));
	tempVector[0].push_back(D3DXVECTOR3(1704, 974, 0));
	tempVector[0].push_back(D3DXVECTOR3(1704, 1045, 0));
	tempVector[0].push_back(D3DXVECTOR3(1631, 1045, 0));
	tempVector[0].push_back(D3DXVECTOR3(1591, 1005, 0));
	tempVector[0].push_back(D3DXVECTOR3(1591, 1005, 0));
	tempVector[0].push_back(D3DXVECTOR3(1591, 643, 0));
	tempVector[0].push_back(D3DXVECTOR3(1716, 518, 0));
	tempVector[0].push_back(D3DXVECTOR3(2295, 518, 0));
	tempVector[0].push_back(D3DXVECTOR3(2295, 883, 0));
	tempVector[0].push_back(D3DXVECTOR3(2303, 883, 0));

	mAdminBorder.push_back(tempVector[0]);

	tempVector[1].push_back(D3DXVECTOR3(1767, 835, 0));
	tempVector[1].push_back(D3DXVECTOR3(1767, 688, 0));
	tempVector[1].push_back(D3DXVECTOR3(2107, 688, 0));
	tempVector[1].push_back(D3DXVECTOR3(2107, 835, 0));
	tempVector[1].push_back(D3DXVECTOR3(1767, 835, 0));

	mAdminBorder.push_back(tempVector[1]);
}

void MapManager::setAdminLoby()
{
	vector<D3DXVECTOR3> tempVector[2];

	tempVector[0].push_back(D3DXVECTOR3(2591, 1355, 0));
	tempVector[0].push_back(D3DXVECTOR3(2591, 1198, 0));
	tempVector[0].push_back(D3DXVECTOR3(2573, 1198, 0));
	tempVector[0].push_back(D3DXVECTOR3(2573, 1019, 0));
	tempVector[0].push_back(D3DXVECTOR3(2302, 1019, 0));


	mAdminLobyBorder.push_back(tempVector[0]);

	tempVector[1].push_back(D3DXVECTOR3(2303, 883, 0));
	tempVector[1].push_back(D3DXVECTOR3(2788, 883, 0));
	tempVector[1].push_back(D3DXVECTOR3(2788, 1198, 0));
	tempVector[1].push_back(D3DXVECTOR3(2772, 1198, 0));
	tempVector[1].push_back(D3DXVECTOR3(2772, 1355, 0));

	mAdminLobyBorder.push_back(tempVector[1]);
}
