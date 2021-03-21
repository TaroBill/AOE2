#pragma once


#include "Component.h"

#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"

namespace GameObject
{
	class Building :public Component
	{
	public:
		int tileX, tileY;
		int sizeX, sizeY;
		int hp;
		int lineOfSight;
		//宣告圖
		game_framework::CMovingBitmap bmp;
		Building()
		{

			TRACE("建立 Building\n");
			this->hp = 0;
			this->sizeX = 0;
			this->sizeY = 0;
			this->lineOfSight = 0;
			this->tileX = 0;
			this->tileY = 0;
		}

		~Building()
		{
			TRACE("刪除 building\n");
		}
	};
}
