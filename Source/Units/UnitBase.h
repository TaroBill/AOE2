#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
/*
*/
using namespace game_framework;
namespace Unit
{

	class UnitBase
	{
	public:
		int tileX, tileY;
		int pointX, pointY;
		//��0�ɬO������A�j��1���ؿv
		int sizeXY;
		int hp;
		int maxHP;
		int movingSpeed;
		//���ݪ��a��ID
		int playerId;
		CMovingBitmap bmp;
		void onMove();
		void onShow(int, int);
		virtual void findpath(int tileX, int tileY, int& map)
		{

		}
		void setBitmap(CMovingBitmap bmp)
		{
			this->bmp = bmp;
		}
		//�V�U�૬
		Villager mineCast(UnitBase ub)
		{
			Villager m = Villager(ub.playerId, ub.tileX, ub.tileY, ub.pointX, ub.pointY, ub.maxHP, ub.movingSpeed);
			return m;
		}
		//�غc�l
		UnitBase()
		{
			tileX = 0;
			tileY = 0;
			pointX = 0;
			pointY = 0;
			maxHP = 1;
			sizeXY = 0;
			hp = maxHP;
			playerId = 0;
			movingSpeed = 0;
		}
		UnitBase(int PlayerID)
		{
			this->playerId = playerId;
		}
		UnitBase(int playerid, int tilex, int tiley, int pointx, int pointy, int maxhp, int movingSpeed)
		{
			this->playerId = playerid;
			this->tileX = tilex;
			this->tileY = tiley;
			this->pointX = pointx;
			this->pointY = pointy;
			this->maxHP = maxhp;
			this->movingSpeed = movingSpeed;
		}

	};
}