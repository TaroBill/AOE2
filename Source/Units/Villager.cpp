#pragma once
#include "../World.h"

//��귽���D���A�����������a�W�[�귽
void Unit::Villager::ReturnResource()
{
	TRACE("=========== now Return Resource =========== \n");
	//�ثe�ȹ�@�k�s�A�å���@�N�귽���۹��������a���W
}

bool Unit::Villager::FindResouce()
{
	TRACE("=========== now Find Resouce =========== \n");
	return false;
}

bool Unit::Villager::FindRecyclingPlace()
{
	TRACE("=========== now Find Recycling Place =========== \n");
	return false;
}

//�Ķ�
void Unit::Villager::Gathering()
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
void Unit::Villager::SetTarget(CPoint point, vector<Entity*> group)
{
	vector<Entity*> temp = World::getInstance()->listAllEntityInRange(
		CPoint(point.x - 100, point.y - 100),
		CPoint(point.x + 100, point.y + 100));
	if (temp.size() > 0 && temp[0]->GetComponent<Gatherable>() != nullptr)
	{
		vs = VillagerState::GetResourceOnRoad;
		resourcePlace = temp[0];
		this->carryResource.ResetType(
			temp[0]->GetComponent<Gatherable>()->resource.type);
	}
	this->GetComponent<Unit::Navigator>()->FindPath(point, group);
}

void Unit::Villager::SetBitmap()
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

void Unit::Villager::FSM(int navigatorState)
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
		Unit::Villager::Gathering();
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


void Unit::Villager::onMove()
{
	navigatorState = GetComponent<Navigator>()->onMove(&point);
	this->FSM(navigatorState);
}

Unit::Villager::Villager(int pointX, int pointY) :Entity(pointX, pointY)
{
	Navigator* n = new Navigator();
	AddComponent(n);
	carryLimit = 10;
	maxHP = 100;
	SetBitmap();
}

Unit::Villager::Villager(CPoint point) :Entity(point)
{
	Navigator* n = new Navigator();
	AddComponent(n);
	carryLimit = 10;
	maxHP = 100;
	SetBitmap();
}
Unit::Villager::Villager()
{
	SetBitmap();
}
Unit::Villager::~Villager()
{
	TRACE("~Villager\n");
}
