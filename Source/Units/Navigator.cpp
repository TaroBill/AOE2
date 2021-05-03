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
	return temp>0 ? temp : 1;
}

//���W��
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
//velocity�γ\�i�H������normalNextPoint
//VectorF

//���
//�¦V�s�骺������V����
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

//���E
//�V�s�骺������m����
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

//����
//�b�s�餺�קK�L�����
//�]�t�׶}��ê��
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
			if (findPathState)//Leader��F
			{
				normalNextPoint[0] = 0;
				normalNextPoint[1] = 0;
				velocity[0] = 0;
				velocity[1] = 0;
				isLeader = false;
				//��L
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
	CPoint* cp =new CPoint(GetParent<Entity>()->GetTileX(), GetParent<Entity>()->GetTileY());//�C�@���_�I
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
	//������
	separation = 0;
	//�����
	alignment = 2;
	//���E��
	//
	coherence = 2;
	//�P���d��
	//�ΨӰ����d�򤺬O�_����ê��
	separationRange = 50;
}
