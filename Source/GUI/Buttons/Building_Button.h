#pragma once
#include "Button.h"
#include "../EntityDataButtonFrame.h"

class Building_Button : public Button
{

public:
	Building_Button() : Button(40, SIZE_Y - 240 + 40, 40, 40, true)
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
private:
};
