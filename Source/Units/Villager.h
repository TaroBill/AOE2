#pragma once
#include "Entity.h"
#include "UnitBase.h"

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
			char* st = ".\\RES\\Villager\\VillagerIdle_2_12.bmp";
			ani.AddBitmap(st, RGB(255, 255, 255));
			//ani.AddBitmap(, RGB(0, 0, 0));
			/*
			char* filename[3] = {
				".\\RES\\Villager\\VillagerIdle_0_0.bmp",
				".\\RES\\Villager\\VillagerIdle_0_1.bmp",
				".\\RES\\Villager\\VillagerIdle_0_2.bmp",
			};
			//char* filename[4] = { ".\\bitmaps\\ball1.bmp",".\\bitmaps\\ball2.bmp",".\\bitmaps\\ball3.bmp",".\\bitmaps\\ball4.bmp" };
			for (int i = 0; i < 4; i++)	// ���J�ʵe(��4�i�ϧκc��)
				ani.AddBitmap(filename[i], RGB(0, 0, 0));
			*/
		}
		void onMove() override
		{
			ani.OnMove();
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