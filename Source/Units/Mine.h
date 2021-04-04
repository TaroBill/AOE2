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
	int GetResource()
	{
		return resource.n--;
	}
	int GetResource(int n)
	{
		int temp = resource.n;
		resource.n -= temp;
		return temp;
	}
	Mine(ResourceType rt, int n)
	{
		sizeX = 3;
		sizeY = 3;
		resource = GameResource(rt, n);
		//Åª¤J¹ïÀ³bmp
		switch (rt)
		{
		case Gold:
			bmp.LoadBitmap(IDB_GOLD, RGB(255, 255, 255));
			break;
		case Stone:
			bmp.LoadBitmap(IDB_STONE, RGB(255, 255, 255));
			break;
		case Meat:
		case Wood:
		default:
			break;
		}
	}
	~Mine()
	{
	}
};