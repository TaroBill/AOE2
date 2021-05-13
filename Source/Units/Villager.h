#pragma once
#include "Entity.h"
#include "UnitBase.h"
#include "Navigator.h"
#include "Gatherable.h"
#include "Attack.h"
#include <sstream>

#include "../Player/GameResource.h"
namespace Unit
{
	class Villager :public Entity 
	{
	public:

		void Serialize(stringstream &in)
		{
			in << "HP " << this->hp << " ";
			in << "maxHP " << this->maxHP << " ";
			in << "PointX " << this->point.x << " ";
			in << "PointY " << this->point.y << " ";
			in << "ID " << this->ID << " ";
			in << "playerID " << this->playerId << " ";
		}

		void deSerialize(stringstream &in)
		{
			string erase;
			in >> erase >> this->hp;
			in >> erase >> this->maxHP;
			in >> erase >> this->point.x;
			in >> erase >> this->point.y;
			in >> erase >> this->ID;
			in >> erase >> this->playerId;
		}

	public:
		enum class VillagerState
		{
			Base,
			GetResourceOnRoad,//���b�Ķ������W
			Gathering,//�Ķ���
			ReturnResourceOnRoad,//�Ķ�������A�N�귽�a�^�����W
			GoAttackOnRoad,//��x���W
			Attacking //���b����
		};
		
		VillagerState vs;

		int resourceCounter = 0;

		int attackCounter = 0;

		//�귽����a�W��
		int carryLimit;
		
		int navigatorState;
		//��a��
		GameResource carryResource;
		//�Ψ��x�s�W�Ӹ귽�I��m
		CPoint resourcePlace;
		//�귽�^�����I(�ټȮɨS�����X����)
		Entity* recyclePlace;

		//��귽���D���A�����������a�W�[�귽
		void ReturnResource();

		bool FindResouce();

		bool FindRecyclingPlace();

		//�Ķ�
		bool Gathering();
		//����
		void Attacking();

		void SetTarget(CPoint point , vector<Entity*> group);

		void SetTarget(CPoint point);
		//�]�m���I�̪񪺼ĤH(�θ귽�A�̷ӥ��b�����欰�P�w)��target
		void SetTargetByRange(CPoint point, VillagerState state);

		void SetBitmap();

		void onMove();

		void FSM(int navigatorState);


		Villager(int pointX, int pointY) ;

		Villager(CPoint point) ;
		Villager();
		 ~Villager();
	};
}