#pragma once

//�� �������� ����ü
//������ �ϳ� �� ������ uv�� [2D�Ƿ� �簢���� uv�� �����Ƿ� 4���� uv�� �ִ�
struct FrameUv {

	FrameUv() {	};

	FrameUv(D3DXVECTOR2 uv0, D3DXVECTOR2 uv1, D3DXVECTOR2 uv2, D3DXVECTOR2 uv3) {

		mUv0 = uv0;
		mUv1 = uv1;
		mUv2 = uv2;
		mUv3 = uv3;
	};

	//�����ϴ�
	D3DXVECTOR2 mUv0;
	//�������
	D3DXVECTOR2 mUv1;
	//�������
	D3DXVECTOR2 mUv2;
	//�����ϴ�
	D3DXVECTOR2 mUv3;
};


//�� �ִϸ��̼��� Ŭ����
//�ϳ��� �ִϸ��̼��� �������� ������� ������ �ִ�
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


//�ϳ��� �ִϸ��̼��� AnimationClass�� �����ϴ� �Ŵ��� Ŭ����
class AnimationManager : public SingletonBase<AnimationManager>
{
public:

	friend class SingletonBase<AnimationManager>;

	AnimationManager();
	~AnimationManager();
	//TODO::�Ҹ�� �޸� ���� �ϱ�


	//�������� ī��Ʈ���ִ� ���
	//myFrame -> Ŭ������ �������ִ� ������
	//myTime -> Ŭ������ �������ִ� �������� �ð�
	//frameTime -> ���ϴ� ������ �ð�
	//isReverse -> �������� ī��Ʈ�� �Ұ��ΰ�?
	void DoCountFrame(UINT * myFrame, UINT maxFrame, float * myTime, float frameTime, bool isReverse) {

		//������ ���
		if (isReverse == false) {
			//1. ����ð��� ���Ѵ�
			*myTime += Time::Get()->Delta();

			//�ִϸ��̼ǿ��� �䱸�ϴ� fps �ð��� ������ ����������
			if (frameTime < *myTime) {

				//�ð� �ʱ�ȭ
				*myTime = 0;

				//���� �������� ������ �������̸� [ �����ǰ� Ȯ�εǴ� �����̿��� ���⼭ ������ Ȯ���ϴ°� �´� ]
				if (*myFrame == (maxFrame - 1)) {
					*myFrame = 0;
				}
				else {
					(*myFrame)++;
				}
			}
		}
		//������ ���
		else {
			//1. ����ð��� ���Ѵ�
			*myTime += Time::Get()->Delta();

			//�ִϸ��̼ǿ��� �䱸�ϴ� fps �ð��� ������ �����Ӱ���
			if (frameTime < *myTime) {

				//�ð� �ʱ�ȭ
				*myTime = 0;

				//���� �������� ������ �������̸� [ ���ҵǰ� Ȯ�εǴ� �����̿��� ���⼭ ������ Ȯ���ϴ°� �´� ]
				if (*myFrame == 0) {
					*myFrame = (maxFrame-1);
				}
				else {
					(*myFrame)--;
				}
			}
		}
	};



	//�ִϸ��̼��� ������
	Animation GetAnimation(string aniName) {
		return mMapAnimation.find(aniName)->second;
	}

	//�Ű������� Uv�� Animation�� ���ϴ� �������� uv�� �����Ѵ�
	void SetUvFromAnimationUv(D3DXVECTOR2 & uv0, D3DXVECTOR2 & uv1, D3DXVECTOR2 & uv2, D3DXVECTOR2 & uv3, FrameUv vecUv, bool isLookingRight) {

		//������ �����ӿ�ũ�� �����ʹ���� �����̴�
		//������ �������� ���Ҷ�
		if (isLookingRight == true) {

			uv0 = vecUv.mUv0;
			uv1 = vecUv.mUv1;
			uv2 = vecUv.mUv2;
			uv3 = vecUv.mUv3;
		}
		//������ ���Ҷ�
		else {

			//�����ϴ�
			uv0 = vecUv.mUv3;
			//�����ϴ�
			uv3 = vecUv.mUv0;

			//�������
			uv1 = vecUv.mUv2;
			//�������
			uv2 = vecUv.mUv1;
		}
	}

