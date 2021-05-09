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

//���o�G���V�q����
float Unit::Navigator::GetLength(CPoint p)
{
	float temp = static_cast<float>(sqrt(p.x * p.x + p.y * p.y));
	return temp > 0 ? temp : 1;
}

//���W��
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


//���u����
//���U���I���u���h
//�O���ʪ���¦
void Unit::Navigator::MoveStraight(CPoint* point)
{
	//�B�I��counter�֭p
	for (unsigned int i = 0; i < 2; i++)counterF[i] += normalNextPoint[i] * speedFixed;
	//����첾�B�I��counter����Ƴ���
	*point += CPoint(static_cast<int>(counterF[0]), static_cast<int>(counterF[1]));
	//�p��P�U�@���I���Z��
	pathDistances.at(0) = GetLength(((pathPoints.at(0))) - *point);
	//�B�I��counter����Ƴ����h��
	for (unsigned int i = 0; i < 2; i++)counterF[i] -= static_cast<int>(counterF[i]);
}




//���ʤ@�B
//0���W
//1��F
//-1�ثe�S�����|�n�i��
int Unit::Navigator::onMove(CPoint* point)
{


	if (pathDistances.size() > 0)
	{
		//GetParent<Entity>()->entityState = Entity::State::Move;
		Normalization(*point, (pathPoints.front()), normalNextPoint);

		MoveStraight(point);
		if (pathDistances.front() <= speedFixed)
		{

			pathDistances.erase(pathDistances.begin());
			pathPoints.erase(pathPoints.begin());

			return 1;
		}
		return 0;
	}
	else
	{
		normalNextPoint[0] = 0;
		normalNextPoint[1] = 0;
		return -1;
	}
	return -1;
}

//���u�M��
//�����N���I�]���U���I
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

//Astar�M��
//�N�C���ਤor��l�]���U���I
void Unit::Navigator::AStar()
{

	vector<CPoint*> close;//�ʳ�list�A�s��w�g�Q���X���I
	vector<CPoint*> open;//�}��list�A�s��i��Q�����_�I���I
	CPoint* cp = new CPoint(GetParent<Entity>()->GetTileX(), GetParent<Entity>()->GetTileY());//�C�@���_�I
	std::map<CPoint*, int> gScore;//�_�I��CP�I���Z��
	std::map<CPoint*, int> hScore;//�����禡�A�i�H�ζZ���B������
	std::map<CPoint*, int> fScore;//g+h
	std::map<CPoint*, CPoint*> come_from;//���`�I
	open.push_back(cp);//�_�I�[�JopenList

	//�_�I�[�Jfscore
	fScore.insert(std::pair<CPoint*, int>(cp, 0));
	hScore.insert(std::pair<CPoint*, int>(cp, 0));
	gScore.insert(std::pair<CPoint*, int>(cp, 0));


	while (open.size() > 0)
	{
		int minIndex = 0, minValue = INT32_MAX;
		//�bopenList����̤p�Ȫ�CPoint�@���o�骺�}�l
#pragma region FindMin


		for (unsigned int i = 0; i < open.size(); i++)
		{
			//��̤p���٤p
			if (fScore[open[i]] < minValue)
			{
				minValue = fScore[open[i]];
				minIndex = i;
			}
		}
#pragma endregion
		cp = open.at(minIndex);//�_�I�ܦ����̤p��f���I
		//�P��K��V���I
		for (int y = -1; y <= 1; y++)
		{
			for (int x = -1; x <= 1; x++)
			{
				if (!(y == 0 && x == 0))//�D�ۤv
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

					//�ثe��o�̪�cost
					int newGScore = gScore[cp] + 1;

					//����cost
					int canPass = World::getInstance()->getLocationItem((*newPoint).x * 50, (*newPoint).y * 50);

					//canPass = 1 - canPass;
					//�ҫ��y�Z���w��
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
		//cp�[�Jclose list
		close.push_back(cp);
		//cp�qopen list���R��
		auto it = open.begin();
		for (unsigned int i = 0; i < open.size(); it++, i++)
		{
			if (*it == cp)
			{
				open.erase(it);
				break;
			}
		}



		if (*cp == targetTile)//��F
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

			//�^��(�s��)���|
		}
	}
}

//�}�l�M��
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
	AStar();
}

//�}�l�M��
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
	normalNextPoint[0] = 0;
	normalNextPoint[1] = 0;
	counterF[0] = 0;
	counterF[1] = 0;


}
