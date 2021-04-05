#pragma once
#include "./UnitBase.h"
#include <map>

namespace Unit
{


	class Entity :public UnitBase
	{
	public:
		//���骺���A
		//�R��ʡB���ʡB���ˡB���`
		enum class State
		{
			Idle, Move,Hurted, Dead
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
		//���ܪ��A(�D���V)
		void StateChange(State s) 
		{
			StateReset();
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