#pragma once
#include "../Geometry/InGame/AactiveTask/CafeTeria_UploadData.h"
#include "../Geometry/InGame/AactiveTask/Sequrity_Sequrity.h"
#include "../Geometry/InGame/AactiveTask/Admin_SwipeCard.h"
#include "../Geometry/InGame/AactiveTask/O2_ClienFilter.h"
#include "../Geometry/InGame/AactiveTask/Admin_Admin.h"


class TaskActtiveManager : public SingletonBase<TaskActtiveManager>
{
public:

	friend class SingletonBase<TaskActtiveManager>;
	

	bool CreateTask(string taskName);

	//�̼��� �����ϸ� true ��ȯ ���аų� �׳� ������ false
	bool Update(string * taskName);
	void Render(string taskName);

	bool GetTaskComplete() { return mTaskComplete;};
	void SetTaskComplete(bool value) { mTaskComplete = value;};

	bool GetClickEnd() { return mClickEnd; };
	void SetClickEnd(bool value) { mClickEnd = value; };

	bool GetIsActtive() { return mIsActtive; };
	void SetIsActtive (bool value) { mIsActtive = value; };//?

private:

	TaskActtiveManager();
	~TaskActtiveManager();

	CafeTeria_UploadData * mUploadData;
	Sequrity_Sequrity * mSequrity;
	Admin_SwipeCard * mSwipeCard;
	O2_ClienFilter * mClienFilter;
	Admin_Admin * mAdmin;

	//�׽�ũ�� Ȱ��ȭ ���ΰ�?? Create�ɶ� true�� �ٲ��
	//�Ϸ�ǰų� ������ false��
	bool mIsActtive = false;

	//

	bool mTaskComplete = false;
	bool mClickEnd = false;
};

