#pragma once

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
using namespace game_framework;
enum mapItem { GRASS, RIVER };
class World {
public:
	World();
	void OnShow();
	int getScreenX();
	int getScreenY();
	int getGlobalX(int);
	int getGlobalY(int);
	int GlobalX2ScreenX(int);
	int GlobalX2ScreenY(int);
	int getLocationItem(int, int);
	void LoadBitMap();
	CMovingBitmap grass;
	CMovingBitmap river;
	void moveScreenUp(bool);
	void moveScreenDown(bool);
	void moveScreenLeft(bool);
	void moveScreenRight(bool);
	void onMove();
private:
	bool isMovingLeft, isMovingRight, isMovingUp, isMovingDown;
	void initMap();
	int map[120][120];
	int sx, sy;
};
