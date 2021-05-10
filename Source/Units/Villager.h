#pragma once
#include "Entity.h"
#include "UnitBase.h"
#include "../Player/GameResource.h"
namespace Unit
{
	class Villager :public Entity
	{
	public:
		enum class VillagerState
		{
			Base,
			GetResourceOnRoad,//正在採集的路上
			Gathering,//採集中
			ReturnResourceOnRoad,//採集結束後，將資源帶回的路上

		};
		
		VillagerState vs;

		int resourceCounter;

		//資源的攜帶上限
		int carryLimit;
		
		int navigatorState;
		//攜帶物
		GameResource carryResource;

		//鎖定的資源源地
		Entity* resourcePlace;

		//資源回收站點(還暫時沒有分出分支)
		Entity* recyclePlace;

		//把資源放到主城，讓對應的玩家增加資源
		void ReturnResource();
		bool FindResouce();

		bool FindRecyclingPlace();

		//採集
		void Gathering();

		void SetTarget(CPoint point , vector<Entity*> group);

		void SetBitmap();

		void onMove();


		void FSM(int navigatorState);


		Villager(int pointX, int pointY) ;

		Villager(CPoint point) ;
		Villager();
		~Villager();
	};
}