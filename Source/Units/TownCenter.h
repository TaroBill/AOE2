#pragma once
#include "Entity.h"
#include "UnitBase.h"

namespace Unit
{
	class TownCenter :public Entity
	{
	public:
		void SetBitmap();
		void onMove();
		TownCenter(int pointX, int pointY);
		TownCenter(CPoint point);
		TownCenter();
	};
}