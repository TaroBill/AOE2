#pragma once
#include "Entity.h"

namespace Unit
{
	class TownCenter :public Entity
	{
	public:
		void SetBitmap() override
		{
			string str = "..\\RES\\Building\\TownCenter.bmp";
			animations[State::Idle][Direction::Down].AddBitmap(const_cast<char*>(str.c_str()), RGB(0, 0, 0));
			size.x = animations[State::Idle][Direction::Down].Width();
			size.y = animations[State::Idle][Direction::Down].Height();
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