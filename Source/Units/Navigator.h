#pragma once
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "UnitBase.h"
//using namespace std;

namespace Unit
{
	class Navigator :public UnitBase
	{
	public:
		//移動用計數器
		//當位移量小於1時，會將位移量累加至計數器
		//當計數器數值達到至少正負1時，將數值使用於移動
		float counterF[2];

		//速度調整
		float speedFixed;
		
		//起始點座標
		CPoint startPoint;

		//起始格座標
		CPoint startTile;

		//目標點座標
		CPoint targetPoint;

		//目標格座標
		CPoint targetTile;

		//路徑點座標
		vector <CPoint> pathPoints;

		//路徑長
		vector<float> pathDistances;

		//正規化的下個點座標
		float normalNextPoint[2];


		//point2tile
		CPoint Point2Tile(CPoint);
		//tile2point
		CPoint Tile2Point(CPoint);

		//取得二維向量長度

		float GetLength(CPoint vector);
		//開始尋路
		void FindPath(int targetPointX, int targetPointY);
		void FindPath(CPoint targetPoint);
		//利用Component找物件
		template<typename T>
		void FindEntityPath()
		{
			
		}
		//正規化
		CPoint Normalization(CPoint start, CPoint end);
		void Normalization(CPoint start, CPoint end,float normal[2]);

		//移動一步
		//0路上
		//1到達
		//-1目前沒有路徑要進行
		int onMove(CPoint* point);
		//直線移動
		//往下個點直線走去
		void MoveStraight(CPoint* point);
		//直線尋路
		//直接將終點設為下個點
		void Straight();
		//直線尋路
		//直接將終點設為下個點
		void Straight(CPoint a,CPoint b);

		//Astar尋路
		//將每個轉角or格子設為下個點
		void AStar();

		Navigator();
	};
};