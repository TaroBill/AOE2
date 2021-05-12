#pragma once
#include "../World.h"

//把資源放到主城，讓對應的玩家增加資源
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
	//目前僅實作歸零，並未實作將資源放到相對應的玩家身上
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

//採集
void Unit::Villager::Gathering()
{
	//應該有個counter累計值
	//累計到應該獲得一點資源的時候才+1
	//但先不管
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
點擊時觸發一次
選取村民後，點擊後判斷點是否為可採集資源後，判斷是什麼資源，不是動物就直接尋路到該點，是動物則判斷血量。
村民會存下當下鎖定的資源種類，以及資源來源、以及資源回收站，在帶滿後會尋路回最近的資源回收站，礦沒了，則會找尋其他的同種類礦物
*/
//設定目標(尋路)
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

		//到了
		if (navigatorState == 1)
		{
			vs = VillagerState::Gathering;
		}
		break;
		//採集中
	case VillagerState::Gathering:
		//TRACE("Gathering\n");

		//採集
		Unit::Villager::Gathering();
		//若滿了
		if (carryResource.amount>= carryLimit )
		{
			//就找地方放
			if (FindRecyclingPlace())//找到
			{


				//切換狀態至放資源的路上
				vs = VillagerState::ReturnResourceOnRoad;
				SetTarget(recyclePlace->point );
			}
			else//沒找到，發呆
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
			//放資源
			ReturnResource();

			if (FindResouce())//找到
			{
				vs = VillagerState::GetResourceOnRoad;
			}
			else//沒找到，發呆
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
