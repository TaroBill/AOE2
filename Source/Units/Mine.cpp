#include "../StdAfx.h"
#include "Mine.h"
#include "../World.h"

namespace Unit
{
	Mine::Mine(CPoint point, ResourceType rt) :Entity(point)
	{
		Gatherable* n = new Gatherable(rt, 35);
		AddComponent(n);
		entityType = EntityTypes::GoldMine;
		SetBitmap();
		World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;

	}

	Mine::Mine(int x, int y, ResourceType rt) : Entity(x, y)
	{
		Gatherable* n = new Gatherable(rt, 35);
		AddComponent(n);
		entityType = EntityTypes::GoldMine;
		SetBitmap();
		World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;

	}


	void Mine::SetBitmap()
	{
		animations[State::Idle][Direction::Down].AddBitmap(IDB_GOLD, RGB(255, 255, 255));
		size.x = animations[State::Idle][Direction::Down].Width();
		size.y = animations[State::Idle][Direction::Down].Height();
	}

	void  Mine::SetTarget(CPoint point, vector<Entity*> group) {}

	void Mine::onMove() {
		HitBox = CRect(point.x, point.y, point.x + size.x, point.y + size.y);
		remainAmount = this->GetComponent<Gatherable>()->resource.amount;
		if (remainAmount <= 0)
			World::getInstance()->killByID(this->ID);
	}

	Mine::~Mine()
	{
		World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 0;
		//TRACE("~Mine\n");
	}









}