#pragma once
#include "Entity.h"
#include "UnitBase.h"
#include "Navigator.h"
#include "Gatherable.h"
#include "../World.h"
#include <sstream>
namespace Unit
{
	class Villager :public Entity , public CObject
	{
	public: // �Ψӥ]�˦���CObject

		void* Villager::operator new(size_t nSize)
		{
			return malloc(nSize);
		}

		void operator delete(void* p)
		{
			free(p);
		}

		void Serialize(stringstream &in)
		{
			in << this->hp << this->maxHP << this->point.x << this->point.y << this->ID << this->playerId;
		}

		void deSerialize(stringstream &in)
		{
			in >> this->hp >> this->maxHP >> this->point.x >> this->point.y >> this->ID >> this->playerId;
		}

	public:
		enum class VillagerState
		{
			Base,
			GetResourceOnRoad,//���b�Ķ������W
			Gathering,//�Ķ���
			ReturnResourceOnRoad,//�Ķ�������A�N�귽�a�^�����W

		};
		
		VillagerState vs = VillagerState::Base;

		int resourceCounter = 0;

		//�귽����a�W��
		int carryLimit;
		
		//��a��
		GameResource carryResource;

		//��w���귽���a
		Entity* resourcePlace;

		//�귽�^�����I(�ټȮɨS�����X����)
		Entity* recyclePlace;

		//��귽���D���A�����������a�W�[�귽
		void ReturnResource()
		{
			TRACE("=========== now Return Resource =========== \n");
			//�ثe�ȹ�@�k�s�A�å���@�N�귽���۹��������a���W
		}

		bool FindResouce()
		{
			TRACE("=========== now Find Resouce =========== \n");
			return false;
		}

		bool FindRecyclingPlace()
		{
			TRACE("=========== now Find Recycling Place =========== \n");
			return false;
		}

		//�Ķ�
		void Gathering()
		{
			//���Ӧ���counter�֭p��
			//�֭p��������o�@�I�귽���ɭԤ~+1
			//��������
			this->carryResource.amount +=
				resourcePlace->GetComponent<Gatherable>()->resource.GetResource();
			
		}


		/*
		�I����Ĳ�o�@��
		���������A�I����P�_�I�O�_���i�Ķ��귽��A�P�_�O����귽�A���O�ʪ��N�����M������I�A�O�ʪ��h�P�_��q�C
		�����|�s�U��U��w���귽�����A�H�θ귽�ӷ��B�H�θ귽�^�����A�b�a����|�M���^�̪񪺸귽�^�����A�q�S�F�A�h�|��M��L���P�����q��
		*/
		//�]�w�ؼ�(�M��)
		void SetTarget(CPoint point, vector<Entity*> group) override
		{
			this->GetComponent<Unit::Navigator>()->FindPath(point, group);
		}

		void SetBitmap() override
		{
			for (int dire = 0; dire < 8; dire++)
			{
				for (int s = 0; s < 15; s++)
				{
					string str = "..\\RES\\Villager\\VillagerIdle_" + to_string(dire) + "_" + to_string(s) + ".bmp";
					State es = State::Idle;
					Direction d = static_cast<Direction>(dire);

					animations[es][d].AddBitmap(const_cast<char*>(str.c_str()), RGB(255, 255, 255));
				}
			}
		}

		void FSM(int navigatorState)
		{
			switch (vs)
			{
			case VillagerState::Base:
				break;
			case VillagerState::GetResourceOnRoad:
				//��F
				if (navigatorState == 1)
				{
					vs = VillagerState::Gathering;
				}
				break;
			//�Ķ���
			case VillagerState::Gathering:
				//�Ķ�
				Gathering();
				//�Y���F
				if (carryLimit == carryResource.amount)
				{
					//�N��a���
					if (FindRecyclingPlace())//���
					{


						//�������A�ܩ�귽�����W
						vs = VillagerState::ReturnResourceOnRoad;
					}
					else//�S���A�o�b
					{
						vs = VillagerState::Base;
						entityState = Entity::State::Idle;

					}
				}
				break;

			case VillagerState::ReturnResourceOnRoad:
				
				if (navigatorState == 1)
				{
					//��귽
					ReturnResource();

					if (FindResouce())//���
					{
						vs = VillagerState::GetResourceOnRoad;
					}
					else//�S���A�o�b
					{
						vs = VillagerState::Base;
						entityState = Entity::State::Idle;
					}
				}
				break;


			default:
				break;
			}
		}


		void onMove() override
		{
			int navigatorState = GetComponent<Navigator>()->onMove(&point);
			//FSM(navigatorState);
		}

		Villager(int pointX, int pointY) :Entity(pointX, pointY)
		{
			Navigator* n = new Navigator();
			AddComponent(n);
			carryLimit = 10;
			maxHP = 100;
			SetBitmap();
		}

		Villager(CPoint point):Entity(point)
		{
			Navigator* n = new Navigator();
			AddComponent(n);
			carryLimit = 10;
			maxHP = 100;
			SetBitmap();
		}
		Villager()
		{

			SetBitmap();
		}
		~Villager()
		{

		}
	};
}