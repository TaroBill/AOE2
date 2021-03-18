#pragma once

#include "Component.h"

namespace composite
{
	class Building :Component
	{
		int x, y;
		int hp;
		int lineOfSight;
	};
}