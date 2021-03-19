#pragma once

#include "Component.h"

namespace composite
{
	class Unit :Component
	{
		int x, y;
		int hp;
		int lineOfSight;
		int moveSpeed;
		void move(int x, int y);
	};
}