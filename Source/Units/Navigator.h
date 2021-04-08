#pragma once
#include "Entity.h"
#include <vector>

namespace Unit
{

	class Navigator :public UnitBase
	{
	public:
		//移動用計數器
		//當位移量小於1時，會將位移量累加至計數器
		//當計數器數值達到至少正負1時，將數值使用於移動
		float counterXF;
		float counterYF;

		//速度調整
		float speedFixed;

		//目標點座標
		int targetPoint[2];

		//目標格座標
		int targetTile[2];

		//路徑X座標
		vector<int> pathPointXs;

		//路徑Y座標
		vector<int> pathPointYs;

		//路徑長
		vector<float> pathDistances;

		//正規化的下個點座標
		float normalNextPoint[2];

		//取得二維向量長度
		float GetLength(int vectorX, int vectorY)
		{
			return static_cast<float>(sqrt(vectorX * vectorX + vectorY * vectorY));
		}
		//取得二維向量長度
		float GetLength(float vectorX, float vectorY)
		{
			return static_cast<float>(sqrt(vectorX * vectorX + vectorY * vectorY));
		}
		//開始尋路
		void Findpath(int targetPointX, int targetPointY)
		{
			int nowX = GetParent<Entity>()->pointX;
			int nowY = GetParent<Entity>()->pointY;
			pathDistances.clear();
			pathPointXs.clear();
			pathPointYs.clear();
			Straight(targetPointX, targetPointY);


		}
		//正規化
		void Normalization(int startX, int startY, int endX, int endY, float normal[2])
		{
			int deltaX = endX - startX;
			int deltaY = endY - startY;
			float l = GetLength(deltaX, deltaY);
			normal[0] = deltaX / l;
			normal[1] = deltaY / l;
		}

		//移動一步
		void onMove(int* pointX, int* pointY)
		{
			if (pathDistances.size() > 0)
			{
				Normalization(*pointX, *pointY, pathPointXs.at(0), pathPointYs.at(0), normalNextPoint);

				MoveStraight(pointX, pointY);
				if (pathDistances.at(0) <= speedFixed)
				{
					pathDistances.pop_back();
					pathPointXs.pop_back();
					pathPointYs.pop_back();
				}
			}
		}
		//直線移動
		//往下個點直線走去
		void MoveStraight(int* pointX, int* pointY)
		{
			counterXF += normalNextPoint[0] * speedFixed;
			counterYF += normalNextPoint[1] * speedFixed;
			*pointX += static_cast<int>(counterXF);
			*pointY += static_cast<int>(counterYF);
			pathDistances.at(0) = GetLength(pathPointXs.at(0) - *pointX, pathPointYs.at(0) - *pointY);
			counterXF -= static_cast<int>(counterXF);
			counterYF -= static_cast<int>(counterYF);
		}
		//直線尋路
		//直接將終點設為下個點
		void Straight(int targetPointX, int targetPointY)
		{
			int nowX, nowY;
			nowX = GetParent<Entity>()->pointX;
			nowY = GetParent<Entity>()->pointY;
			pathPointXs.push_back(targetPointX);
			pathPointYs.push_back(targetPointY);
			Normalization(nowX, nowY, targetPoint[0], targetPoint[1], normalNextPoint);
			pathDistances.push_back(GetLength(nowX - targetPointX, nowY - targetPointY));
		}
		//Astar尋路
		//將每個轉角or格子設為下個點
		void AStar(int targetTileX, int targetTileY, int** tileMap)
		{
		}

		Navigator()
		{
			speedFixed = 5;
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