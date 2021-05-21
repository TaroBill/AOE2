#pragma once
#include "Button.h"

class CreateServerButton : public Button
{

public:
	CreateServerButton();
	~CreateServerButton();
	void loadBitmap();
	void OnShow();
	void onClicked() override;
};
