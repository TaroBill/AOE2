#pragma once
#include "Button.h"
#include "../Frames/EntityDataButtonFrame.h"

class Building_Button : public Button
{

public:
	Building_Button();
	~Building_Button();
	void loadBitmap();

	void onClicked() override;
private:
};
