#pragma once
#include "Button.h"
#include "../Frames/EntityDataButtonFrame.h"

class Stone_Button : public Button
{

public:
	Stone_Button();
	~Stone_Button();
	void loadBitmap();

	void onClicked() override;
private:
};
