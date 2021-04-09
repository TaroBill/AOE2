#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include "minimap.h"

using namespace game_framework;
class GUI {
public:
	GUI();
	void LoadBitMap();
	void onShow();
	bool isInGUI(int, int);
	MiniMap minimap;
	CMovingBitmap resourcesBackground;
	CMovingBitmap buttonBackground;
	CMovingBitmap entityDataBackground;
};
