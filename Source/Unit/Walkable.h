#pragma once

#include "Component.h"
namespace GameObject
{
	class Walkable :Component
	{
	public:
		int moveSpeed;
		void walk(int x,int y);


	};
}