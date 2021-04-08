#pragma once
#include "Entity.h"
#include <vector>

namespace Unit
{

	class Navigator :public UnitBase
	{
	public:
		//���ʥέp�ƾ�
		//��첾�q�p��1�ɡA�|�N�첾�q�֥[�ܭp�ƾ�
		//��p�ƾ��ƭȹF��ܤ֥��t1�ɡA�N�ƭȨϥΩ󲾰�
		float counterXF;
		float counterYF;

		//�t�׽վ�
		float speedFixed;

		//�ؼ��I�y��
		int targetPoint[2];

		//�ؼЮ�y��
		int targetTile[2];

		//���|X�y��
		vector<int> pathPointXs;

		//���|Y�y��
		vector<int> pathPointYs;

		//���|��
		vector<float> pathDistances;

		//���W�ƪ��U���I�y��
		float normalNextPoint[2];

		//���o�G���V�q����
		float GetLength(int vectorX, int vectorY)
		{
			return static_cast<float>(sqrt(vectorX * vectorX + vectorY * vectorY));
		}
		//���o�G���V�q����
		float GetLength(float vectorX, float vectorY)
		{
			return static_cast<float>(sqrt(vectorX * vectorX + vectorY * vectorY));
		}
		//�}�l�M��
		void Findpath(int targetPointX, int targetPointY)
		{
			int nowX = GetParent<Entity>()->pointX;
			int nowY = GetParent<Entity>()->pointY;
			pathDistances.clear();
			pathPointXs.clear();
			pathPointYs.clear();
			Straight(targetPointX, targetPointY);


		}
		//���W��
		void Normalization(int startX, int startY, int endX, int endY, float normal[2])
		{
			int deltaX = endX - startX;
			int deltaY = endY - startY;
			float l = GetLength(deltaX, deltaY);
			normal[0] = deltaX / l;
			normal[1] = deltaY / l;
		}

		//���ʤ@�B
		void onMove(int* pointX, int* pointY)
		{
			if (pathDistances.size() > 0)
			{
				Normalization(*pointX, *pointY, pathPointXs.at(0), pathPointYs.at(0), normalNextPoint);

				MoveStraight(pointX, pointY);
				if (pathDistances.at(0) <= speedFixed)
				{
					pathDistances.pop_back();
					pathPointXs.pop_back();
					pathPointYs.pop_back();
				}
			}
		}
		//���u����
		//���U���I���u���h
		void MoveStraight(int* pointX, int* pointY)
		{
			counterXF += normalNextPoint[0] * speedFixed;
			counterYF += normalNextPoint[1] * speedFixed;
			*pointX += static_cast<int>(counterXF);
			*pointY += static_cast<int>(counterYF);
			pathDistances.at(0) = GetLength(pathPointXs.at(0) - *pointX, pathPointYs.at(0) - *pointY);
			counterXF -= static_cast<int>(counterXF);
			counterYF -= static_cast<int>(counterYF);
		}
		//���u�M��
		//�����N���I�]���U���I
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
		//Astar�M��
		//�N�C���ਤor��l�]���U���I
		void AStar(int targetTileX, int targetTileY, int** tileMap)
		{
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