#pragma once
#include "../World.h"

//��귽���D���A�����������a�W�[�귽
void Unit::Villager::ReturnResource()
{
	switch (this->carryResource.type)
	{
	case ResourceType::Gold:
		World::getInstance()->player.gold += this->carryResource.amount;
		break;
	case ResourceType::Food:
		World::getInstance()->player.food += this->carryResource.amount;
		break;
	case ResourceType::Stone:
		World::getInstance()->player.stone += this->carryResource.amount;
		break;
	case ResourceType::Wood:
		World::getInstance()->player.wood += this->carryResource.amount;
		break;
	case ResourceType::None:
		break;
	default:
		break;
	}
	this->carryResource.amount = 0;
	//�ثe�ȹ�@�k�s�A�å���@�N�귽���۹��������a���W
}

bool Unit::Villager::FindResouce()
{

	//TRACE("=========== now Find Resouce =========== \n");
	this->GetComponent<Unit::Navigator>()->FindPath(target->point);
	return true;
}

bool Unit::Villager::FindRecyclingPlace()
{
	//TRACE("=========== now Find Recycling Place =========== \n");

	for (size_t i = 0; i < World::getInstance()->unit.size(); i++)
	{
		if (dynamic_cast<TownCenter*>( World::getInstance()->unit.at(i)))
		{
			recyclePlace = World::getInstance()->unit.at(i);
			return true;
		}
	}
	return false;
}

//�Ķ�
void Unit::Villager::Gathering()
{
	//���Ӧ���counter�֭p��
	//�֭p��������o�@�I�귽���ɭԤ~+1
	//��������
	resourceCounter++;
	if (resourceCounter >= 15)
	{
		resourceCounter = 0;
		this->carryResource.amount +=
			target->GetComponent<Gatherable>()->resource.GetResource();
		TRACE("ID:%d now carryResource:%d\n", this->ID,this->carryResource.amount);
	}

}


/*
�I����Ĳ�o�@��
���������A�I����P�_�I�O�_���i�Ķ��귽��A�P�_�O����귽�A���O�ʪ��N�����M������I�A�O�ʪ��h�P�_��q�C
�����|�s�U��U��w���귽�����A�H�θ귽�ӷ��B�H�θ귽�^�����A�b�a����|�M���^�̪񪺸귽�^�����A�q�S�F�A�h�|��M��L���P�����q��
*/
//�]�w�ؼ�(�M��)
void Unit::Villager::SetTarget(CPoint point, vector<Entity*> group)
{
	Entity* temp = World::getInstance()->getNearestEntity(point);
	if (temp != NULL) {
		TRACE("Target set to %d\n", temp->ID);
		if (temp->GetComponent<Gatherable>() != nullptr)
		{
			TRACE("On gather road\n");
			vs = VillagerState::GetResourceOnRoad;
			target = temp;
			this->carryResource.ResetType(
				temp->GetComponent<Gatherable>()->resource.type);
		}
		else if (dynamic_cast<TownCenter*>(temp))
		{
			//TRACE("TC\n");
			vs = VillagerState::ReturnResourceOnRoad;
		}
	}
	else
	{
		vs = VillagerState::Base;
	}
	this->GetComponent<Unit::Navigator>()->FindPath(point, group);
}
void Unit::Villager::SetTarget(CPoint point)
{
	Entity* temp = World::getInstance()->getNearestEntity(point);
	if (temp != NULL) {
		TRACE("Target set to %d\n", temp->ID);
		if (temp->GetComponent<Gatherable>() != nullptr)
		{
			TRACE("On gather road\n");
			vs = VillagerState::GetResourceOnRoad;
			target = temp;
			this->carryResource.ResetType(
				temp->GetComponent<Gatherable>()->resource.type);
			
		}
		else if (dynamic_cast<TownCenter*>( temp ))
		{
			//TRACE("TC\n");
			vs = VillagerState::ReturnResourceOnRoad;
		}
	}
	else
	{
		vs = VillagerState::Base;
	}
	this->GetComponent<Unit::Navigator>()->FindPath(point);
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
	size.x = animations[State::Idle][Direction::Down].Width();
	size.y = animations[State::Idle][Direction::Down].Height();
	HitBox = CRect(point.x, point.y, point.x + size.x, point.y + size.y);
}

void Unit::Villager::FSM(int navigatorState)
{
	switch (vs)
	{
	case VillagerState::Base:
		break;
	case VillagerState::GetResourceOnRoad:
		//TRACE("GetResourceOnRoad\n");

		//��F
		if (navigatorState == 1)
		{
			vs = VillagerState::Gathering;
		}
		break;
		//�Ķ���
	case VillagerState::Gathering:
		//TRACE("Gathering\n");

		//�Ķ�
		Unit::Villager::Gathering();
		//�Y���F
		if (carryResource.amount>= carryLimit )
		{
			//�N��a���
			if (FindRecyclingPlace())//���
			{


				//�������A�ܩ�귽�����W
				vs = VillagerState::ReturnResourceOnRoad;
				SetTarget(recyclePlace->point );
			}
			else//�S���A�o�b
			{
				vs = VillagerState::Base;
				entityState = Entity::State::Idle;

			}
		}
		break;

	case VillagerState::ReturnResourceOnRoad:
		//TRACE("ReturnResourceOnRoad\n");
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
	resourceCounter = 0;
	SetBitmap();
}

Unit::Villager::Villager(CPoint point) :Entity(point)
{
	Navigator* n = new Navigator();
	AddComponent(n);
	carryLimit = 10;
	maxHP = 100;
	damage = 10;
	resourceCounter = 0;
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
