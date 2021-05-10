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
	class Mine :public Entity
	{
	public:
		int remainAmount;

		CPoint point;

		Mine(CPoint, ResourceType);

		Mine(int, int, ResourceType );

		void SetBitmap()override;

		void SetTarget(CPoint, vector<Entity*>) override;

		void onMove()override;

		 ~Mine() ;
	};
}