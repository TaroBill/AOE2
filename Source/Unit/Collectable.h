#pragma once
#include "Component.h"

namespace GameObject
{
	class Collectable :public Component
	{
	public:
		int resource;
		int gatherRate;
		void reduceResource()
		{
			resource--;
		}
		Collectable()
		{
			resource = 0;
			gatherRate = 0;
		}
		Collectable(int resource, int gatherRate):Collectable()
		{
			this->resource = resource;
			this->gatherRate = gatherRate;
			TRACE("新增Collectable\n");
		};
		//採集資源
		int getResource()
		{
			TRACE("資源減少了");
			reduceResource();

			return 1;
		}

	};
}
