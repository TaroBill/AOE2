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
		//���ʥέp�ƾ�
		//��첾�q�p��1�ɡA�|�N�첾�q�֥[�ܭp�ƾ�
		//��p�ƾ��ƭȹF��ܤ֥��t1�ɡA�N�ƭȨϥΩ󲾰�
		float counterF[2];

		//�t�׽վ�
		float speedFixed;
		
		//�_�l�I�y��
		CPoint startPoint;

		//�_�l��y��
		CPoint startTile;

		//�ؼ��I�y��
		CPoint targetPoint;

		//�ؼЮ�y��
		CPoint targetTile;

		//���|�I�y��
		vector <CPoint> pathPoints;

		//���|��
		vector<float> pathDistances;

		//���W�ƪ��U���I�y��
		float normalNextPoint[2];


		//point2tile
		static CPoint Point2Tile(CPoint);
		//tile2point
		static CPoint Tile2Point(CPoint);
		//���o�G���V�q����
		static float GetLength(CPoint vector);
		//���W��
		static CPoint Normalization(CPoint start, CPoint end);
		static void Normalization(CPoint start, CPoint end,float normal[2]);

		//�{�b�I�y��
		CPoint GetNowPoint();
		
		//�}�l�M��
		void FindPath(CPoint targrtPoint, vector<Entity*> entityList);
		void FindPath(CPoint targrtPoint);

		//�Q��Component�䪫��
		template<typename T>
		void FindEntityPath()
		{
			
		}

		//���ʤ@�B
		//0���W
		//1��F
		//-1�ثe�S�����|�n�i��
		int onMove(CPoint* point);
		//���u����
		//���U���I���u���h
		void MoveStraight(CPoint* point);
		//���u�M��
		//�����N���I�]���U���I
		void Straight();
		//���u�M��
		//�����N���I�]���U���I
		void Straight(CPoint a,CPoint b);

		//Astar�M��
		//�N�C���ਤor��l�]���U���I
		void AStar();

		Navigator();
	};
};