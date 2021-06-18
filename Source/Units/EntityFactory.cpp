#include "EntityFactory.h"
#include "../World.h"
#include <exception>

Unit::Entity* EntityFactory::SpawnEntity(int type, CPoint p) {
	register
    Unit::Entity* entity = NULL;
    switch (type)
    {
    case EntityTypes::Villager:
        entity = new Unit::Villager(p);
        break;
    case EntityTypes::GoldMine:
        entity = new Unit::Mine(p, ResourceType::Gold);
        World::getInstance()->buildingMap[(int)(p.y / 50)][(int)(p.x / 50)] = 1;
		break;
	case EntityTypes::TownCenter:
		entity = new Unit::TownCenter(p);
		World::getInstance()->buildingMap[(int)(p.y / 50)][(int)(p.x / 50)] = 1;
		break;
    case EntityTypes::Stone:
        entity = new Unit::Stone(p, ResourceType::Stone);
        World::getInstance()->buildingMap[(int)(p.y / 50)][(int)(p.x / 50)] = 1;
        break;
	case EntityTypes::Tree:
		entity = new Unit::Tree(p, ResourceType::Wood);
		break;
	case EntityTypes::Sheep:
		entity = new Unit::Sheep(p, ResourceType::Food);
	default:
        break;
    }
    return entity;
}

Unit::Entity* EntityFactory::SpawnEntity(int type, int x, int y) {
    Unit::Entity* entity = NULL;
	switch (type)
	{
	case EntityTypes::Villager:
		entity = new Unit::Villager(x, y);
		break;
	case EntityTypes::GoldMine:
		entity = new Unit::Mine(x, y, ResourceType::Gold);
		World::getInstance()->buildingMap[(int)(y / 50)][(int)(x / 50)] = 1;
		break;
	case EntityTypes::TownCenter:
		entity = new Unit::TownCenter(x, y);
		World::getInstance()->buildingMap[(int)(y / 50)][(int)(x / 50)] = 1;
		break;
	case EntityTypes::Stone:
		entity = new Unit::Stone(x, y, ResourceType::Stone);
		World::getInstance()->buildingMap[(int)(y / 50)][(int)(x / 50)] = 1;
		break;
	case EntityTypes::Tree:
		entity = new Unit::Tree(x, y, ResourceType::Wood);
		break;
	case EntityTypes::Sheep:
		entity = new Unit::Sheep(x,y, ResourceType::Food);
	default:
		break;
	}
    return entity;
}