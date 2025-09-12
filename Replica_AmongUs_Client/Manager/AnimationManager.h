#pragma once

//한 프레임의 구조체
//프레임 하나 당 가지는 uv값 [2D므로 사각형의 uv를 가지므로 4개의 uv가 있다
struct FrameUv {

	FrameUv() {	};

	FrameUv(D3DXVECTOR2 uv0, D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3) {

		mUv0 = uv0;
		mUv1 = uv1;
		mUv2 = uv2;
		mUv3 = uv3;
	};

	//좌측하단
	D3DXVECTOR2 mUv0;
	//좌측상단
	D3DXVECTOR2 mUv1;
	//우측상단
	D3DXVECTOR2 mUv2;
	//우측하단
	D3DXVECTOR2 mUv3;
};


//한 애니메이션의 클래스
//하나의 애니메이션이 가져야할 멤버들을 가지고 있다
class Animation {
public:
	Animation() {};
	Animation(WCHAR * imageName, float width, float height, int maxFrame, float fps) {

		mWidth = width;
		mHeight = height;
		mMaxFrame = maxFrame;

		mFps = fps;

		mVecFrame.assign(maxFrame, FrameUv());

		mVecFrame.at(0).mUv0 = D3DXVECTOR2(123.0f, 0);

		mSrv = ImageManager::Get()->GetImage(imageName);
	}

public:

	float mWidth;
	float mHeight;

	UINT mMaxFrame;

	float mFps;
	
	vector<FrameUv> mVecFrame;

	ID3D11ShaderResourceView * mSrv;
};


//하나의 애니메이션인 AnimationClass를 관리하는 매니저 클래스
class AnimationManager : public SingletonBase<AnimationManager>
{
public:

	friend class SingletonBase<AnimationManager>;

	AnimationManager();
	~AnimationManager();
	//TODO::소멸시 메모리 해제 하기


	//프레임을 카운트해주는 기능
	//myFrame -> 클래스가 가지고있는 프레임
	//myTime -> 클래스가 가지고있는 독자적인 시간
	//frameTime -> 원하는 프레임 시간
	//isReverse -> 역순으로 카운트를 할것인가?
	void DoCountFrame(UINT * myFrame, UINT maxFrame, float * myTime, float frameTime, bool isReverse) {

		//정방향 재생
		if (isReverse == false) {
			//1. 경과시간을 더한다
			*myTime += Time::Get()->Delta();

			//애니메이션에서 요구하는 fps 시간이 넘으면 프레임증가
			if (frameTime < *myTime) {

				//시간 초기화
				*myTime = 0;

				//현재 프레임이 마지막 프레임이면 [ 증가되고 확인되는 로직이여서 여기서 마지막 확인하는게 맞다 ]
				if (*myFrame == (maxFrame - 1)) {
					*myFrame = 0;
				}
				else {
					(*myFrame)++;
				}
			}
		}
		//역방향 재생
		else {
			//1. 경과시간을 더한다
			*myTime += Time::Get()->Delta();

			//애니메이션에서 요구하는 fps 시간이 넘으면 프레임감소
			if (frameTime < *myTime) {

				//시간 초기화
				*myTime = 0;

				//현재 프레임이 마지막 프레임이면 [ 감소되고 확인되는 로직이여서 여기서 마지막 확인하는게 맞다 ]
				if (*myFrame == 0) {
					*myFrame = (maxFrame-1);
				}
				else {
					(*myFrame)--;
				}
			}
		}
	};



	//애니메이션을 가져옴
	Animation GetAnimation(string aniName) {
		return mMapAnimation.find(aniName)->second;
	}

