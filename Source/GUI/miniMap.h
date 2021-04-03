#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include "../World.h"

using namespace game_framework;
class MiniMap {
public:
	MiniMap();
	MiniMap(int, int, string);
	void OnShow();
	void LoadBitMap();
	CMovingBitmap map;
	CMovingBitmap CurrentLocation;
	bool isInMiniMap(int, int);
	void setCurrentLocation(int, int);
	CPoint MiniMapLoc2GlobalLoc(CPoint);
private:
	string Name;
	int h, w;
	int x, y;
	int CurrentLocationX, CurrentLocationY;
};
