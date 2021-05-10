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
		Mine();
		~Mine();
	private:
		void loadBitmap();
		int remainAmount;
		CPoint point;



		Mine(CPoint point,ResourceType rt) :Entity(point)
		{
			Gatherable* n = new Gatherable(rt, 800);
			AddComponent(n);

			SetBitmap();
		}

		Mine(int x,int y, ResourceType rt) :Entity(x,y)
		{
			Gatherable* n = new Gatherable(rt, 800);
			AddComponent(n);

			SetBitmap();
		}
		void SetBitmap()override
		{
			animations[State::Idle][Direction::Down].AddBitmap(IDB_GOLD, RGB(255, 255, 255));
		}
		void SetTarget(CPoint point, vector<Entity*> group) override
		{

		}
		void onMove()override
		{
			if (this->GetComponent<Gatherable>()->resource.amount==0)
			{
				delete this;
			}
		}
		~Mine()
		{
			TRACE("¨S¸ê·½¤F");
		}
	};
}