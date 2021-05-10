#pragma once
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "UnitBase.h"
#include "Entity.h"
#include <memory> 

using namespace std;
 struct threadInfo
{
	CPoint targetPoint;
	CPoint targetTile;
	CPoint startPoint;
	CPoint startTile;
	vector<CPoint> pathPoints;
	vector<float> pathDistance;
	threadInfo()
	{
		targetPoint = CPoint(0, 0);
		 targetTile = CPoint(0,0);
		 startPoint = CPoint(0, 0);
		 startTile = CPoint(0, 0);
	}
	~threadInfo()
	{

	}
};
namespace Unit
{
	class Navigator :public UnitBase
	{
	public:
		threadInfo Info;//�ǻ�������Ǩ�ƪ��Ѽ�
		HANDLE hThead;//�x�s�����Handle
		DWORD dwThreadID;//�x�s�h�����ID
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
		float velocity[2];

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
		//�h����Ǫ�Astar
		//DWORD WINAPI AStarSync(LPVOID pParam);
		Navigator();

		~Navigator();
	};
};