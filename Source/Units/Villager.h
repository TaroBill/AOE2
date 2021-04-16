#pragma once
#include "Entity.h"
#include "UnitBase.h"
#include "Navigator.h"
#include "Gatherable.h"
#include "World.h"
namespace Unit
{
	class Villager :public Entity
	{
	public:
		enum class VillagerState
		{
			Idle,//閒置、等待命令
			OnSetting,//設定命令中，有最高優先級
			GetResourceOnRoad,//正在採集的路上
			Gathering,//採集中
			ReturnResourceOnRoad,//採集結束後，將資源帶回的路上
			//SearchingResource 帶回資源後，
			Attack
		};
		
		VillagerState vs = VillagerState::Idle;

		int resourceCounter = 0;

		//資源的攜帶上限
		int carryLimit;
		
		//攜帶物
		GameResource carryResource;

		//鎖定的資源源地
		Entity* resourcePlace;

		//資源回收站點(還暫時沒有分出分支)
		Entity* recyclePlace;

		//把資源放到主城，讓對應的玩家增加資源
		void ReturnResource()
		{
			TRACE("=========== now Return Resource =========== \n");
		}

		void GetResource()
		{
			TRACE("=========== now Get Resource ing =========== \n");
		}

		void FindResouce()
		{
			TRACE("=========== now Find Resouce =========== \n");
		}

		void FindRecyclingPlace()
		{
			TRACE("=========== now Find Recycling Place =========== \n");
		}

		//採集
		void Gathering()
		{
			//應該有個counter累計值
			//累計到應該獲得一點資源的時候才+1
			//但先不管
			this->carryResource.amount += resourcePlace->GetComponent<Gatherable>()->resource.GetResource();
		}


		/*
		點擊時觸發一次
		選取村民後，點擊後判斷點是否為可採集資源後，判斷是什麼資源，不是動物就直接尋路到該點，是動物則判斷血量。
		村民會存下當下鎖定的資源種類，以及資源來源、以及資源回收站，在帶滿後會尋路回最近的資源回收站，礦沒了，則會找尋其他的同種類礦物
		*/
		void SetTarget(Entity* target) override
		{

			Gatherable* tar = (*target).GetComponent<Gatherable>();

			if (tar != nullptr)
			{
				switch (tar->resource.type)
				{
				case ResourceType::Meat://肉
					if (target->hp > 0)//目標還活著，攻擊
					{
						break;
					}
				case ResourceType::Wood://木頭
				case ResourceType::Stone://石礦
				case ResourceType::Gold://金礦
					resourcePlace = target;
					vs = VillagerState::GetResourceOnRoad;
					GetComponent<Navigator>()->FindPath(target->pointX, target->pointY);
					break;
				default:
					break;
				}
			}
			else
			{
				//沒找到
			}
		}


		void SetBitmap() override
		{
			for (int dire = 0; dire < 8; dire++)
			{
				for (int s = 0; s < 15; s++)
				{
					string str = ".\\RES\\Villager\\VillagerIdle_" + to_string(dire) + "_" + to_string(s) + ".bmp";
					State es = State::Idle;
					Direction d = static_cast<Direction>(dire);

					animations[es][d].AddBitmap(const_cast<char*>(str.c_str()), RGB(255, 255, 255));
				}
			}
		}

		void FSM(int navigatorState)
		{
			switch (vs)
			{
			case VillagerState::Idle:
				break;
			case VillagerState::OnSetting:
				break;
			case VillagerState::GetResourceOnRoad:
				if (navigatorState == 1)
				{
					vs = VillagerState::Gathering;
				}
				break;
			//採集中
			case VillagerState::Gathering:
				//採集
				resourcePlace->GetComponent<Gatherable>();
				
				if (carryLimit == carryResource.amount)//滿了
				{
					//滿了就找地方放
					FindRecyclingPlace();
					//切換狀態
					vs = VillagerState::ReturnResourceOnRoad;
				}
				break;
			case VillagerState::ReturnResourceOnRoad:

				break;
			case VillagerState::Attack:
				break;
			default:
				break;
			}
		}


		void onMove() override
		{
			int navigatorState = GetComponent<Navigator>()->onMove(&pointX, &pointY);
			
			FSM(navigatorState);
			//這裡只做狀態機使用
			
			/*
			animations[entityState][faceDirection].OnMove();
			if (entityState == State::Move)
			{
				GetComponent<Navigator>()->onMove(&pointX, &pointY);

			}
			*/
		}
		Villager(int pointX, int pointY) :Entity(pointX, pointY)
		{

			Navigator* n = new Navigator();
			AddComponent(n);
			carryLimit = 10;

			SetBitmap();
		}
		Villager()
		{
			SetBitmap();
		}
		~Villager()
		{

		}
	};
}