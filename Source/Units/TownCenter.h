#pragma once
#include "Entity.h"

namespace Unit
{
	class TownCenter :public Entity
	{
	public:
		void SetBitmap() override
		{
			string str = ".\\RES\\Building\\TownCenter.bmp";
			animations[State::Idle][Direction::Down].AddBitmap(const_cast<char*>(str.c_str()), RGB(0, 0, 0));
		}
		void SetTarget(CPoint point) override
		{
			
		}
		void onMove() override
		{

		}
		TownCenter(int pointX, int pointY) :Entity(pointX, pointY) 
		{
			SetBitmap();
		}
		TownCenter(CPoint point) :Entity(point)
		{
			SetBitmap();
		}
		TownCenter()
		{
			SetBitmap();
		}
	};
}