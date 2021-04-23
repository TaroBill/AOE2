#pragma once
#include "Button.h"
//#include "../GUI.h"
//#include "../EntityDataButtonFrame.h"

class Building_Button : public Button
{

public:
	Building_Button() : Button(10, SIZE_Y - 300 + 10, 40, 40, true)
	{
		loadBitmap();
	}
	~Building_Button()
	{

	}
	void loadBitmap() override {
		texture.LoadBitmap(IDB_BUILDING_BUTTON);
	}

	void onClicked() override {
		//GUI::getInstance()->entityDataButtonFrame.LoadBuildingButtons();
	}
};
