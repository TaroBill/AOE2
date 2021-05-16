#pragma once
#include "Button.h"

class MultiGameButton : public Button
{

public:
	MultiGameButton();
	~MultiGameButton();
	void loadBitmap();
	void OnShow();
	void onClicked() override;
};
