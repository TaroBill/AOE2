#pragma once
#include "Button.h"
#include "../Frames/EntityDataButtonFrame.h"

class Water_Button : public Button
{

public:
	Water_Button();
	~Water_Button();
	void loadBitmap();

	void onClicked() override;
private:
};
