#pragma once
#include "Frame.h"
#include <map>
class EntityDataButtonFrame : public Frame
{
public:
	EntityDataButtonFrame();
	~EntityDataButtonFrame();
	void LoadBitmap() override;
	void onClicked(CPoint) override;
private:
	void LoadVillagerButtons();
	map<string, Button> buttons;
};