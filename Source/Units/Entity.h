#pragma once
#include "./UnitBase.h"
#include <map>

namespace Unit
{


	class Entity :public UnitBase
	{
	public:
		//實體的狀態
		//靜止不動、移動、受傷、死亡
		enum class State
		{
			Idle, Move,Hurted, Dead
		};
		//實體的八方向面向
		enum class Direction
		{
			Down, LeftDown, Left, LeftUp, Up, RightUp, Right, RightDown
		};
	private:

	public:
		//動作狀態
		State entityState;
		//面向狀態
		Direction faceDirection;
		//動畫
		map<State, map<Direction, CAnimation>> animations;
		//狀態重置時，使動畫重置
		//改變面向時不需要調用此函式
		void StateReset()
		{
			map<State, map<Direction, CAnimation>>::iterator it = animations.begin();
			while (it != animations.end())
			{
				map<Direction, CAnimation>::iterator it2 = it->second.begin();
				while (it2 != it->second.end())
				{
					it2->second.Reset();
					it2++;
				}
				it++;
			}
		}
		//改變狀態(非面向)
		void StateChange(State s) 
		{
			StateReset();
			entityState = s;
		}


		//所屬玩家的ID
		int playerId;

		//格座標
		int tileX, tileY;

		//點座標
		int pointX, pointY;

		//為0時是角色單位，大於1為建築
		int sizeXY;

		//血量
		int hp;
		int maxHP;


		virtual void onMove()
		{
			animations[entityState][faceDirection].OnMove();
		}

		void onShow(int screenX, int screenY)
		{
			animations[entityState][faceDirection].SetTopLeft(screenX, screenY);
			animations[entityState][faceDirection].OnShow();

		}

		virtual void SetBitmap() = 0;
		Entity()
		{
			this->playerId = 0;
			this->tileX = 0;
			this->tileY = 0;
			this->pointX = 0;
			this->pointY = 0;
			this->sizeXY = 0;
			this->maxHP = 0;
			this->hp = this->maxHP;;
			this->entityState = State::Idle;
			this->faceDirection = Direction::Down;
		}
		Entity(int tileX, int tileY) :Entity()
		{
			this->tileX = tileX;
			this->tileY = tileY;
		}
	};
}