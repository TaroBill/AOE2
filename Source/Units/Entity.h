#pragma once
#include "./UnitBase.h"
#include <map>
#include "../ID.h"

enum EntityTypes {
	Villager = 100000,
	GoldMine,
	TownCenter,
	Stone,
	Tree,
	Sheep
};

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
			Idle, Move, Hurted, Dead, Extra
		};
		//實體的八方向面向
		enum class Direction
		{
			Down, LeftDown, Left, LeftUp, Up, RightUp, Right, RightDown
		};

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

		unsigned int ID;
		//點座標
		//int pointX, pointY;
		CPoint point;
		//角色的圖大小
		CPoint size;
		//角色的點擊HitBox
		CRect HitBox;
		//鎖定的實體
		struct ShortEntity {
			unsigned int ID;
			CPoint point;
			bool isLive = false;
		}target;
		//血量
		int hp;
		int maxHP;
		bool isBuilding = false;
		//這個實體的entityType
		EntityTypes entityType;

		int GetTileX() { return point.x / 50; }
		int GetTileY() { return point.y / 50; }
		CPoint GetTile() { return CPoint(GetTileX(), GetTileY()); }
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

		//virtual void SetTarget(Entity* target) = NULL;
		//virtual void SetTarget(CPoint point) = NULL;
		virtual void SetTarget(CPoint point, vector<Entity*> group) {};
		virtual void SetTarget(CPoint point) {};

		virtual void SetBitmap(){};


		void Init()
		{
			this->playerId = 0;
			this->maxHP = 100;
			this->hp = this->maxHP;;
			this->entityState = State::Idle;
			this->faceDirection = Direction::Down;
			this->ID = ID::getInstance()->GetID();
		}
		bool operator==(Entity& other) {
			if (this->ID == other.ID)
			{
				return true;
			}
			return false;
		}
		Entity()
		{
			Init();
		}
		Entity(int pointX, int pointY)
		{
			Init();

			this->point.x = pointX;
			this->point.y = pointY;

		}
		Entity(CPoint point) :Entity()
		{
			Init();
			this->point = point;
		}

		virtual ~Entity()
		{
			//TRACE("~Entity%d\n",this->ID);
		}

		//copy constructor
		Entity(const Entity& entity) {
			this->entityType = entity.entityType;
			this->playerId = entity.playerId;
			this->maxHP = entity.maxHP;
			this->hp = entity.hp;
			this->entityState = entity.entityState;
			this->faceDirection = entity.faceDirection;
			this->ID = entity.ID;
			this->point = entity.point;
			this->size = entity.size;
			this->HitBox = entity.HitBox;
		}

		//copy assignment
		Entity operator=(const Entity& entity) {
			this->entityType = entity.entityType;
			this->playerId = entity.playerId;
			this->maxHP = entity.maxHP;
			this->hp = entity.hp;
			this->entityState = entity.entityState;
			this->faceDirection = entity.faceDirection;
			this->ID = entity.ID;
			this->point = entity.point;
			this->size = entity.size;
			this->HitBox = entity.HitBox;
			return *this;
		}

	};
}