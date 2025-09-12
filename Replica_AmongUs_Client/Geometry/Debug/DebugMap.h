#pragma once
class DebugMap : public Line
{
public:

	DebugMap();
	~DebugMap();

	virtual void Update() override;
	virtual void Render() override;

private:
	
	void vbUpdateAndDraw(string mapName);
};

