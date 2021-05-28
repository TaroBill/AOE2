#pragma once
#include "Frame.h"
#include <vector>
#include<typeinfo>
#include "../Buttons/Building_Button.h"
#include "../Buttons/Military_Button.h"
#include "../Buttons/House_Button.h"


class EntityDataButtonFrame : public Frame
{
public:
	EntityDataButtonFrame();
	~EntityDataButtonFrame();
	void loadBitmap() override;
	void OnShow();
	void onMove() override;
	void LoadEmpty();
	void LoadVillagerButtons();
	void LoadBuildingButtons();
};

