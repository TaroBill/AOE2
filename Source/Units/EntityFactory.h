#pragma once
#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include <Vector>
#include "Villager.h"
#include "Mine.h"
#include "Stone.h"

class EntityFactory {
public:
    Unit::Entity* SpawnEntity(int, CPoint);

    Unit::Entity* SpawnEntity(int, int, int);
};