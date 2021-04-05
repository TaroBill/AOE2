#pragma once
#include "./UnitBase.h"
#include <map>

namespace Unit
{


	class Entity :public UnitBase
	{
	public:
		enum class State
		{
			Idle, Move, Dead
		};
		enum class Direction
		{
			Down, LeftDown, Left, LeftUp, Up, RightUp, Right, RightDown
		};
	private:

	public:
		State entityState;;//�ʧ@���A
		Direction faceDirection;//���V���A
		map<State, map<Direction, CAnimation>> animations;//�ʵe


		void StateChanged(State s)
		{
			map<State, map<Direction, CAnimation>>::iterator it = animations.begin();
			while (it != animations.end())
			{
				map<Direction, CAnimation>::iterator it2 = it->second.begin();
				while (it2 != it->second.end())
				{
					it2->second.Reset();
				}
				it++;
			}
			entityState = s;
		}


		//���ݪ��a��ID
		int playerId;

		//��y��
		int tileX, tileY;

		//�I�y��
		int pointX, pointY;

		//��0�ɬO������A�j��1���ؿv
		int sizeXY;

		//��q
		int hp;
		int maxHP;


		CMovingBitmap bmp;
		CAnimation ani;
		virtual void onMove()
		{
			animations[entityState][faceDirection].OnMove();
			ani.OnMove();
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