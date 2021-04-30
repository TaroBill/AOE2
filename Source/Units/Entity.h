#pragma once
#include "./UnitBase.h"
#include <map>

namespace Unit
{
	class Entity :public UnitBase
	{
	public:
		//���骺���A
		//�R��ʡB���ʡB���ˡB���`�B��L
		//��ܨ�L�ɡA�H��쪬�A���u��
		enum class State
		{
			Idle, Move, Hurted, Dead, Extra
		};
		//���骺�K��V���V
		enum class Direction
		{
			Down, LeftDown, Left, LeftUp, Up, RightUp, Right, RightDown
		};
	private:

	public:
		//�ʧ@���A
		State entityState;
		//���V���A
		Direction faceDirection;
		//�ʵe
		map<State, map<Direction, CAnimation>> animations;
		//���A���m�ɡA�ϰʵe���m
		//���ܭ��V�ɤ��ݭn�եΦ��禡
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
		//���ܪ��A(�D���V)
		void StateChange(State s)
		{
			StateReset();
			entityState = s;

		}


		//���ݪ��a��ID
		int playerId;

		//�I�y��
		//int pointX, pointY;
		CPoint point;
		//��0�ɬO������A�j��1���ؿv
		int sizeXY;

		//��q
		int hp;
		int maxHP;

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
		virtual void SetTarget(CPoint point) = NULL;
		virtual void SetBitmap() = NULL;
		void Init()
		{
			this->playerId = 0;
			this->sizeXY = 0;
			this->maxHP = 100;
			this->hp = this->maxHP;;
			this->entityState = State::Idle;
			this->faceDirection = Direction::Down;
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
		~Entity()
		{
			delete this;
		}
	};
}