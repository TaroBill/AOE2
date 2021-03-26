#pragma once

#include "UnitBase.h"
#include "../Player/GameResource.h"
#include "Mine.h"
//using namespace
class Villager :public UnitBase
{
public:
	
	GameResource carry;
	//�q�q�����o�귽
	void GetResource(Mine m)
	{
		if (m.resource.type == carry.type)
		{
			carry.n = m.GetResource();
		}
		else
		{
			carry.type = m.resource.type;
			carry.n = m.resource.n;
		}
		
	}
	//��귽���D���A�����������a�W�[�귽
	void ReturnResource()
	{

	}
	Villager(int pID, int mHP, int tileX, int tileY, int movingSpeed) : UnitBase(pID, mHP, tileX, tileY, movingSpeed)
	{
		carry = GameResource(ResourceType.None, 0);
	}
};