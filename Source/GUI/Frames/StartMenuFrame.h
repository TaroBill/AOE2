#pragma once
#include "Frame.h"
#include <vector>
#include "../Buttons/Button.h"

class StartMenuFrame : public Frame
{
public:
	StartMenuFrame();
	~StartMenuFrame();
	void loadBitmap() override;
	void OnShow();
	void onMove() override;
	void LoadButtons();
};
