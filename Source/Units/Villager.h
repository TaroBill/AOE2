#pragma once

#include "UnitBase.h"
#include "../Player/GameResource.h"
#include "Mine.h"
class Villager :public UnitBase
{
public:
	GameResource carry;
	//�q�q�����o�귽
	void GetResource(Mine m)
	{
		m.getResource();
		if (rs.type == carry.type)
		{
			carry.n += rs.n;
		}
		else
		{
			carry.type = rs.type;
			carry.n = rs.n;
		}
	}
	//��귽���D���A�����������a�W�[�귽
	void ReturnResource()
	{

	}
};