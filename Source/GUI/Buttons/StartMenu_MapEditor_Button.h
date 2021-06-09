#pragma once
#include "Button.h"

class MapEditorButton : public Button
{

public:
	MapEditorButton();
	~MapEditorButton();
	void loadBitmap();
	void OnShow();
	void onClicked() override;
};
