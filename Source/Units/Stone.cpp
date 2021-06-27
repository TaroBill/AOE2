#include "../StdAfx.h"
#include "Stone.h"
#include "../World.h"

namespace Unit
{
	Stone::Stone(CPoint point, ResourceType rt) :Entity(point)
	{
		Gatherable* n = new Gatherable(rt, 35);
		AddComponent(n);
		entityType = EntityTypes::Stone;
		SetBitmap();
		World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;

	}

	Stone::Stone(int x, int y, ResourceType rt) : Entity(x, y)
	{
		Gatherable* n = new Gatherable(rt, 35);
		AddComponent(n);
		entityType = EntityTypes::Stone;
		SetBitmap();
		World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;

	}


	void Stone::SetBitmap()
	{
		animations[State::Idle][Direction::Down].AddBitmap(IDB_STONE, RGB(255, 255, 255));
		size.x = animations[State::Idle][Direction::Down].Width();
		size.y = animations[State::Idle][Direction::Down].Height();
	}

	void  Stone::SetTarget(CPoint point, vector<Entity*> group) {}

	void Stone::onMove() {
		HitBox = CRect(point.x, point.y, point.x + size.x, point.y + size.y);
		remainAmount = this->GetComponent<Gatherable>()->resource.amount;
		if (remainAmount <= 0)
			World::getInstance()->killByID(this->ID);
	}

	Stone::~Stone()
	{
		World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 0;
		//TRACE("~Stone\n");
	}









}