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

		//point2tile
		int Point2Tile(int p);
		//tile2point
		int Tile2Point(int t);

		//���o�G���V�q����
		float GetLength(int vectorX, int vectorY);
		//���o�G���V�q����
		float GetLength(float vectorX, float vectorY);
		//�}�l�M��
		void FindPath(int nowX,int nowY,int targetPointX, int targetPointY);
		//�Q��Component�䪫��
		template<typename T>
		void FindEntityPath()
		{
			
		}
		//���W��
		void Normalization(int startX, int startY, int endX, int endY, float normal[2]);

		//���ʤ@�B
		//0���W
		//1��F
		//-1�ثe�S�����|�n�i��
		int onMove(int* pointX, int* pointY);
		//���u����
		//���U���I���u���h
		void MoveStraight(int* pointX, int* pointY);
		//���u�M��
		//�����N���I�]���U���I
		void Straight(int nowX,int nowY,int targetPointX, int targetPointY);

		//Astar�M��
		//�N�C���ਤor��l�]���U���I
		void AStar(int targetPointX, int targetPointY);

		Navigator();
	};
};