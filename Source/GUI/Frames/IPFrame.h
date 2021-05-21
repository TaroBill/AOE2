#pragma once
#include "Frame.h"
#include <vector>
#include "../Buttons/Button.h"

class IPFrame : public Frame
{
public:
	IPFrame();
	~IPFrame();
	void loadBitmap() override;
	void OnShow();
	void onMove() override;
	void LoadButtons();
};
