#pragma once
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "Navigator.h"
#include "Entity.h"
#include "../World.h"
#include <memory> 

using namespace std;
#pragma region Utility
//point2tile
CPoint Unit::Navigator::Point2Tile(CPoint p)
{

	CPoint np;
	np.x = p.x / 50;
	np.y = p.y / 50;
	return np;
};

//tile2point
CPoint Unit::Navigator::Tile2Point(CPoint p)
{
	CPoint np;
	np.x = p.x * 50;
	np.y = p.y * 50;
	return np;
};

//取得二維向量長度
float Unit::Navigator::GetLength(CPoint p)
{
	float temp = static_cast<float>(sqrt(p.x * p.x + p.y * p.y));
	return temp > 0 ? temp : 1;
}

//正規化
void Unit::Navigator::Normalization(CPoint start, CPoint end, float normal[2])
{
	CPoint delta = end - start;
	float l = GetLength(delta);
	normal[0] = delta.x / l;
	normal[1] = delta.y / l;
}



CPoint Unit::Navigator::GetNowPoint()
{
	return (this->GetParent<Entity>()->point);
}
#pragma endregion


//直線移動
//往下個點直線走去
//是移動的基礎
void Unit::Navigator::MoveStraight(CPoint* point)
{

	//浮點數counter累計
	for (unsigned int i = 0; i < 2; i++)counterF[i] += velocity[i] * speedFixed;
	//角色位移浮點數counter的整數部分
	*point += CPoint(static_cast<int>(counterF[0]), static_cast<int>(counterF[1]));
	//計算與下一個點的距離
	pathDistances.at(0) = GetLength(((pathPoints.at(0))) - *point);
	//浮點數counter的整數部分去除
	for (unsigned int i = 0; i < 2; i++)counterF[i] -= static_cast<int>(counterF[i]);
}



//移動一步
//0路上
//1到達
//-1目前沒有路徑要進行
int Unit::Navigator::onMove(CPoint* point)
{
	targetPoint = Info.targetPoint;
	targetTile = Info.targetTile;
	pathPoints = Info.pathPoints;
	pathDistances = Info.pathDistance;
	startPoint = Info.startPoint;
	startTile = Info.startTile;

	if (pathDistances.size() > 0 && pathPoints.size() > 0)
	{

		//GetParent<Entity>()->entityState = Entity::State::Move;
		Normalization(*point, (pathPoints.front()), velocity);

		MoveStraight(point);
		if (pathDistances.front() <= speedFixed)
		{
			Info.pathPoints.erase(Info.pathPoints.begin());
			Info.pathDistance.erase(Info.pathDistance.begin());
			if (pathDistances.size() <= 1)
			{
				return 1;
			}
		}
		return 0;
	}
	else
	{
		velocity[0] = 0;
		velocity[1] = 0;
		return -1;
	}
	return -1;
}

//直線尋路
//直接將終點設為下個點
void Unit::Navigator::Straight()
{
	pathPoints.push_back(targetPoint);
	pathDistances.push_back(GetLength(startPoint - targetPoint));
}
void Unit::Navigator::Straight(CPoint a, CPoint b)
{
	pathPoints.push_back(b);
	pathDistances.push_back(GetLength(a - b));
}






struct CPointCompare
{
	bool operator() (const CPoint& p1, const CPoint& p2) const
	{
		if (p1.x < p2.x)
			return true;
		if (p2.x < p1.x)
			return false;

		// a1==b1: continue with element 2
		if (p1.y < p2.y)
			return true;
		if (p2.y < p1.y)
			return false;

		return false; // early out
	}
};


