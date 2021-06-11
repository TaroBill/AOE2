#pragma once
#include "Button.h"
#include "../Frames/EntityDataButtonFrame.h"

class Gold_Button : public Button
{

public:
	Gold_Button();
	~Gold_Button();
	void loadBitmap();

	void onClicked() override;
private:
};
