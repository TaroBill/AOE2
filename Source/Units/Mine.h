#pragma once
#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"

#include "../Player/GameResource.h"
namespace Unit
{
	class Mine
	{
	public:
		game_framework::CMovingBitmap bmp;
		int sizeX, sizeY;
		GameResource resource;
		Mine(ResourceType rt, int n)
		{
			sizeX = 3;
			sizeY = 3;
			resource = GameResource(rt, n);
			//Åª¤J¹ïÀ³bmp
			switch (rt)
			{
			case ResourceType::None:
				break;
			case ResourceType::Gold:
				bmp.LoadBitmap(IDB_GOLD, RGB(255, 255, 255));
				break;
			case ResourceType::Stone:
				bmp.LoadBitmap(IDB_STONE, RGB(255, 255, 255));
				break;
			case ResourceType::Meat:
				break;
			case ResourceType::Wood:
				break;
			default:
				break;
			}
		}
		~Mine()
		{
		}
	};
}