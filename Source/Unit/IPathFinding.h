#pragma once
#include <Vector>
namespace Utility
{
	namespace PathFinding
	{

		class PathFinding
		{
			//存放可以直線前進到的下一個點，應該給Unit存
			std::vector<int[2]>paths;

			//計算路徑
			virtual void calPath(int startX, int startY, int endX, int endY, int* map);
			
			//回傳下一個座標，使用者將依照速度直接面向下一個點，傳送到下一步
			virtual int* moveNextStep(int speed);
			
			

			//////////以下是假設實體村民的使用情況
			/*
			int nowX, nowY;
			
			//右鍵點下，開始設定導航的情況
			void Navigate(int targetX,int targetY,int* map)
			{
				pathes = PathFinding::calPath(nowX,nowY,targetX,targetY,map);
			}
			//移動
			void MoveTo()
			{
				villager villager1;
				villager
					
			}//*/
		};
	}
}