//Astar尋路
//將每個轉角or格子設為下個點
DWORD WINAPI AStarSync(LPVOID p)
{


	vector<CPoint> close;//封閉list，存放已經被走訪的點
	vector<CPoint> open;//開啟list，存放可能被做為起點的點
	CPoint cp = CPoint(
		((threadInfo*)p)->startTile.x,
		((threadInfo*)p)->startTile.y
		);//每一輪起點
	std::map<CPoint, int, CPointCompare> gScore;//起點到CP點的距離
	std::map<CPoint, int, CPointCompare> hScore;//評估函式，可以用距離、難易度
	std::map<CPoint, int, CPointCompare> fScore;//g+h
	std::map<CPoint, CPoint, CPointCompare> come_from;//父節點
	open.push_back(cp);//起點加入openList

	//起點加入fscore
	fScore.insert(std::pair<CPoint, int>(cp, 0));
	hScore.insert(std::pair<CPoint, int>(cp, 0));
	gScore.insert(std::pair<CPoint, int>(cp, 0));


	while (open.size() > 0)
	{
		int minIndex = 0, minValue = INT32_MAX;
		//在openList中找最小值的CPoint作為這圈的開始
#pragma region FindMin


		for (unsigned int i = 0; i < open.size(); i++)
		{
			//比最小值還小
			if (fScore[open[i]] < minValue)
			{
				minValue = fScore[open[i]];
				minIndex = i;
			}
		}
#pragma endregion
		cp = open.at(minIndex);//起點變成有最小值f的點
		//周圍八方向的點
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				if (!(y == 0 && x == 0))//非自己
				{
					CPoint newPoint = (CPoint(cp.x + x, cp.y + y));
					bool continueFlag = false;
					for (unsigned i = 0; i < close.size(); i++)
					{
						if (close[i] == newPoint)
						{
							continueFlag = true;
							break;
						}
					}
					if (continueFlag)continue;

					//目前到這裡的cost
					int newGScore = gScore[cp] + 1;

					//評估cost
					int canPass = World::getInstance()->getLocationItem((newPoint).x * 50, (newPoint).y * 50);

					//canPass = 1 - canPass;
					//曼哈頓距離預測
					int newHScore = 1000 * canPass + (abs(((threadInfo*)p)->targetTile.x - (newPoint).x) + abs(((threadInfo*)p)->targetTile.y - (newPoint).y));

					int newFScore = newGScore + newHScore;


					gScore.insert(pair<CPoint, int>(newPoint, newGScore));
					hScore.insert(pair<CPoint, int>(newPoint, newHScore));
					fScore.insert(pair<CPoint, int>(newPoint, newFScore));
					open.push_back(newPoint);
					come_from.insert(pair<CPoint, CPoint>(newPoint, cp));

				}
			}
		}
		//cp加入close list
		close.push_back(cp);
		//cp從open list中刪除
		auto it = open.begin();
		for (unsigned int i = 0; i < open.size(); it++, i++)
		{
			if (*it == cp)
			{
				open.erase(it);
				break;
			}
		}


		if (cp == ((threadInfo*)p)->targetTile)//到了
		{
			stack<CPoint>stackPath;
			while (true)
			{
				stackPath.push(cp);
				if (cp == ((threadInfo*)p)->startTile)break;
				cp = come_from[cp];
			}
			unsigned int s = stackPath.size();
			for (unsigned int i = 0; i < s; i++)
			{
				((threadInfo*)p)->pathPoints.push_back(std::move(Unit::Navigator::Tile2Point(stackPath.top())));
				stackPath.pop();
				TRACE("%d,%d", ((threadInfo*)p)->pathPoints[i].x, ((threadInfo*)p)->pathPoints[i].y);
			}
			for (unsigned int i = 0; i < ((threadInfo*)p)->pathPoints.size() - 1; i++)
			{
				((threadInfo*)p)->pathDistance.push_back(std::move(Unit::Navigator::GetLength(((threadInfo*)p)->pathPoints[i] - ((threadInfo*)p)->pathPoints[i + 1])));
			}
			((threadInfo*)p)->pathPoints.push_back(std::move(((threadInfo*)p)->targetPoint));
			((threadInfo*)p)->pathDistance.push_back(std::move(Unit::Navigator::GetLength(((threadInfo*)p)->pathPoints.back() - ((threadInfo*)p)->targetPoint)));


			return 0;

			//回傳(存放)路徑
		}
	}
	return 0;
}


