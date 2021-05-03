#pragma once
#include "Frame.h"
#include <vector>
#include "Buttons/Button.h"
#include "../Player/Player.h"

class ResourceFrame : public Frame
{
public:
	ResourceFrame();
	~ResourceFrame();
	void loadBitmap() override;
	void onClicked(CPoint) override;
	void OnShow();
private:
	vector<Button*> buttons;
};
