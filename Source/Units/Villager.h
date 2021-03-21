#pragma once

#include "UnitBase.h"
#include "../Player/GameResource.h"
#include "Mine.h"
class Villager :public UnitBase
{
public:
	GameResource carry;
	//從礦場取得資源
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
	//把資源放到主城，讓對應的玩家增加資源
	void ReturnResource()
	{

	}
};