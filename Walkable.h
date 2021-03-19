#pragma once

#include "Component.h"
namespace composite
{
	class Walkable :Component
	{
	public:
		int moveSpeed;
		void walk(int x,int y);


	};
}