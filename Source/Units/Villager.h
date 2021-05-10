#pragma once
#include "Entity.h"
#include "UnitBase.h"
#include "../Player/GameResource.h"
namespace Unit
{
	class Villager :public Entity
	{
	public:
		enum class VillagerState
		{
			Base,
			GetResourceOnRoad,//���b�Ķ������W
			Gathering,//�Ķ���
			ReturnResourceOnRoad,//�Ķ�������A�N�귽�a�^�����W

		};
		
		VillagerState vs;

		int resourceCounter;

		//�귽����a�W��
		int carryLimit;
		
		int navigatorState;
		//��a��
		GameResource carryResource;

		//��w���귽���a
		Entity* resourcePlace;

		//�귽�^�����I(�ټȮɨS�����X����)
		Entity* recyclePlace;

		//��귽���D���A�����������a�W�[�귽
		void ReturnResource();
		bool FindResouce();

		bool FindRecyclingPlace();

		//�Ķ�
		void Gathering();

		void SetTarget(CPoint point , vector<Entity*> group);

		void SetBitmap();

		void onMove();


		void FSM(int navigatorState);


		Villager(int pointX, int pointY) ;

		Villager(CPoint point) ;
		Villager();
		~Villager();
	};
}