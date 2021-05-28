#pragma once
#include "Frame.h"
#include <vector>
#include "../Buttons/Button.h"

class ServerFrame : public Frame
{
public:
	ServerFrame();
	~ServerFrame();
	void loadBitmap() override;
	void OnShow();
	void onMove() override;
	void LoadButtons();
};
