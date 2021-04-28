#pragma once
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "Navigator.h"
#include "Entity.h"
#include "../World.h"

using namespace std;

//point2tile
int Unit::Navigator::Point2Tile(int p) { return p / 50; };
//tile2point
int Unit::Navigator::Tile2Point(int t) { return t * 50; };

//���o�G���V�q����
float Unit::Navigator::GetLength(int vectorX, int vectorY)
{
	return static_cast<float>(sqrt(vectorX * vectorX + vectorY * vectorY));
}
//���o�G���V�q����
float Unit::Navigator::GetLength(float vectorX, float vectorY)
{
	return static_cast<float>(sqrt(vectorX * vectorX + vectorY * vectorY));
}
//�}�l�M��
void Unit::Navigator::FindPath(int nowX,int nowY,int targetPointX, int targetPointY)
{

	pathDistances.clear();
	pathPointXs.clear();
	pathPointYs.clear();
	//Straight(targetPointX, targetPointY);
	AStar(targetPointX, targetPointY);
}
//�Q��Component�䪫��
/*
template<typename T>
void Unit::Navigator::FindEntityPath()
{

}
*/
//���W��
void Unit::Navigator::Normalization(int startX, int startY, int endX, int endY, float normal[2])
{
	int deltaX = endX - startX;
	int deltaY = endY - startY;
	float l = GetLength(deltaX, deltaY);
	normal[0] = deltaX / l;
	normal[1] = deltaY / l;
}

//���ʤ@�B
//0���W
//1��F
//-1�ثe�S�����|�n�i��
int Unit::Navigator::onMove(int* pointX, int* pointY)
{
	if (pathDistances.size() > 0)
	{
		//GetParent<Entity>()->entityState = Entity::State::Move;
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
//���u����
//���U���I���u���h
void Unit::Navigator::MoveStraight(int* pointX, int* pointY)
{
	counterXF += normalNextPoint[0] * speedFixed;
	counterYF += normalNextPoint[1] * speedFixed;
	*pointX += static_cast<int>(counterXF);
	*pointY += static_cast<int>(counterYF);
	pathDistances.at(0) = GetLength(pathPointXs.at(0) - *pointX, pathPointYs.at(0) - *pointY);
	counterXF -= static_cast<int>(counterXF);
	counterYF -= static_cast<int>(counterYF);
	//TRACE("%f,%f\n", normalNextPoint[0], normalNextPoint[1]);

}
//���u�M��
//�����N���I�]���U���I
void Unit::Navigator::Straight(int nowX,int nowY,int targetPointX, int targetPointY)
{

	pathPointXs.push_back(targetPointX);
	pathPointYs.push_back(targetPointY);
	Normalization(nowX, nowY, targetPoint[0], targetPoint[1], normalNextPoint);
	pathDistances.push_back(GetLength(nowX - targetPointX, nowY - targetPointY));

}

//Astar�M��
//�N�C���ਤor��l�]���U���I
void Unit::Navigator::AStar(int targetPointX, int targetPointY)
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
			if (fScore[open.at(i)] < minValue)
			{
				minValue = fScore[open.at(i)];
				minIndex = i;
			}
		}
#pragma endregion
		cp = open.at(minIndex);//�_�I�ܦ����̤p��f���I
		//�P��K��V���I
		for (unsigned int y = -1; y <= 1; y++)
		{
			for (unsigned int x = -1; x <= 1; x++)
			{
				if (!(y == 0 && x == 0))//�D�ۤv
				{
					CPoint* newPoint =new CPoint(cp->x + x, cp->y + y);
					if (std::find(close.begin(), close.end(), newPoint) == close.end())//�D�bclose list
					{
						//�ثe��o�̪�cost
						int newGScore = gScore[cp] + 1;

						//����cost
						int newHScore = World::getInstance()->getLocationItem(Tile2Point(newPoint->x), Tile2Point(newPoint->y));

						//�O�o�[�J�ҫ��y�Z���w��
						//newHScore += targetPointX

						int newFScore = newGScore + newHScore;


						gScore.insert(pair<CPoint*, int>(newPoint, newGScore));
						hScore.insert(pair<CPoint*, int>(newPoint, newHScore));
						fScore.insert(pair<CPoint*, int>(newPoint, newFScore));
						open.push_back(newPoint);
						come_from.insert(pair<CPoint*, CPoint*>(newPoint, cp));
					}
				}
			}
		}
		close.push_back(cp);
		///open.erase(,)
		//�O�o�R��cp from open list


		
		//if (cp.x == targetX && cp.y == targetY)//��F
		//{
			//�^��(�s��)���|
		//}
		

		//��n�qopen list�R��
		//��n�[�Jclose list
		//for i in n���F�~
			//if i in close (�Yi�bclose list�A���L�L)
			//continue
	}
	
}

Unit::Navigator::Navigator()
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
