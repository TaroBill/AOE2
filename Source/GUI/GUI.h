#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include "minimap.h"
#include "ResourceFrame.h"
#include "EntityDataFrame.h"
#include "EntityDataButtonFrame.h"

using namespace game_framework;
class GUI {
public:
	GUI();
	~GUI();
	static GUI* getInstance();
	void loadBitmap();
	void onShow();
	bool isInGUI(int, int);
	bool isInGUI(CPoint);
	void triggerOnClicked(CPoint);
	MiniMap minimap;
	ResourceFrame resourceFrame;
	EntityDataFrame entityDataFrame;
	EntityDataButtonFrame entityDataButtonFrame;
private:
	static GUI* instance;
};
