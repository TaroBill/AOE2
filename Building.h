#pragma once

#include "Component.h"
#include "./Source/gamelib.h"

namespace composite
{
	class Building :Component
	{
		int x, y;
		int sizeX, sizeY;
		int hp;
		int lineOfSight;
		//�ŧi��
		game_framework::CMovingBitmap buildingBitmap;
	};
}