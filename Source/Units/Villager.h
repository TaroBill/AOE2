#pragma once
#include "Entity.h"
#include "UnitBase.h"
#include "Navigator.h"
#include "Gatherable.h"
#include "World.h"
namespace Unit
{
	class Villager :public Entity
	{
	public:
		enum class VillagerState
		{
			Idle,//���m�B���ݩR�O
			OnSetting,//�]�w�R�O���A���̰��u����
			GetResourceOnRoad,//���b�Ķ������W
			Gathering,//�Ķ���
			ReturnResourceOnRoad,//�Ķ�������A�N�귽�a�^�����W
			//SearchingResource �a�^�귽��A
			Attack
		};
		
		VillagerState vs = VillagerState::Idle;

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
		}

		void GetResource()
		{
			TRACE("=========== now Get Resource ing =========== \n");
		}

		void FindResouce()
		{
			TRACE("=========== now Find Resouce =========== \n");
		}

		void FindRecyclingPlace()
		{
			TRACE("=========== now Find Recycling Place =========== \n");
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
		void SetTarget(Entity* target) override
		{

			Gatherable* tar = (*target).GetComponent<Gatherable>();

			if (tar != nullptr)
			{
				switch (tar->resource.type)
				{
					resourcePlace = target;
				case ResourceType::Meat://��
					//�ؼ��٬��ۡA����or�إ�
					if (target->hp > 0)
					{
					}
					else
					{
						carryResource.ResetType(tar->resource.type);
					}
					break;

				case ResourceType::Wood://���Y
				case ResourceType::Stone://���q
				case ResourceType::Gold://���q
					carryResource.ResetType(tar->resource.type);
					vs = VillagerState::GetResourceOnRoad;
					GetComponent<Navigator>()->FindPath(target->pointX, target->pointY);
					break;

				default:
					break;
				}
			}
			else
			{
				//�S���
			}
		}


		void SetBitmap() override
		{
			for (int dire = 0; dire < 8; dire++)
			{
				for (int s = 0; s < 15; s++)
				{
					string str = ".\\RES\\Villager\\VillagerIdle_" + to_string(dire) + "_" + to_string(s) + ".bmp";
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
			case VillagerState::Idle:
				break;
			case VillagerState::OnSetting:
				break;
			case VillagerState::GetResourceOnRoad:
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
					FindRecyclingPlace();
					//�������A�ܩ�귽�����W
					vs = VillagerState::ReturnResourceOnRoad;
					//�M���h��귽
					FindRecyclingPlace();
				}
				break;

			case VillagerState::ReturnResourceOnRoad:

				break;

			case VillagerState::Attack:
				break;

			default:
				break;
			}
		}


		void onMove() override
		{
			int navigatorState = GetComponent<Navigator>()->onMove(&pointX, &pointY);
			FSM(navigatorState);
		}
		Villager(int pointX, int pointY) :Entity(pointX, pointY)
		{

			Navigator* n = new Navigator();
			AddComponent(n);
			carryLimit = 10;

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