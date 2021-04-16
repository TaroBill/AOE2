#pragma once
#include "Entity.h"
#include <vector>
#include <map>
#include "World.h"
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
		void FindPath(int targetPointX, int targetPointY)
		{
			int nowX = GetParent<Entity>()->pointX;
			int nowY = GetParent<Entity>()->pointY;
			pathDistances.clear();
			pathPointXs.clear();
			pathPointYs.clear();
			Straight(targetPointX, targetPointY);
		}
		//利用Component找物件
		void FindEntityPath(UnitBase ub)
		{

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
		//0路上
		//1到達
		//-1目前沒有路徑要進行
		int onMove(int* pointX, int* pointY)
		{
			if (pathDistances.size() > 0)
			{
				GetParent<Entity>()->entityState = Entity::State::Move;
				Normalization(*pointX, *pointY, pathPointXs.at(0), pathPointYs.at(0), normalNextPoint);

				MoveStraight(pointX, pointY);
				if (pathDistances.at(0) <= speedFixed)
				{
					pathDistances.pop_back();
					pathPointXs.pop_back();
					pathPointYs.pop_back();
					return 1;
				}
				return 0;
			}
			else
			{
				return -1;
				//GetParent<Entity>()->entityState = Entity::State::Idle;
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
			TRACE("%f,%f\n", normalNextPoint[0], normalNextPoint[1]);
			/*
			if (normalNextPoint[0]<0)
			{
				if (normalNextPoint[1]<0)GetParent<Entity>()->faceDirection = Entity::Direction::LeftUp;
				else if (normalNextPoint[1] == 0)GetParent<Entity>()->faceDirection = Entity::Direction::Left;
				else if (normalNextPoint[1] > 0)GetParent<Entity>()->faceDirection = Entity::Direction::LeftDown;
			}
			else if (normalNextPoint[0] == 0)
			{
				if (normalNextPoint[1] < 0)GetParent<Entity>()->faceDirection = Entity::Direction::Up;
				else if (normalNextPoint[1] == 0)GetParent<Entity>()->faceDirection = Entity::Direction::Down;
				else if (normalNextPoint[1] > 0)GetParent<Entity>()->faceDirection = Entity::Direction::Down;
			}
			else if (normalNextPoint[0] > 1)
			{
				if (normalNextPoint[1] < 0)GetParent<Entity>()->faceDirection = Entity::Direction::RightUp;
				else if (normalNextPoint[1] == 0)GetParent<Entity>()->faceDirection = Entity::Direction::Right;
				else if (normalNextPoint[1] > 0)GetParent<Entity>()->faceDirection = Entity::Direction::RightDown;
			}
			*/
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

		//直線尋路
		//直接將終點設為下個點
		void Straight(UnitBase targetComponent)
		{
			int nowX, nowY;
			nowX = GetParent<Entity>()->pointX;
			nowY = GetParent<Entity>()->pointY;
			//pathPointXs.push_back(targetPointX);
			//pathPointYs.push_back(targetPointY);
			Normalization(nowX, nowY, targetPoint[0], targetPoint[1], normalNextPoint);
			//pathDistances.push_back(GetLength(nowX - targetPointX, nowY - targetPointY));

		}

		//Astar尋路
		//將每個轉角or格子設為下個點
		void AStar(int x, int y, int cost, int map[][120])
		{
			
			vector<CPoint> close;
			vector<CPoint> open;
			CPoint cp = CPoint(GetParent<Entity>()->GetTileX(), GetParent<Entity>()->GetTileY());
			std::map<CPoint, int> gScore;//起點到CP點的距離
			std::map<CPoint, int> hScore;//評估函式，可以用距離、難易度
			std::map<CPoint, int> fScore;//g+h
			std::list<CPoint> s;
			vector<CPoint> came_from;//到目前的路徑
			open.push_back(cp);
			while (open.size() > 0)
			{
				//找最小值的CPoint給smallest
				int smallest = 0;
				CPoint n = open.at(smallest);
				if (n.x == x && n.y == y)//到了
				{
					//回傳(存放)路徑
				}
			
				//把n從open list刪掉
				//把n加入close list
				//for i in n的鄰居
					//if i in close (若i在close list，跳過他)
					//continue

			}
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