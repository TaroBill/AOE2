#pragma once
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "Navigator.h"
#include "Entity.h"
#include "../World.h"

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
	return temp>0 ? temp : 1;
}

//正規化
void Unit::Navigator::Normalization(CPoint start, CPoint end, float normal[2])
{
	CPoint delta = end - start;
	float l = GetLength(delta);
	normal[0] = delta.x / l;
	normal[1] = delta.y / l;
}

void Unit::Navigator::SetLeader(vector<Entity*> entities, CPoint centre)
{
	float smallDis = static_cast<float>(INT32_MAX);
	unsigned int index = -1;
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		float dis = GetLength(centre - entities[i]->point);
		if (dis <= smallDis)
		{
			index = i;
			smallDis = dis;
		}
		auto p = this->GetParent<Entity>();
		if ((entities[i])->ID != p->ID)
		{
			others.push_back(entities[i]->GetComponent<Navigator>());
		}
	}
	entities[index]->GetComponent<Navigator>()->isLeader = true;
	this->Leader = entities[index]->GetComponent<Navigator>();
}

CPoint Unit::Navigator::GetCentre(vector<Entity*> entityList)
{
	CPoint c = CPoint(0, 0);
	for (unsigned int i = 0; i < entityList.size(); i++)
	{
		c += entityList[i]->point;
	}
	c.x = c.x / entityList.size();
	c.y = c.y / entityList.size();
	return c;
}

CPoint Unit::Navigator::GetNowPoint()
{
	return (this->GetParent<Entity>()->point);
}
#pragma endregion

#pragma region BoidsNavigator
//TODO List
//velocity或許可以直接用normalNextPoint
//VectorF

//對齊
//朝向群體的平均方向移動
void Unit::Navigator::Alignment(float p[2])
{
	float _x = 0, _y = 0;
	for (unsigned int i = 0; i < others.size(); i++)
	{
		_x = _x + (*others[i]).velocity[0];
		_y = _y + (*others[i]).velocity[1];
	}
	_x /= alignment;
	_y /= alignment;
	p[0] = _x;
	p[1] = _y;
}

//凝聚
//向群體的平均位置移動
void Unit::Navigator::Cohesion(float p[2])
{
	float fp[2] = { 0,0 };
	for (unsigned int i = 0; i < others.size(); i++)
	{
		fp[0] += others[i]->GetNowPoint().x;
		fp[1] += others[i]->GetNowPoint().y;
	}
	fp[0] /= others.size();
	fp[1] /= others.size();
	CPoint cp = CPoint(static_cast<int>(p[0]), static_cast<int>(p[1]));
	Normalization(this->GetNowPoint(), cp, fp);
	p[0] = fp[0]/coherence;
	p[1] = fp[1]/coherence;
}

//分離
//在群體內避免過於擁擠
//包含避開障礙物
void Unit::Navigator::Separation(float p[2])
{
	float _x = 0, _y = 0;
	for (unsigned int i = 0; i < others.size(); i++)
	{
		float ax = 0, ay = 0, bx = 0, by = 0;
		float dis = 0;
		ax = static_cast<float>(others[i]->GetNowPoint().x);
		ay = static_cast<float>(others[i]->GetNowPoint().y);
		bx = static_cast<float>(this->GetNowPoint().x);
		by = static_cast<float>(this->GetNowPoint().y);
		dis = static_cast<float>(sqrt(ax * ax + by * by));

		if (dis < separationRange)
		{
			_x = _x - (bx - ax);
			_y = _y - (by - ay);
		}
	}
	p[0] = _x;
	p[1] = _y;
}

void Unit::Navigator::BoidsFlocking(CPoint* point)
{
	float v1[2] = { 0,0 }, v2[2] = { 0,0 }, v3[2] = { 0,0 };

	Alignment(v1);
	Cohesion(v2);
	Separation(v3);
	this->velocity[0] = v1[0] + v2[0] + v3[0];
	this->velocity[1] = v1[1] + v2[1] + v3[1];
	point->x += static_cast<int>(velocity[0]);
	point->y += static_cast<int>(velocity[1]);
}
#pragma endregion 

