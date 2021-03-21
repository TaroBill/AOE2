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
			TRACE("�s�WCollectable\n");
		};
		//�Ķ��귽
		int getResource()
		{
			TRACE("�귽��֤F");
			reduceResource();

			return 1;
		}

	};
}
