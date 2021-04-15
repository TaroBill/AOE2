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
	void LoadBitmap();
	void onShow();
	bool isInGUI(int, int);
	void triggerOnClicked(CPoint);
	vector<Frame *> AllFrames;
	MiniMap minimap;
};
