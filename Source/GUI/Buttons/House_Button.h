#pragma once
#include "Button.h"


class House_Button : public Button {

public:
	House_Button() : Button(10, SIZE_Y - 300 + 10, 40, 40, true)
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

	}
};
