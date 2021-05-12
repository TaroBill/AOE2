#pragma once
#include "../StdAfx.h"
#include "UnitBase.h"

namespace Unit
{
	class Attack : public UnitBase 
	{
	public:
		Attack();
		Attack(int damage, int range);
		~Attack();
		bool doAttack();
		int Damage;
		int Range;
	private:
		double calculateLength(CPoint, CPoint);
	};
}