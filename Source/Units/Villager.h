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
		if (m.resource.type == carry.type)
		{
			carry.n += m.getResource();
		}
		else
		{
			carry.type = m.resource.type;
			carry.n = m.resource.n;
		}
		
	}
	//把資源放到主城，讓對應的玩家增加資源
	void ReturnResource()
	{

	}
};