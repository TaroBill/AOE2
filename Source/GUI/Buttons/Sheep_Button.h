#pragma once
#include "Button.h"
#include "../Frames/EntityDataButtonFrame.h"

class Sheep_Button : public Button
{

public:
	Sheep_Button();
	~Sheep_Button();
	void loadBitmap();

	void onClicked() override;
private:
};
