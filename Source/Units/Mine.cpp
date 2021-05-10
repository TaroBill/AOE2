#include "Mine.h"


namespace Unit
{
	Mine::Mine(CPoint point, ResourceType rt) :Entity(point)
	{
		Gatherable* n = new Gatherable(rt, 800);
		AddComponent(n);

		SetBitmap();
	}

	Mine::Mine(int x, int y, ResourceType rt) : Entity(x, y)
	{
		Gatherable* n = new Gatherable(rt, 800);
		AddComponent(n);

		SetBitmap();
	}

	Mine::~Mine()
	{
		TRACE("沒資源了\n");
	}

	void Mine::SetBitmap()
	{
		animations[State::Idle][Direction::Down].AddBitmap(IDB_GOLD, RGB(255, 255, 255));
	}

	void  Mine::SetTarget(CPoint point, vector<Entity*> group) {}

	void Mine::onMove() {
		{
			/*if (this->GetComponent<Gatherable>()->resource.amount == 0)
			{
				delete this; //不該在這delete
			}*/
		}
	}










}