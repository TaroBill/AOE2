#pragma once

#include "../stdafx.h"


using namespace game_framework;

class UnitBase
{
public:
	int tileX, tileY;
	int hp;
	int maxHP;
	int movingSpeed;
	int playerId;
	CMovingBitmap bmp;
	void findpath(int targetTileX, int targetTileY)
	{

	}
	UnitBase(int playerId, int maxHP, int tileX, int tileY, int movingSpeed)
	{
		this->maxHP = maxHP;
		this->tileX = tileX;
		this->tileY = tileY;
		this->movingSpeed = movingSpeed;
		hp = maxHP;
		this->playerId = playerId;
	}
	void setBitmap(CMovingBitmap bmp)
	{
		this->bmp = bmp;
	}
};