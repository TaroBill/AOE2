#pragma once
#include "Button.h"


class Military_Button : public Button {

public:
	Military_Button() : Button(50, SIZE_Y - 300 + 50, 40, 40, true)
	{
		loadBitmap();
	}
	~Military_Button()
	{

	}
	void loadBitmap() override {
		Button::texture.LoadBitmap(IDB_MILITARY_BUTTON);
	}

	void onClicked() override {

	}
};
