#pragma once
#include "Button.h"

class JoinServerButton : public Button
{

public:
	JoinServerButton();
	~JoinServerButton();
	void loadBitmap();
	void OnShow();
	void onClicked() override;
};
