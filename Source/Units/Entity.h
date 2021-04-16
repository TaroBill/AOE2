#pragma once
#include "./UnitBase.h"
#include <map>

namespace Unit
{
	class Entity :public UnitBase
	{
	public:
		//實體的狀態
		//靜止不動、移動、受傷、死亡、其他
		//選擇其他時，以單位狀態為優先
		enum class State
		{
			Idle, Move, Hurted, Dead, Other
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
		void ChangeDirection(int i)
		{
			//faceDirection = static_cast<Unit::Entity::Direction>(i);
		}
		//改變狀態(非面向)
		void StateChange(State s)
		{
			StateReset();
			entityState = s;

		}


		//所屬玩家的ID
		int playerId;

		//點座標
		int pointX, pointY;

		//為0時是角色單位，大於1為建築
		int sizeXY;

		//血量
		int hp;
		int maxHP;

		int GetTileX() { return pointX / 50; }
		int GetTileY() { return pointY / 50; }
		int Point2Tile(int p) { return p / 50; }
		int Tile2Point(int t) { return t / 50; }

		virtual void onMove()
		{
			animations[entityState][faceDirection].OnMove();
		}

		virtual void onShow(int screenX, int screenY)
		{
			animations[entityState][faceDirection].SetTopLeft(screenX, screenY);
			animations[entityState][faceDirection].OnShow();

		}

		virtual void SetTarget(Entity* target) = NULL;

		virtual void SetBitmap() = NULL;
		Entity()
		{
			this->playerId = 0;

			this->pointX = 0;
			this->pointY = 0;
			this->sizeXY = 0;
			this->maxHP = 0;
			this->hp = this->maxHP;;
			this->entityState = State::Idle;
			this->faceDirection = Direction::Down;
		}
		Entity(int pointX, int pointY) :Entity()
		{
			this->playerId = 0;
			this->pointX = 0;
			this->pointY = 0;
			this->sizeXY = 0;
			this->maxHP = 0;
			this->hp = this->maxHP;;
			this->entityState = State::Idle;
			this->faceDirection = Direction::Down;
			this->pointX = pointX;
			this->pointY = pointY;
		}
	};
}