#pragma once
#include "Button.h"

class HelpButton : public Button
{

public:
	HelpButton();
	~HelpButton();
	void loadBitmap();
	void OnShow();
	void onClicked() override;
};
