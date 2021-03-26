#pragma once

#include "UnitBase.h"
#include "../Player/GameResource.h"
#include "Mine.h"
//using namespace
namespace Unit
{
	class Villager :public UnitBase
	{
	public:

		GameResource carry;
		//�q�q�����o�귽
		void GetResource(Mine m)
		{
			if (m.resource.type == carry.type)
			{
				carry.amount += m.resource.GetResource();
			}
			else
			{
				carry.type = m.resource.type;
				carry.amount = m.resource.GetResource();
			}

		}
		//��귽���D���A�����������a�W�[�귽
		void ReturnResource()
		{

		}
		Villager()
		{

		}
		Villager(int pID):UnitBase()
		{

		}
		Villager(int pID, int tileX, int tileY, int pointX, int pointY, int mHP, int movingSpeed) : UnitBase(pID, tileX, tileY, pointX, pointY, mHP, movingSpeed)
		{
			carry = GameResource(ResourceType::None, 0);
		}
	};
}