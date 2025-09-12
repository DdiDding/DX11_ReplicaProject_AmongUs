#pragma once


////////////////////////////////////////////////////////
//Include < ~ >
////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <array>
#include <string>
#include <assert.h>
#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <random>


using namespace std;


////////////////////////////////////////////////////////
//DirectX
////////////////////////////////////////////////////////

#include <dxgi.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")

////////////////////////////////////////////////////////
//Include " ~ "
////////////////////////////////////////////////////////
#include "Util/SingletonBase.h"
#include "Util/Keyboard.h"
#include "Util/Collision.h"

#include "System/Mouse.h"
#include "System/Time.h"


#include "Manager/ImageManager.h"
#include "Manager/AnimationManager.h"
#include "Manager/MapManager.h"
#include "Manager/SceneManager.h"
#include "Manager/FontManager.h"
#include "Manager/SceneManager.h"

#include "TcpClient/Structs.h"
#include "TcpClient/ClientData.h"


#include "Graphic.h"




////////////////////////////////////////////////////////
//Define
////////////////////////////////////////////////////////
#define SAFE_DELETE(p) { if(p) { delete(p); (p) = nullptr; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr; } }

#define ASSERT(hr) assert(SUCCEEDED(hr));

#define GETDEVICE Graphic::Get()->GetDevice()
#define GETDC Graphic::Get()->GetDC()

#define GETCAMERA PublicCamera::Get()->GetCamera()

#define WinMaxWidth 1280
#define WinMaxHeight 720
#define WinMaxWidthHalf 640
#define WinMaxHeightHalf 360


#define RED D3DXCOLOR(1,0,0,1)
#define BLUE D3DXCOLOR(0,0,1,1)
#define BLACK D3DXCOLOR(0,0,0,1)
#define WHITE D3DXCOLOR(1,1,1,1)

#define SAFE_DELETE(p) { if(p) { delete(p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[](p); (p) = nullptr; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr; } }

#define PORT 1313
#define IP "127.0.0.1"

////////////////////////////////////////////////////////
//Function
////////////////////////////////////////////////////////

//벡터와 벡터 사이의 거리를 스칼라로 반환
//vec1 - Head
//vec2 - Tail
static float GetVectorLength(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2) {

	return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2));
}
static float GetVectorLength(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2) {

	return sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2));
}


////////////////////////////////////////////////////////
//Struct
////////////////////////////////////////////////////////

struct Ui_inGame_slotData
{
	Ui_inGame_slotData(bool isActtive, string taskKey) {

		mIsActtive = isActtive;
		mTaskKey = taskKey;
	}

	//슬롯이 활성화 되어있는지
	bool mIsActtive;
	//액티브 테스크 키값
	string mTaskKey;
};


////////////////////////////////////////////////////////
//Static
////////////////////////////////////////////////////////
static random_device rd;
static mt19937 gen(rd());