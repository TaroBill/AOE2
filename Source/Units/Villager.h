#pragma once
#include "Entity.h"
#include "UnitBase.h"

namespace Unit
{
	class Villager :public Entity
	{
	public:
		int carryLimit;
		
		//從礦場取得資源

		//把資源放到主城，讓對應的玩家增加資源
		void ReturnResource()
		{

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
		void onMove() override
		{
			animations[entityState][faceDirection].OnMove();
			//ani.OnMove();
		}
		Villager(int tileX,int tileY):Entity(tileX,tileY)
		{
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