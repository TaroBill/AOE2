#include "../World.h"

namespace Unit
{
	void init()
	{

	}
	Tree::Tree(CPoint point, ResourceType rt) :Entity(point)
	{
		Gatherable* n = new Gatherable(rt, 35);
		AddComponent(n);
		entityType = EntityTypes::Tree;
		SetBitmap();
		World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;

	}

	Tree::Tree(int x, int y, ResourceType rt) : Entity(x, y)
	{
		Gatherable* n = new Gatherable(rt, 35);
		AddComponent(n);
		entityType = EntityTypes::Tree;
		SetBitmap();
		World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;

	}


	void Tree::SetBitmap()
	{
		animations[State::Idle][Direction::Down].AddBitmap(IDB_TREE, RGB(255, 255, 255));
		size.x = animations[State::Idle][Direction::Down].Width();
		size.y = animations[State::Idle][Direction::Down].Height();
	}

	void Tree::onShow(int screenX,int screenY)
	{
		animations[entityState][faceDirection].SetTopLeft(screenX-size.x/2, screenY-size.y/2);
		animations[entityState][faceDirection].OnShow();
	}

	void Tree::SetTarget(CPoint point, vector<Entity*> group) {}

	void Tree::onMove() {
		HitBox = CRect(point.x, point.y, point.x + size.x/2, point.y + size.y/2);
		remainAmount = this->GetComponent<Gatherable>()->resource.amount;
		if (remainAmount <= 0)
			World::getInstance()->killByID(this->ID);
	}

	Tree::~Tree()
	{
		World::getInstance()->buildingMap[GetTileY()][GetTileY()] = 0;

		//TRACE("~Stone\n");
	}
}
