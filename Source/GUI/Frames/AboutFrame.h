#pragma once
#include "Frame.h"
#include <vector>
#include "../Buttons/Button.h"

class AboutFrame : public Frame
{
public:
	AboutFrame();
	~AboutFrame();
	void loadBitmap() override;
	void OnShow();
	void onMove() override;
	void LoadButtons();
};
