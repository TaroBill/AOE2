#pragma once
#include "Button.h"

class JoinServerButton2 : public Button
{

public:
	JoinServerButton2();
	~JoinServerButton2();
	void loadBitmap();
	void OnShow();
	void onClicked() override;
};
