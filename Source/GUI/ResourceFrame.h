#pragma once
#include "Frame.h"
#include <vector>
#include "Buttons/Button.h"


class ResourceFrame : public Frame
{
public:
	ResourceFrame();
	~ResourceFrame();
	void loadBitmap() override;
	void onClicked(CPoint) override;
private:
	vector<Button*> buttons;
};
