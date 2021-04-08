#pragma once
#include "Entity.h"
#include "UnitBase.h"
#include "Navigator.h"
namespace Unit
{
	class Villager :public Entity
	{
	public:
		int carryLimit;
		
		//�q�q�����o�귽

		//��귽���D���A�����������a�W�[�귽
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
			GetComponent<Navigator>()->onMove(&pointX,&pointY);
			//TRACE("now at:%d,%d\n", pointX, pointY);
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