//Astar尋路
//將每個轉角or格子設為下個點
void Unit::Navigator::AStar()
{
	vector<CPoint> close;//封閉list，存放已經被走訪的點
	vector<CPoint> open;//開啟list，存放可能被做為起點的點
	CPoint cp = CPoint(GetParent<Entity>()->GetTileX(), GetParent<Entity>()->GetTileY());//每一輪起點
	std::map<CPoint, int, CPointCompare> gScore;//起點到CP點的距離
	std::map<CPoint, int, CPointCompare> hScore;//評估函式，可以用距離、難易度
	std::map<CPoint, int, CPointCompare> fScore;//g+h
	std::map<CPoint, CPoint, CPointCompare> come_from;//父節點
	open.push_back(cp);//起點加入openList

	//起點加入fscore
	fScore.insert(std::pair<CPoint, int>(cp, 0));
	hScore.insert(std::pair<CPoint, int>(cp, 0));
	gScore.insert(std::pair<CPoint, int>(cp, 0));


	while (open.size() > 0)
	{
		int minIndex = 0, minValue = INT32_MAX;
		//在openList中找最小值的CPoint作為這圈的開始
#pragma region FindMin


		for (unsigned int i = 0; i < open.size(); i++)
		{
			//比最小值還小
			if (fScore[open[i]] < minValue)
			{
				minValue = fScore[open[i]];
				minIndex = i;
			}
		}
#pragma endregion
		cp = open.at(minIndex);//起點變成有最小值f的點
		//周圍八方向的點
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				if (!(y == 0 && x == 0))//非自己
				{
					CPoint newPoint = CPoint(cp.x + x, cp.y + y);
					bool continueFlag = false;
					for (unsigned i = 0; i < close.size(); i++)
					{
						if (close[i] == newPoint)
						{
							continueFlag = true;
							break;
						}
					}
					if (continueFlag)continue;

					//目前到這裡的cost
					int newGScore = gScore[cp] + 1;

					//評估cost
					int canPass = World::getInstance()->getLocationItem((newPoint).x * 50, (newPoint).y * 50);

					//canPass = 1 - canPass;
					//曼哈頓距離預測
					int newHScore = 1000 * canPass + (abs(targetTile.x - (newPoint).x) + abs(targetTile.y - (newPoint).y));

					int newFScore = newGScore + newHScore;


					gScore.insert(pair<CPoint, int>(newPoint, newGScore));
					hScore.insert(pair<CPoint, int>(newPoint, newHScore));
					fScore.insert(pair<CPoint, int>(newPoint, newFScore));
					open.push_back(newPoint);
					come_from.insert(pair<CPoint, CPoint>(newPoint, cp));

				}
			}
		}
		//cp加入close list
		close.push_back(cp);
		//cp從open list中刪除
		auto it = open.begin();
		for (unsigned int i = 0; i < open.size(); it++, i++)
		{
			if (*it == cp)
			{
				open.erase(it);
				break;
			}
		}



		if (cp == targetTile)//到了
		{
			stack<CPoint>stackPath;
			while (true)
			{
				stackPath.push(cp);
				if (cp == startTile)break;
				cp = come_from[cp];
			}
			unsigned int s = stackPath.size();
			for (unsigned int i = 0; i < s; i++)
			{
				pathPoints.push_back(Tile2Point(stackPath.top()));
				stackPath.pop();

			}
			for (unsigned int i = 0; i < pathPoints.size() - 1; i++)
			{
				pathDistances.push_back(GetLength(pathPoints[i] - pathPoints[i + 1]));
			}
			Straight(pathPoints.back(), targetPoint);
			pathDistances.push_back(GetLength(pathPoints.back() - targetPoint));


			gScore.clear();
			hScore.clear();
			fScore.clear();
			come_from.clear();

			return;

			//回傳(存放)路徑
		}
	}
}


//開始尋路
void Unit::Navigator::FindPath(CPoint targrtP, vector<Entity*> entityList)
{
	int canPass = World::getInstance()->getLocationItem(targrtP.x, targrtP.y);

	if (canPass)
	{
		TRACE("Find Path Fail\n");
		return;
	}

	startPoint = this->GetParent<Entity>()->point;
	startTile = this->GetParent<Entity>()->GetTile();
	pathPoints.clear();
	pathDistances.clear();
	this->targetPoint = targrtP;
	targetTile = Point2Tile(targrtP);

	
	Info = threadInfo();
	Info.pathDistance.clear();
	Info.pathPoints.clear();
	Info.startPoint = startPoint;
	Info.startTile = startTile;
	Info.targetPoint = targetPoint;
	Info.targetTile = targetTile;

	hThead = CreateThread(NULL, 0, AStarSync, &Info, 0, &dwThreadID);
	


	//if (GetHandleInformation(hThead, (LPDWORD)dwThreadID))
	//{
	//		CloseHandle(hThead);
	//}

}

//開始尋路
void Unit::Navigator::FindPath(CPoint targrtP)
{
	int canPass = World::getInstance()->getLocationItem(targrtP.x, targrtP.y);

	if (canPass)
	{
		TRACE("Find Path Fail\n");
		return;
	}

	startPoint = this->GetParent<Entity>()->point;
	startTile = this->GetParent<Entity>()->GetTile();
	pathPoints.clear();
	pathDistances.clear();
	this->targetPoint = targrtP;
	targetTile = Point2Tile(targrtP);
	AStar();
}
Unit::Navigator::Navigator()
{
	speedFixed = 5;
	targetPoint = CPoint(0, 0);
	targetTile = CPoint(0, 0);
	velocity[0] = 0;
	velocity[1] = 0;
	counterF[0] = 0;
	counterF[1] = 0;


}
Unit::Navigator::~Navigator()
{
	TRACE("~Navigator\n");
}