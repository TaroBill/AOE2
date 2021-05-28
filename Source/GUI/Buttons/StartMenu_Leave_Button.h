#pragma once
#include "Button.h"

class LeaveButton : public Button
{

public:
	LeaveButton();
	~LeaveButton();
	void loadBitmap();
	void OnShow();
	void onClicked() override;
};
