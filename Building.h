#pragma once

#include "Component.h"

namespace composite
{
	class Building :Component
	{
		int x, y;
		int sizeX, sizeY;
		int hp;
		int lineOfSight;
	};
}