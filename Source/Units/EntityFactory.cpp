#include "../StdAfx.h"
#include "EntityFactory.h"
#include "../World.h"
#include <exception>
#include "../mygame.h"

Unit::Entity* EntityFactory::SpawnEntity(int type, CPoint p) {
	register
    Unit::Entity* entity = NULL;
    switch (type)
    {
    case EntityTypes::Villager:
        entity = new Unit::Villager(p);
		CAudio::Instance()->Play(AUDIO_UNITCREATION, false);
        break;
    case EntityTypes::GoldMine:
        entity = new Unit::Mine(p, ResourceType::Gold);
		break;
	case EntityTypes::TownCenter:
		if (World::getInstance()->cheaterMode)
			entity = new Unit::TownCenter(p, 100);
		else
			entity = new Unit::TownCenter(p);
		break;
    case EntityTypes::Stone:
        entity = new Unit::Stone(p, ResourceType::Stone);
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
		CAudio::Instance()->Play(AUDIO_UNITCREATION, false);
		break;
	case EntityTypes::GoldMine:
		entity = new Unit::Mine(x, y, ResourceType::Gold);
		break;
	case EntityTypes::TownCenter:
		if(World::getInstance()->cheaterMode)
			entity = new Unit::TownCenter(x, y, 100);
		else
			entity = new Unit::TownCenter(x, y);
		break;
	case EntityTypes::Stone:
		entity = new Unit::Stone(x, y, ResourceType::Stone);
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