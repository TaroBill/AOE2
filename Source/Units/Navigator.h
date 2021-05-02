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

		//�{�b�I�y��
		CPoint* nowPoint;

		//���|�I�y��
		vector <CPoint> pathPoints;

		//���|��
		vector<float> pathDistances;

		//���W�ƪ��U���I�y��
		float normalNextPoint[2];


		//point2tile
		CPoint Point2Tile(CPoint);
		//tile2point
		CPoint Tile2Point(CPoint);

		//���o�G���V�q����
		float GetLength(CPoint vector);
		//���W��
		CPoint Normalization(CPoint start, CPoint end);
		void Normalization(CPoint start, CPoint end,float normal[2]);
		
		//�p������L�H
		vector<Navigator*>others;
		//�O�_�������A�O���ܫh�i��M���A�ä��ϥκ�k(�ثe)
		bool isLeader;
		//������
		//������V�t�סA�ΥH�קK�P��L���ͤӪ�
		int separation;
		//�����
		//��������L���ͪ��t��
		int alignment;
		//���E��
		//
		int coherence;
		//�P���d��
		//�ΨӰ����d�򤺬O�_����ê��
		int separationRange;
		//��ϥ�
		vector<float>velocity;
		//����
		//�b�s�餺�קK�L�����
		//�]�t�׶}��ê��
		CPoint Separation();
		//���
		//�¦V�s�骺������V����
		CPoint Alignment();
		//���E
		//�V�s�骺������m����
		CPoint Cohesion();
		
		
		//�}�l�M��
		void FindPath(int targetPointX, int targetPointY);
		void FindPath(CPoint targetPoint);
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