	//매개변수의 Uv를 Animation의 원하는 프레임의 uv로 변경한다
	void SetUvFromAnimationUv(D3DXVECTOR2 & uv0, D3DXVECTOR2 & uv1, D3DXVECTOR2 & uv2, D3DXVECTOR2 & uv3, FrameUv vecUv, bool isLookingRight) {

		//지금의 프레임워크는 오른쪽방면이 정석이다
		//사진이 오른쪽을 향할때
		if (isLookingRight == true) {

			uv0 = vecUv.mUv0;
			uv1 = vecUv.mUv1;
			uv2 = vecUv.mUv2;
			uv3 = vecUv.mUv3;
		}
		//왼쪽을 향할때
		else {

			//좌측하단
			uv0 = vecUv.mUv3;
			//우측하단
			uv3 = vecUv.mUv0;

			//좌측상단
			uv1 = vecUv.mUv2;
			//우측상단
			uv2 = vecUv.mUv1;
		}
	}

	D3DXVECTOR2 GetOriginSize_player() { return mPlayerOriginSize; };

private:


	//생성시 가져야할 애니메이션을 모두 생성한다
	void Init() {
		createAnimation("Player_Walk", L"Resorce/Player/walk.png", 84, 110, 12, 0.06f);
		createAnimation("Player_Stand", L"Resorce/Player/stand.png", 84, 110, 1, 0.0f);
		createAnimation("Player_Kill", L"Resorce/Player/kill.png", 84, 110, 1, 0.00f);
		createAnimation("Player_Ghost", L"Resorce/Player/ghost.png", 103, 110, 46, 0.06f);
		createAnimation("Player_DieBody", L"Resorce/Player/DieBody.png", 84, 81, 32, 0.06f);
		createAnimation("Player_Spawn1", L"Resorce/Player/spawn1.png", 273, 168, 5, 0.5f);
		createAnimation("Player_Spawn2", L"Resorce/Player/spawn2.png", 273, 168, 9, 0.09f);
		

		//애니메이션아님 내가 분할하기 귀찮아서 한거임
		createAnimation("Ui_Play", L"Resorce/Ui/Ui_play.png", 904, 115, 8, 0.0f);
		
		createAnimation("Task_UploadData_Folder", L"Resorce/Task/UploadData/folder.png", 138, 66, 5, 0.08f);

		createAnimation("Task_CleanFilter_leftArrow", L"Resorce/Task/CleanFilter/leftArrow.png", 30, 48, 10, 0.03f);
		createAnimation("Task_CleanFilter_rightArrow", L"Resorce/Task/CleanFilter/rightArrow.png", 11, 21, 10, 0.03f);


		createAnimation("Kill_Imposter", L"Resorce/Kill/KillAniImposter.png", 486, 214, 33, 0.04f);
		createAnimation("Kill_Crew", L"Resorce/Kill/KillAniCrew.png", 486, 214, 33, 0.04f);
	}

	//애니메이션 만들어두기 (애니메이션이름, 프레임)

	//maxFrame = 총 장면이 5개다, 그럼 5 대입
	void createAnimation(string aniName, WCHAR * imageName, float width, float height, int maxFrame, float fps) {
		

		//맵에 저장하기 전까지 잠시 저장할 애니메이션 클래스
		Animation tempAni (imageName, width, height, maxFrame, fps);


		//프레임 하나의 가로길이(uv 좌표계)
		float tempX = 1.0f / maxFrame;

		//프레임당 각 uv값을 저장
		for (int frameIndex = 0; frameIndex < maxFrame; frameIndex++) {

			//캐릭터가 오른쪽을 바라보는 기준
			//왼쪽
			float left = (tempX * frameIndex);
			//오른쪽
			float right = left + tempX;

			//좌측 하단
			tempAni.mVecFrame.at(frameIndex).mUv0 = D3DXVECTOR2(left, 1);
			//좌측 상단
			tempAni.mVecFrame.at(frameIndex).mUv1 = D3DXVECTOR2(left, 0);
			//우측 상단
			tempAni.mVecFrame.at(frameIndex).mUv2 = D3DXVECTOR2(right, 0);
			//우측 하단
			tempAni.mVecFrame.at(frameIndex).mUv3 = D3DXVECTOR2(right, 1);
		}

		mMapAnimation.insert(make_pair(aniName, tempAni));
	};


	
	

private:

	unordered_map< string, Animation > mMapAnimation;


	//플레이어에 애니메이션에 관한 기본 사이즈
	D3DXVECTOR2 mPlayerOriginSize;
};

