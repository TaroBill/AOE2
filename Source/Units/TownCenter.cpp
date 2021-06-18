#include "../World.h"

void Unit::TownCenter::SetBitmap()
{
	string str = "..\\RES\\Building\\TownCenterNotDone.bmp";
	animations[State::Idle][Direction::Down].AddBitmap(const_cast<char*>(str.c_str()), RGB(255, 255, 255));
	string str2 = "..\\RES\\Building\\TownCenter.bmp";
	animations[State::Idle][Direction::Up].AddBitmap(const_cast<char*>(str2.c_str()), RGB(0, 0, 0));
	size.x = animations[State::Idle][Direction::Down].Width();
	size.y = animations[State::Idle][Direction::Down].Height();
	HitBox = CRect(point.x, point.y, point.x + size.x, point.y + size.y);
}

void Unit::TownCenter::doneBuilding() 
{
	this->faceDirection = Direction::Up;
	isDoneBuilding = true;
}

void Unit::TownCenter::onMove()
{
	HitBox = CRect(point.x, point.y, point.x + size.x, point.y + size.y);
	if (this->hp == this->maxHP && !isDoneBuilding) {
		doneBuilding();
	}
}
Unit::TownCenter::TownCenter(int pointX, int pointY, int Hp = 1) :Entity(pointX, pointY)
{
	isDoneBuilding = false;
	isBuilding = true;
	SetBitmap();
	World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY()][GetTileX()+1] = 1;
	World::getInstance()->buildingMap[GetTileY()+1][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY()+1][GetTileX()+1] = 1;
	this->entityType = EntityTypes::TownCenter;
	this->hp = Hp;
}
Unit::TownCenter::TownCenter(CPoint point, int Hp = 1) :Entity(point)
{
	isDoneBuilding = false;
	isBuilding = true;
	SetBitmap();
	World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY()][GetTileX() + 1] = 1;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX() + 1] = 1;
	this->entityType = EntityTypes::TownCenter;
	this->hp = Hp;
}
Unit::TownCenter::TownCenter()
{
	isDoneBuilding = false;
	isBuilding = true;
	SetBitmap();
	World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY()][GetTileX() + 1] = 1;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX()] = 1;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX() + 1] = 1;
	this->entityType = EntityTypes::TownCenter;
	this->hp = 1;
}

Unit::TownCenter::~TownCenter()
{
	World::getInstance()->buildingMap[GetTileY()][GetTileX()] = 0;
	World::getInstance()->buildingMap[GetTileY()][GetTileX() + 1] = 0;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX()] = 0;
	World::getInstance()->buildingMap[GetTileY() + 1][GetTileX() + 1] = 0;
}
