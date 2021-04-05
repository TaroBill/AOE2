#pragma once
#include "Entity.h"
#include <vector>
namespace Unit
{
	class Navigator :Entity
	{
	public:
		int movingSpeed = 0;
		CPoint* path;
		virtual void Findpath(int tileX, int tileY, int& map)
		{
		}
		void AStar(int targetTileX, int targetTileY, int** tileMap)
		{
			/*
			vector<CPoint> openList
			int cost = 0;
			tileMap[targetTileY][targetTileX]
			*/
		}
		Navigator()
		{

		}
	};
}