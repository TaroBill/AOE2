#pragma once
#include "../StdAfx.h"
#include "../Player/GameResource.h"
namespace Unit
{
	class Gatherable :public UnitBase
	{

	public:
		GameResource resource;
		Gatherable()
		{
			resource = GameResource(ResourceType::None, 10);
		}
		Gatherable(ResourceType resourceType, int amount)
		{
			resource = GameResource(resourceType, amount);
		}
		~Gatherable()
		{

		}
	};
}