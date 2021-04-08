#pragma once
#include "Entity.h"
#include <vector>

namespace Unit
{
	class Navigator :public UnitBase
	{
		int counterX;
		int counterY;
		float counterXF;
		float counterYF;
	public:
		float speedFixed;
		int targetPoint[2];
		int targetTile[2];
		vector<float> pathPointXs;
		vector<float> pathPointYs;
		vector<float> pathDistances;
		float normalNextPoint[2];

		float GetLength(int vectorX, int vectorY)
		{
			return static_cast<float>(sqrt(vectorX* vectorX+ vectorY* vectorY));
		}
		float GetLength(float vectorX, float vectorY)
		{
			return static_cast<float>(sqrt(vectorX * vectorX + vectorY * vectorY));
		}
		void Findpath(int pointX, int pointY)
		{
			int nowX = GetParent<Entity>()->pointX;
			int nowY = GetParent<Entity>()->pointY;
			targetPoint[0] = pointX;
			targetPoint[1] = pointY;
			pathDistances.clear();
			//pathPointXs.push_back(targetPoint[0]);
			//pathPointYs.push_back(targetPoint[0]);
			Normalization(targetPoint[0], targetPoint[1]);
			pathDistances.push_back(GetLength(nowX - pointX, nowY - pointY));

		}
		void Normalization(int targetX, int targetY)
		{
			int nowX = GetParent<Entity>()->pointX;
			int nowY = GetParent<Entity>()->pointY;
			int deltaX = targetX - nowX;
			int deltaY =  targetY - nowY;

			float l = GetLength(deltaX, deltaY);
			float NormalX = deltaX / l;
			float NormalY = deltaY / l;

			normalNextPoint[0] = (NormalX);
			normalNextPoint[1] = (NormalY);
		}

		void onMove(int* pointX, int* pointY)
		{

			if (pathDistances.size() > 0)
			{
				Staright(pointX, pointY);
			}
		}
		void Staright(int* pointX, int* pointY)
		{
			counterXF += normalNextPoint[0] * speedFixed;
			counterYF += normalNextPoint[1] * speedFixed;
			*pointX += static_cast<int>(counterXF);
			*pointY += static_cast<int>(counterYF);
			//pathDistances.at(0) -= GetLength(counterXF, counterYF);

			pathDistances.at(0) = GetLength(targetPoint[0]-*pointX, targetPoint[1]-*pointY);
			counterXF -= static_cast<int>(counterXF);
			counterYF -= static_cast<int>(counterYF);
			TRACE("%f\n", pathDistances.at(0));



			if (pathDistances.at(0) <= speedFixed)pathDistances.pop_back();
			//TRACE("%f,%f\n", normalNextPoint[0], normalNextPoint[1]);
			//TRACE("%d,%d\n", counterXF, counterYF);
		}
		void AStar(int targetTileX, int targetTileY, int** tileMap)
		{
			
			//vector<CPoint> openList
			//int cost = 0;
			//tileMap[targetTileY][targetTileX]
			
		}

		Navigator()
		{
			speedFixed = 15;
			counterXF = 0;
			counterYF = 0;
			for (int i = 0; i < 2; i++)
			{
				targetPoint[i] = { 0 };
				targetTile[i] = { 0 };
				normalNextPoint[i] = { 0 };
			}
		}
	};
}