#pragma once
#include "Frame.h"
#include <vector>
#include<typeinfo>


class EntityDataButtonFrame : public Frame
{
public:
	EntityDataButtonFrame();
	~EntityDataButtonFrame();
	void loadBitmap() override;
	void OnShow();
	void onMove() override;
	void LoadEmpty();
	void LoadMapEditorButtons();
	void LoadVillagerButtons();
	void LoadBuildingButtons();
};

