#pragma once
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <Vector>
#include "Units/Villager.h"

enum EntityTypes {
    Villager = 100000,

};

class EntityFactory {
public:
    Unit::Entity* SpawnEntity(int type, CPoint p){
        Unit::Entity* entity;
        switch (type)
        {
        case EntityTypes::Villager:
            entity = new Unit::Villager(p);
            break;
        default:
            break;
        }
        return entity;
    }
    Unit::Entity* SpawnEntity(int type, int x, int y) {
        Unit::Entity* entity;
        switch (type)
        {
        case EntityTypes::Villager:
            entity = new Unit::Villager(x, y);
            break;
        default:
            break;
        }
        return entity;
    }
};