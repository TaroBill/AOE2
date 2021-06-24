#pragma once
#include "Frame.h"
#include <vector>
#include "../Buttons/Button.h"

class HelpFrame : public Frame
{
public:
	HelpFrame();
	~HelpFrame();
	void loadBitmap() override;
	void OnShow();
	void onMove() override;
	void LoadButtons();
};
