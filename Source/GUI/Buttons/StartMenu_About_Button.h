#pragma once
#include "Button.h"

class AboutButton : public Button
{

public:
	AboutButton();
	~AboutButton();
	void loadBitmap();
	void OnShow();
	void onClicked() override;
};
