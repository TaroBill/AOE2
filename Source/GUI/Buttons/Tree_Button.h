#pragma once
#include "Button.h"
#include "../Frames/EntityDataButtonFrame.h"

class Tree_Button : public Button
{

public:
	Tree_Button();
	~Tree_Button();
	void loadBitmap();

	void onClicked() override;
private:
};
