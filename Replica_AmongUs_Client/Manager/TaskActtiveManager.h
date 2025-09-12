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

	//미션을 성공하면 true 반환 실패거나 그냥 나가면 false
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

	//테스크가 활성화 중인가?? Create될때 true로 바뀌며
	//완료되거나 꺼지면 false다
	bool mIsActtive = false;

	//

	bool mTaskComplete = false;
	bool mClickEnd = false;
};

