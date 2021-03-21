#pragma once


#include "Building.h"
#include "Collectable.h"


namespace GameObject
{
	class GoldMine :public Building
	{
	public:
		Collectable c;
		GoldMine()
		{
		}

	};
	
}
