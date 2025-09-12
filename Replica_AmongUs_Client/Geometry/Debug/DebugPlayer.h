#pragma once
#include "../Line.h"

class DebugPlayer : public Line
{
public:
	DebugPlayer();
	~DebugPlayer();

	virtual void Update() final;
	virtual void Render(D3DXVECTOR2 playerTrans, D3DXVECTOR2 playerSize, float guideSize);

private:


};

