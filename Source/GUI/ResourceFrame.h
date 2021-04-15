#pragma once
#include "Frame.h"

class ResourceFrame : public Frame
{
public:
	ResourceFrame();
	~ResourceFrame();
	void LoadBitmap() override;
	void onClicked(CPoint) override;
private:
	vector<Button> buttons;
};