#pragma once
#include "Button.h"
#include "../Frames/EntityDataButtonFrame.h"

class Grass_Button : public Button
{

public:
	Grass_Button();
	~Grass_Button();
	void loadBitmap();

	void onClicked() override;
private:
};
