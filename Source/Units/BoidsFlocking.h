#pragma once
/*
Flocking
為Navigator 的Leaf
一個
會包含 Leader
以及其他隊友
Leader在一個群集中只有一個
非Leader 跟著Leader
Leader負責尋路

偵測拆散

拆散時 假設4人 ABCD 往 P點，A為Leader

若Leader被拆散
原Leader的路徑交接給新Leader ，新Lea

Case 1:
	AB被抓去往Q點 ，此時CD皆會失去Leader，但仍然需要往原路走
	A的Leader路徑給CD中的新Leader
	新Leader只需要在尋路List的前端
	加上前往舊Leader路徑，就可以無縫接軌
	然後AB中選出新Leader，進行尋路與跟隨
Case 2:
	CD被抓去往Q點，此時AB Leader不動，但CD需要選出新Leader
*/
#pragma once
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "Navigator.h"
#include "Entity.h"
#include "../World.h"
namespace Unit
{

	class BoidsFlocking :public UnitBase
	{
		//小隊的其他人
		vector<Entity>others;
		//是否為隊長，是的話則進行尋路，並不使用算法(目前)
		bool isLeader;
		//分離值
		//控制轉向速度，用以避免與其他隊友太近
		int separation;
		//對齊值
		//控制對齊其他隊友的速度
		int alignment;
		//凝聚值
		//
		int coherence;
		//感測範圍
		//用來偵測範圍內是否有障礙物
		int sightRange;
		//當使用
		vector<float>velocity;
		//分離
		//在群體內避免過於擁擠
		//包含避開障礙物
		void Separation();
		//對齊
		//朝向群體的平均方向移動
		void Alignment();
		//凝聚
		//向群體的平均位置移動
		void Cohesion();
	};
}