//直線移動
//往下個點直線走去
//是移動的基礎
void Unit::Navigator::MoveStraight(CPoint* point)
{
	//浮點數counter累計
	for (unsigned int i = 0; i < 2; i++)counterF[i] += normalNextPoint[i] * speedFixed;
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
	if (isLeader)
	{
		
		if (pathDistances.size() > 0)
		{
			//GetParent<Entity>()->entityState = Entity::State::Move;
			Normalization(*point, (pathPoints.front()), normalNextPoint);
			velocity[0] = normalNextPoint[0];
			velocity[1] = normalNextPoint[1];
			MoveStraight(point);
			if (pathDistances.front() <= speedFixed)
			{

				pathDistances.erase(pathDistances.begin());
				pathPoints.erase(pathPoints.begin());
				findPathState = 1;
				if (pathDistances.size() == 1)
				{
					normalNextPoint[0] = 0;
					normalNextPoint[1] = 0;
					velocity[0] = 0;
					velocity[1] = 0;
					isLeader = false;
				}
				return 1;
			}
			findPathState = 0;
			return 0;
		}
		else
		{
			isLeader = false;
			findPathState = -1;
			normalNextPoint[0] = 0;
			normalNextPoint[1] = 0;
			return -1;
		}
	}
	else
	{
		if (findPathState == 0)
		{
			findPathState = Leader->findPathState;
			if (findPathState)//Leader到了
			{
				normalNextPoint[0] = 0;
				normalNextPoint[1] = 0;
				velocity[0] = 0;
				velocity[1] = 0;
				isLeader = false;
				//其他
			}
			BoidsFlocking(point);
		}
	}
	normalNextPoint[0] = 0;
	normalNextPoint[1] = 0;
	velocity[0] = 0;
	velocity[1] = 0;
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

//Astar尋路
//將每個轉角or格子設為下個點
void Unit::Navigator::AStar()
{
	
	vector<CPoint*> close;//封閉list，存放已經被走訪的點
	vector<CPoint*> open;//開啟list，存放可能被做為起點的點
	CPoint* cp =new CPoint(GetParent<Entity>()->GetTileX(), GetParent<Entity>()->GetTileY());//每一輪起點
	std::map<CPoint*, int> gScore;//起點到CP點的距離
	std::map<CPoint*, int> hScore;//評估函式，可以用距離、難易度
	std::map<CPoint*, int> fScore;//g+h
	std::map<CPoint*, CPoint*> come_from;//父節點
	open.push_back(cp);//起點加入openList

	//起點加入fscore
	fScore.insert(std::pair<CPoint*, int>(cp, 0));
	hScore.insert(std::pair<CPoint*, int>(cp, 0));
	gScore.insert(std::pair<CPoint*, int>(cp, 0));


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
					CPoint* newPoint = new CPoint(cp->x + x, cp->y + y);
					bool continueFlag = false;
					for (unsigned i = 0; i < close.size(); i++)
					{
						if (*close[i] == *newPoint)
						{
							continueFlag = true;
							break;
						}
					}
					if (continueFlag)continue;

					//目前到這裡的cost
					int newGScore = gScore[cp] + 1;

					//評估cost
					int canPass = World::getInstance()->getLocationItem((*newPoint).x * 50, (*newPoint).y * 50);

					//canPass = 1 - canPass;
					//曼哈頓距離預測
					int newHScore = 1000 * canPass + (abs(targetTile.x - (*newPoint).x) + abs(targetTile.y - (*newPoint).y));

					int newFScore = newGScore + newHScore;


					gScore.insert(pair<CPoint*, int>(newPoint, newGScore));
					hScore.insert(pair<CPoint*, int>(newPoint, newHScore));
					fScore.insert(pair<CPoint*, int>(newPoint, newFScore));
					open.push_back(newPoint);
					come_from.insert(pair<CPoint*, CPoint*>(newPoint, cp));

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



		if (*cp == targetTile)//到了
		{
			stack<CPoint>stackPath;
			while (true)
			{
				stackPath.push(*cp);
				if (*cp == startTile)break;
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

			for (unsigned int i = 0; i < close.size(); i++)
				delete close[i];
			for (unsigned int i = 0; i < open.size(); i++)
				delete open[i];
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
	for (unsigned int i = 0; i < entityList.size(); i++)
	{
		TRACE("Group Id %d\n",entityList[i]->ID);
	}
	if (entityList.size() == 1)
	{
		isLeader = true;
	}
	else
	{
		CPoint centre = GetCentre(entityList);
		SetLeader(entityList, centre);
	}
	startPoint = this->GetParent<Entity>()->point;
	startTile = this->GetParent<Entity>()->GetTile();
	pathPoints.clear();
	pathDistances.clear();
	this->targetPoint = targrtP;
	targetTile = Point2Tile(targrtP);
	findPathState = 0;
	if (this->isLeader)
	{
		AStar();
	}
}
Unit::Navigator::Navigator()
{
	speedFixed = 5;
	targetPoint = CPoint(0, 0);
	targetTile = CPoint(0, 0);
	normalNextPoint[0] = 0;
	normalNextPoint[1] = 0;
	counterF[0] = 0;
	counterF[1] = 0;
	isLeader = 0;
	findPathState = -1;
	velocity[0] = 0;
	velocity[1] = 0;
	//分離值
	separation = 0;
	//對齊值
	alignment = 2;
	//凝聚值
	//
	coherence = 2;
	//感測範圍
	//用來偵測範圍內是否有障礙物
	separationRange = 50;
}
