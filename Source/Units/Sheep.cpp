#include "../World.h"


namespace Unit
{

	Sheep::Sheep(CPoint point, ResourceType rt) :Entity(point)
	{
		Gatherable* n = new Gatherable(rt, 35);
		AddComponent(n);
		AddComponent<Navigator>();
		entityType = EntityTypes::Sheep;
		SetBitmap();
		
	}

	Sheep::Sheep(int x, int y, ResourceType rt) : Entity(x, y)
	{
		Gatherable* n = new Gatherable(rt, 35);
		AddComponent(n);
		AddComponent<Navigator>();
		entityType = EntityTypes::Sheep;
		SetBitmap();
	}


	void Sheep::SetBitmap()
	{
		animations[State::Idle][Direction::Down].AddBitmap(IDB_SHEEP, RGB(0, 0, 0));
		size.x = animations[State::Idle][Direction::Down].Width();
		size.y = animations[State::Idle][Direction::Down].Height();
	}

	void Sheep::onShow(int screenX, int screenY)
	{
		animations[entityState][faceDirection].SetTopLeft(screenX, screenY);
		animations[entityState][faceDirection].OnShow();
	}

	void Sheep::SetTarget(CPoint point, vector<Entity*> group) {}

	void Sheep::onMove() {

		HitBox = CRect(point.x, point.y, point.x + size.x , point.y + size.y);
		remainAmount = this->GetComponent<Gatherable>()->resource.amount;
		GetComponent<Navigator>()->onMove(&point);
		if (remainAmount <= 0)
			World::getInstance()->killByID(this->ID);
	}


	Sheep::~Sheep()
	{
		World::getInstance()->buildingMap[GetTileY()][GetTileY()] = 0;
	}
}