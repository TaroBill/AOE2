#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include "../World.h"
#include "Frame.h"

using namespace game_framework;
class MiniMap  : public Frame{
public:
	MiniMap();
	~MiniMap();
	void LoadBitmap() override;
	void OnShow();
	MiniMap(int, int, string);
	bool isInMiniMap(int, int);
	void setCurrentLocation(int, int);
	void onClicked(CPoint) override;
	CPoint MiniMapLoc2GlobalLoc(CPoint);
private:
	string Name;
	CMovingBitmap CurrentLocation;
	int CurrentLocationX, CurrentLocationY;
};
