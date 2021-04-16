#pragma once
#include "Frame.h"

class EntityDataFrame : public Frame
{
public:
	EntityDataFrame();
	~EntityDataFrame();
	void LoadBitmap() override;
	void onClicked(CPoint) override;
private:
	vector<Button> buttons;
};