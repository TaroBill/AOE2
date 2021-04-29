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

		//point2tile
		int Point2Tile(int p);
		//tile2point
		int Tile2Point(int t);

		//取得二維向量長度
		float GetLength(int vectorX, int vectorY);
		//取得二維向量長度
		float GetLength(float vectorX, float vectorY);
		//開始尋路
		void FindPath(int nowX,int nowY,int targetPointX, int targetPointY);
		//利用Component找物件
		template<typename T>
		void FindEntityPath()
		{
			
		}
		//正規化
		void Normalization(int startX, int startY, int endX, int endY, float normal[2]);

		//移動一步
		//0路上
		//1到達
		//-1目前沒有路徑要進行
		int onMove(int* pointX, int* pointY);
		//直線移動
		//往下個點直線走去
		void MoveStraight(int* pointX, int* pointY);
		//直線尋路
		//直接將終點設為下個點
		void Straight(int nowX,int nowY,int targetPointX, int targetPointY);

		//Astar尋路
		//將每個轉角or格子設為下個點
		void AStar(int targetPointX, int targetPointY);

		Navigator();
	};
};