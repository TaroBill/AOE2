#pragma once
#include "Frame.h"
#include <vector>
#include "Buttons/Building_Button.h"
#include "Buttons/Military_Button.h"
#include "Buttons/House_Button.h"


class EntityDataButtonFrame : public Frame
{
public:
	EntityDataButtonFrame();
	~EntityDataButtonFrame();
	void loadBitmap() override;
	void onClicked(CPoint) override;
	void OnShow();
	void LoadVillagerButtons();
	void LoadBuildingButtons();
private:
	vector<Button*> buttons;
};