	D3DXVECTOR2 GetOriginSize_player() { return mPlayerOriginSize; };

private:


	//������ �������� �ִϸ��̼��� ��� �����Ѵ�
	void Init() {
		createAnimation("Player_Walk", L"Resorce/Player/walk.png", 84, 110, 12, 0.06f);
		createAnimation("Player_Stand", L"Resorce/Player/stand.png", 84, 110, 1, 0.0f);
		createAnimation("Player_Kill", L"Resorce/Player/kill.png", 84, 110, 1, 0.00f);
		createAnimation("Player_Ghost", L"Resorce/Player/ghost.png", 103, 110, 46, 0.06f);
		createAnimation("Player_DieBody", L"Resorce/Player/DieBody.png", 84, 81, 32, 0.06f);
		createAnimation("Player_Spawn1", L"Resorce/Player/spawn1.png", 273, 168, 5, 0.5f);
		createAnimation("Player_Spawn2", L"Resorce/Player/spawn2.png", 273, 168, 9, 0.09f);
		

		//�ִϸ��̼Ǿƴ� ���� �����ϱ� �����Ƽ� �Ѱ���
		createAnimation("Ui_Play", L"Resorce/Ui/Ui_play.png", 904, 115, 8, 0.0f);
		
		createAnimation("Task_UploadData_Folder", L"Resorce/Task/UploadData/folder.png", 138, 66, 5, 0.08f);

		createAnimation("Task_CleanFilter_leftArrow", L"Resorce/Task/CleanFilter/leftArrow.png", 30, 48, 10, 0.03f);
		createAnimation("Task_CleanFilter_rightArrow", L"Resorce/Task/CleanFilter/rightArrow.png", 11, 21, 10, 0.03f);


		createAnimation("Kill_Imposter", L"Resorce/Kill/KillAniImposter.png", 486, 214, 33, 0.04f);
		createAnimation("Kill_Crew", L"Resorce/Kill/KillAniCrew.png", 486, 214, 33, 0.04f);
	}

	//�ִϸ��̼� �����α� (�ִϸ��̼��̸�, ������)

	//maxFrame = �� ����� 5����, �׷� 5 ����
	void createAnimation(string aniName, WCHAR * imageName, float width, float height, int maxFrame, float fps) {
		

		//�ʿ� �����ϱ� ������ ��� ������ �ִϸ��̼� Ŭ����
		Animation tempAni (imageName, width, height, maxFrame, fps);


		//������ �ϳ��� ���α���(uv ��ǥ��)
		float tempX = 1.0f / maxFrame;

		//�����Ӵ� �� uv���� ����
		for (int frameIndex = 0; frameIndex < maxFrame; frameIndex++) {

			//ĳ���Ͱ� �������� �ٶ󺸴� ����
			//����
			float left = (tempX * frameIndex);
			//������
			float right = left + tempX;

			//���� �ϴ�
			tempAni.mVecFrame.at(frameIndex).mUv0 = D3DXVECTOR2(left, 1);
			//���� ���
			tempAni.mVecFrame.at(frameIndex).mUv1 = D3DXVECTOR2(left, 0);
			//���� ���
			tempAni.mVecFrame.at(frameIndex).mUv2 = D3DXVECTOR2(right, 0);
			//���� �ϴ�
			tempAni.mVecFrame.at(frameIndex).mUv3 = D3DXVECTOR2(right, 1);
		}

		mMapAnimation.insert(make_pair(aniName, tempAni));
	};


	
	

private:

	unordered_map< string, Animation > mMapAnimation;


	//�÷��̾ �ִϸ��̼ǿ� ���� �⺻ ������
	D3DXVECTOR2 mPlayerOriginSize;
};

