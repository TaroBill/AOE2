#pragma once
#include "Button.h"
#include "../Frames/EntityDataButtonFrame.h"

class Eraser_Button : public Button
{

public:
	Eraser_Button();
	~Eraser_Button();
	void loadBitmap();

	void onClicked() override;
private:
};
