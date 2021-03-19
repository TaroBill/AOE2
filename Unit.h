#pragma once

#include "Component.h"
#include <Vector>

namespace composite
{
	class Unit :Component
	{
		int x, y;
		int hp;
		int lineOfSight;
		int moveSpeed;
		enum State
		{
			idle,walk,attack,die
		};
		std::vector<int[2]> moveList;
		void move(int x, int y);
	};
}