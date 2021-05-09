#pragma once
#include "Button.h"
#include "../../socket/NetWork.h"


class Military_Button : public Button {

public:
	Military_Button() : Button(90, SIZE_Y - 240 + 40, 40, 40, true)
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
		NetWork::getInstance()->SendData();
	}
};
