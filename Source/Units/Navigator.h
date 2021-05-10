#pragma once
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "UnitBase.h"
#include "Entity.h"
#include <memory> 

using namespace std;
 struct threadInfo
{
	CPoint targetPoint;
	CPoint targetTile;
	CPoint startPoint;
	CPoint startTile;
	vector<CPoint> pathPoints;
	vector<float> pathDistance;
	threadInfo()
	{
		targetPoint = CPoint(0, 0);
		 targetTile = CPoint(0,0);
		 startPoint = CPoint(0, 0);
		 startTile = CPoint(0, 0);
	}
	~threadInfo()
	{

	}
};
namespace Unit
{
	class Navigator :public UnitBase
	{
	public:
		threadInfo Info;//傳遞給執行序函數的參數
		HANDLE hThead;//儲存直行序Handle
		DWORD dwThreadID;//儲存多執行序ID
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
		float velocity[2];

		//point2tile
		static CPoint Point2Tile(CPoint);
		//tile2point
		static CPoint Tile2Point(CPoint);
		//取得二維向量長度
		static float GetLength(CPoint vector);
		//正規化
		static CPoint Normalization(CPoint start, CPoint end);
		static void Normalization(CPoint start, CPoint end,float normal[2]);

		//現在點座標
		CPoint GetNowPoint();
		


		//開始尋路
		void FindPath(CPoint targrtPoint, vector<Entity*> entityList);
		void FindPath(CPoint targrtPoint);

		//利用Component找物件
		template<typename T>
		void FindEntityPath()
		{
			
		}

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
		//多執行序版Astar
		//DWORD WINAPI AStarSync(LPVOID pParam);
		Navigator();

		~Navigator();
	};
};