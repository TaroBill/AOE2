#pragma once
#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"

#include "../Player/GameResource.h"

class Mine
{
public:
	game_framework::CMovingBitmap bmp;
	int sizeX, sizeY;
	GameResource resource;
	GameResource getResource()
	{
		return resource;
	}
	Mine()
	{
		resource = GameResource(Gold,100 );
	}
	~Mine()
	{
	}
};