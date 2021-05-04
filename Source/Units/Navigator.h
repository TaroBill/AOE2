#pragma once
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "UnitBase.h"
#include "Entity.h"
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
		static CPoint Point2Tile(CPoint);
		//tile2point
		static CPoint Tile2Point(CPoint);
		//取得二維向量長度
		static float GetLength(CPoint vector);
		//正規化
		static CPoint Normalization(CPoint start, CPoint end);
		static void Normalization(CPoint start, CPoint end,float normal[2]);
		static CPoint GetCentre(vector<Entity*> entities);
		void SetLeader(vector<Entity*> entities, CPoint centre);
		//現在點座標
		CPoint GetNowPoint();
		//小隊的其他人
		vector<Navigator*>others;
		Navigator* Leader;
		//是否為隊長，是的話則進行尋路，並不使用算法(目前)
		bool isLeader;
		//狀態
		//0路上
		//1到達
		//-1目前沒有路徑要進行
		int findPathState;
		//分離值
		//控制轉向速度，用以避免與其他隊友太近
		int separation;
		//對齊值
		//控制對齊其他隊友的速度
		int alignment;
		//凝聚值
		//
		int coherence;
		//感測範圍
		//用來偵測範圍內是否有障礙物
		int separationRange;
		//當使用
		float velocity[2];
		//分離
		//在群體內避免過於擁擠
		//包含避開障礙物
		void Separation(float[2]);
		//對齊
		//朝向群體的平均方向移動
		void Alignment(float[2]);
		//凝聚
		//向群體的平均位置移動
		void Cohesion(float [2]);
		//BoidsFlocking
		//
		void BoidsFlocking(CPoint *point);

		//開始尋路
		void FindPath(CPoint targrtPoint, vector<Entity*> entityList);
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

		Navigator();
	};
};