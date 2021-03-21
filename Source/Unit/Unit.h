#pragma once

#include "Component.h"

#include <Vector>

#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"

namespace GameObject
{
	class Unit :Component
	{
		int pointX, pointY;
		int tileX, tileY;
		int hp;
		int lineOfSight;
		int moveSpeed;
		enum State
		{
			idle, walk, attack, die
		};
		State state;
		std::vector<int[2]> moveList;
		void move(int x, int y);
		game_framework::CAnimation ani;
	};
}