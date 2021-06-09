#include "../World.h"

void Unit::TownCenter::SetBitmap()
{
	string str = "..\\RES\\Building\\TownCenter.bmp";
	animations[State::Idle][Direction::Down].AddBitmap(const_cast<char*>(str.c_str()), RGB(0, 0, 0));
	size.x = animations[State::Idle][Direction::Down].Width();
	size.y = animations[State::Idle][Direction::Down].Height();
	HitBox = CRect(point.x, point.y, point.x + size.x, point.y + size.y);
}

void Unit::TownCenter::onMove()
{
	HitBox = CRect(point.x, point.y, point.x + size.x, point.y + size.y);
}
Unit::TownCenter::TownCenter(int pointX, int pointY) :Entity(pointX, pointY)
{
	SetBitmap();
	World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY()][GetTileX()+1] = 1;
	World::getInstance()->buildingMap[GetTileY()+1][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY()+1][GetTileX()+1] = 1;
	this->entityType = EntityTypes::TownCenter;

}
Unit::TownCenter::TownCenter(CPoint point) :Entity(point)
{
	SetBitmap();
	World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY()][GetTileX() + 1] = 1;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX() + 1] = 1;
	this->entityType = EntityTypes::TownCenter;
}
Unit::TownCenter::TownCenter()
{
	SetBitmap();
	World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY()][GetTileX() + 1] = 1;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX() + 1] = 1;
	this->entityType = EntityTypes::TownCenter;
}

Unit::TownCenter::~TownCenter()
{
	World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 0;
	World::getInstance()->buildingMap[GetTileY()][GetTileX() + 1] = 0;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX()] = 0;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX() + 1] = 0;
}
