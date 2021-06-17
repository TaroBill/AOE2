#pragma once
#include "Button.h"
#include "../../World.h"

class House_Button : public Button {

public:
	House_Button() : Button(40, SIZE_Y - 240 + 40, 40, 40, true)
	{
		loadBitmap();
	}
	~House_Button()
	{

	}
	void loadBitmap() override {
		texture.LoadBitmap(IDB_HOUSE_BUTTON);
	}

	void onClicked() override {
		World::getInstance()->spawningEntity(IDB_TOWNCENTER_ICON);
	}
};
