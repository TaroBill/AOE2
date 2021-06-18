#pragma once
#include "Entity.h"
#include "../Player/GameResource.h"

namespace Unit
{
	class Sheep :public Entity
	{
	public:
		int remainAmount;

		Sheep(CPoint, ResourceType);

		Sheep(int, int, ResourceType);

		void SetBitmap()override;

		void SetTarget(CPoint, vector<Entity*>) override;

		void onShow(int screenX, int screenY) override;

		void onMove()override;
		

		~Sheep();
	};
}