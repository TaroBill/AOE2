#pragma once
#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include "../Units/Entity.h"
#include "./Gatherable.h"
namespace Unit
{
	class Stone :public Entity
	{
	public:
		int remainAmount;

		Stone(CPoint, ResourceType);

		Stone(int, int, ResourceType );

		void SetBitmap()override;

		void SetTarget(CPoint, vector<Entity*>) override;

		void onMove()override;

		 ~Stone() ;
	};
}