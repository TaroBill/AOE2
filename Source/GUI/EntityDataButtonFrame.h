#pragma once
#include "Frame.h"

class EntityDataButtonFrame : public Frame
{
public:
	EntityDataButtonFrame();
	~EntityDataButtonFrame();
	void LoadBitmap() override;
	void onClicked(CPoint) override;
private:
	vector<Button> buttons;
};