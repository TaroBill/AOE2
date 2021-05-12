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


	void Mine::SetBitmap()
	{
		animations[State::Idle][Direction::Down].AddBitmap(IDB_GOLD, RGB(255, 255, 255));
		size.x = animations[State::Idle][Direction::Down].Width();
		size.y = animations[State::Idle][Direction::Down].Height();
		HitBox = CRect(point.x, point.y, point.x + size.x, point.y + size.y);
	}

	void  Mine::SetTarget(CPoint point, vector<Entity*> group) {}

	void Mine::onMove() {
		
	}

	Mine::~Mine()
	{
		TRACE("~Mine\n");
	}









}