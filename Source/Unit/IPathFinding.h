#pragma once
#include <Vector>
namespace Utility
{
	namespace PathFinding
	{

		class PathFinding
		{
			//�s��i�H���u�e�i�쪺�U�@���I�A���ӵ�Unit�s
			std::vector<int[2]>paths;

			//�p����|
			virtual void calPath(int startX, int startY, int endX, int endY, int* map);
			
			//�^�ǤU�@�Ӯy�СA�ϥΪ̱N�̷ӳt�ת������V�U�@���I�A�ǰe��U�@�B
			virtual int* moveNextStep(int speed);
			
			

			//////////�H�U�O���]����������ϥα��p
			/*
			int nowX, nowY;
			
			//�k���I�U�A�}�l�]�w�ɯ誺���p
			void Navigate(int targetX,int targetY,int* map)
			{
				pathes = PathFinding::calPath(nowX,nowY,targetX,targetY,map);
			}
			//����
			void MoveTo()
			{
				villager villager1;
				villager
					
			}//*/
		};
	}
}