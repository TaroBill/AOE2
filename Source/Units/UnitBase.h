#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"

class UnitBase
{
public:
	int tileX, tileY;
	int hp;
	int movingSpeed;
	int playerId;
	CMovingBitmap bmp;
	void findpath(int tileX, int tileY, int& map)
	{

	}
};