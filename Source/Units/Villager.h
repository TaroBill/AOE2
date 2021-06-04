#pragma once
#include "Entity.h"
#include "UnitBase.h"
#include "Navigator.h"
#include "Gatherable.h"
#include "Attack.h"
#include <sstream>

#include "../Player/GameResource.h"
namespace Unit
{
	class Villager :public Entity 
	{
	public:

		void Serialize(stringstream &in)
		{
			in << "Type " << this->entityType << " ";
			in << "HP " << this->hp << " ";
			in << "PointX " << this->point.x << " ";
			in << "PointY " << this->point.y << " ";
			in << "ID " << this->ID << " ";
			in << "playerID " << (1 - this->playerId) << " ";
			in << "resourceCounter " << resourceCounter << " ";
			in << "attackCounter " << attackCounter << " ";
			in << "End ";

		}

		void deSerialize(stringstream &in)
		{
			string erase;
			in >> erase >> this->hp;
			in >> erase >> this->point.x;
			in >> erase >> this->point.y;
			in >> erase >> this->ID;
			in >> erase >> this->playerId;
			in >> erase >> this->resourceCounter;
			in >> erase >> this->attackCounter;
			in >> erase; //吃掉End
		}

	public:
		enum class VillagerState
		{
			Base,
			GetResourceOnRoad,//正在採集的路上
			Gathering,//採集中
			ReturnResourceOnRoad,//採集結束後，將資源帶回的路上
			GoAttackOnRoad,//行軍路上
			Attacking //正在攻擊
		};
		
		VillagerState vs;

		int resourceCounter = 0;

		int attackCounter = 0;

		//資源的攜帶上限
		int carryLimit;
		
		int navigatorState;
		//攜帶物
		GameResource carryResource;
		//用來儲存上個資源點位置
		CPoint resourcePlace;
		//資源回收站點(還暫時沒有分出分支)
		Entity* recyclePlace;

		//把資源放到主城，讓對應的玩家增加資源
		void ReturnResource();

		bool FindResouce();

		bool FindRecyclingPlace();

		//採集
		bool Gathering();
		//攻擊
		void Attacking();

		void SetTarget(CPoint point , vector<Entity*> group);

		void SetTarget(CPoint point);
		//設置離點最近的敵人(或資源，依照正在做的行為判定)為target
		void SetTargetByRange(CPoint point, VillagerState state);

		void SetBitmap();

		void onMove();

		void FSM(int navigatorState);


		Villager(int pointX, int pointY) ;

		Villager(CPoint point) ;
		Villager();
		 ~Villager();
	};
}