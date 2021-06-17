#pragma once
#include "../World.h"

//把資源放到主城，讓對應的玩家增加資源
void Unit::Villager::ReturnResource()
{
	if (this->playerId != 0)//不是己方村民放資源不要理他
	{
		this->carryResource.amount = 0;
		return;
	}
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
	SetTargetByRange(resourcePlace, VillagerState::Gathering);
	if (!target.isLive)
		return false;
	//TRACE("=========== now Find Resouce =========== \n");
	//this->GetComponent<Unit::Navigator>()->FindPath(target.point);
	return true;
}

bool Unit::Villager::FindRecyclingPlace()
{
	//TRACE("=========== now Find Recycling Place =========== \n");
	if (this->playerId == 0) {
		for (size_t i = 0; i < World::getInstance()->unit.size(); i++)
		{
			if (dynamic_cast<TownCenter*>(World::getInstance()->unit.at(i)))
			{
				recyclePlace = World::getInstance()->unit.at(i);
				return true;
			}
		}
	}
	else if (this->playerId == 1) {
		for (size_t i = 0; i < World::getInstance()->EnemyUnit.size(); i++)
		{
			if (dynamic_cast<TownCenter*>(World::getInstance()->EnemyUnit.at(i)))
			{
				recyclePlace = World::getInstance()->EnemyUnit.at(i);
				return true;
			}
		}
	}
	return false;
}

//採集
bool Unit::Villager::Gathering()
{
	//應該有個counter累計值
	//累計到應該獲得一點資源的時候才+1
	//但先不管
	resourceCounter++;
	if (resourceCounter >= 15)
	{
		resourceCounter = 0;
		if (target.isLive == false)
			return false;
		this->carryResource.amount +=
			World::getInstance()->getEntityByID(target.ID)->GetComponent<Gatherable>()->resource.GetResource();
		TRACE("ID:%d now carryResource:%d\n", this->ID,this->carryResource.amount);
	}
	return true;
}

//攻擊
void Unit::Villager::Attacking()
{
	attackCounter++;
	if (attackCounter >= 20)
	{
		attackCounter = 0;
		if (!this->GetComponent<Attack>()->doAttack()) {
			this->SetTargetByRange(target.point, VillagerState::Attacking);
			vs = VillagerState::GoAttackOnRoad; //追擊
		}
		TRACE("ID:%d now attacking:%d\n", this->ID, this->target.ID);
	}

}

bool Unit::Villager::Building() {
	resourceCounter++;
	if (resourceCounter >= 15)
	{
		//TRACE("Building towncenter\n");
		resourceCounter = 0;
		Entity* e = World::getInstance()->getEntityByID(target.ID);
		if (e == NULL) {
			TRACE("can't find Building %d\n", target.ID);
			return false;
		}
		else if (e->hp == e->maxHP)
			return false;
		e->hp = (e->hp + 10 > e->maxHP) ? e->maxHP : (e->hp + 10);
	}
	return true;
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
			target.ID = temp->ID;
			target.point = temp->point;
			target.isLive = true;
			this->carryResource.ResetType(
				temp->GetComponent<Gatherable>()->resource.type);
		}
		else if (temp->isBuilding && temp->playerId == 1 && this->playerId == 1) {
			if (temp->hp < temp->maxHP) {
				vs = VillagerState::BuildingOnRoad;
				target.ID = temp->ID;
				target.point = temp->point;
				target.isLive = true;
			}
			else if (dynamic_cast<TownCenter*>(temp) && dynamic_cast<TownCenter*>(temp)->isDoneBuilding)
			{
				//TRACE("TC\n");
				vs = VillagerState::ReturnResourceOnRoad;
			}

		}
		else if (temp->isBuilding && temp->playerId == 0 && this->playerId == 0) {
			if (temp->hp < temp->maxHP) {
				vs = VillagerState::BuildingOnRoad;
				target.ID = temp->ID;
				target.point = temp->point;
				target.isLive = true;
			}
			else if (dynamic_cast<TownCenter*>(temp) && dynamic_cast<TownCenter*>(temp)->isDoneBuilding)
			{
				//TRACE("TC\n");
				vs = VillagerState::ReturnResourceOnRoad;
			}
		}
		else if (temp->playerId == 1 && this->playerId == 0) {
			vs = VillagerState::GoAttackOnRoad;
			target.ID = temp->ID;
			target.point = temp->point;
			target.isLive = true;
		}
		else if (temp->playerId == 0 && this->playerId == 1) {
			vs = VillagerState::GoAttackOnRoad;
			target.ID = temp->ID;
			target.point = temp->point;
			target.isLive = true;
		}
	}
	else
	{
		target.isLive = false;
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
			resourcePlace = temp->point;
			vs = VillagerState::GetResourceOnRoad;
			target.ID = temp->ID;
			target.point = temp->point;
			target.isLive = true;
			this->carryResource.ResetType(
				temp->GetComponent<Gatherable>()->resource.type);
			
		}
		else if (temp->isBuilding && temp->playerId == 1 && this->playerId == 1) {
			if (temp->hp < temp->maxHP) {
				vs = VillagerState::BuildingOnRoad;
				target.ID = temp->ID;
				target.point = temp->point;
				target.isLive = true;
			}
			else if (dynamic_cast<TownCenter*>(temp) && dynamic_cast<TownCenter*>(temp)->isDoneBuilding)
			{
				//TRACE("TC\n");
				vs = VillagerState::ReturnResourceOnRoad;
			}
		}
		else if (temp->isBuilding && temp->playerId == 0 && this->playerId == 0) {
			if (temp->hp < temp->maxHP) {
				vs = VillagerState::BuildingOnRoad;
				target.ID = temp->ID;
				target.point = temp->point;
				target.isLive = true;
			}
			else if (dynamic_cast<TownCenter*>(temp) && dynamic_cast<TownCenter*>(temp)->isDoneBuilding)
			{
				//TRACE("TC\n");
				vs = VillagerState::ReturnResourceOnRoad;
			}
		}
		else if (temp->playerId == 1 && this->playerId == 0) {
			vs = VillagerState::GoAttackOnRoad;
			target.ID = temp->ID;
			target.point = temp->point;
			target.isLive = true;
		}
		else if (temp->playerId == 0 && this->playerId == 1) {
			vs = VillagerState::GoAttackOnRoad;
			target.ID = temp->ID;
			target.point = temp->point;
			target.isLive = true;
		}
	}
	else
	{
		target.isLive = false;
		vs = VillagerState::Base;
	}
	this->GetComponent<Unit::Navigator>()->FindPath(point);
}

void Unit::Villager::SetTargetByRange(CPoint point, VillagerState states)
{
	CRect nearbyRange = CRect(point.x - 100, point.y - 100, point.x + 100, point.y + 100);
	vector<Entity*> entitys;
	switch (states) {
	case VillagerState::Attacking:
		if (this->playerId == 0) {
			entitys = World::getInstance()->EnemyUnit;
			for (unsigned int i = 0; i < entitys.size(); i++) {
				if (nearbyRange.PtInRect(entitys[i]->point)) {
					vs = VillagerState::GoAttackOnRoad;
					target.ID = entitys[i]->ID;
					target.point = entitys[i]->point;
					target.isLive = true;
					this->GetComponent<Unit::Navigator>()->FindPath(point);
					return;
				}
			}
			break;
		}
		else if (this->playerId == 1) {
			entitys = World::getInstance()->unit;
			for (unsigned int i = 0; i < entitys.size(); i++) {
				if (nearbyRange.PtInRect(entitys[i]->point)) {
					vs = VillagerState::GoAttackOnRoad;
					target.ID = entitys[i]->ID;
					target.point = entitys[i]->point;
					target.isLive = true;
					this->GetComponent<Unit::Navigator>()->FindPath(point);
					return;
				}
			}
			break;
		}
	case VillagerState::Gathering:
		entitys = World::getInstance()->ResaurceUnit;
		for (unsigned int i = 0; i < entitys.size(); i++) {
			if (nearbyRange.PtInRect(entitys[i]->point)) {
				vs = VillagerState::GoAttackOnRoad;
				target.ID = entitys[i]->ID;
				target.point = entitys[i]->point;
				target.isLive = true;
				this->GetComponent<Unit::Navigator>()->FindPath(point);
				return;
			}
		}
		break;
	default:
		break;
	}
	target.isLive = false;
	entityState = Entity::State::Idle;
	vs = VillagerState::Base;
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
		//TRACE("target %d %d\n", target.point.x, target.point.y);
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
		if (!Unit::Villager::Gathering()) {//若採集完尋找附近可採集點
			SetTargetByRange(target.point, VillagerState::Gathering);
		}
		//若滿了
		if (carryResource.amount>= carryLimit || target.isLive == false)
		{
			//就找地方放
			if (FindRecyclingPlace())//找到
			{


				//切換狀態至放資源的路上
				vs = VillagerState::ReturnResourceOnRoad;
				resourcePlace = target.point;
				SetTarget(recyclePlace->point);
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

	case VillagerState::GoAttackOnRoad:
		//TRACE("GoAttackOnRoad\n");
		if (navigatorState == 1)
		{
			vs = VillagerState::Attacking;
		}
		break;
		
	case VillagerState::Attacking:
		//TRACE("Attacking\n");
		Unit::Villager::Attacking();
		if (World::getInstance()->getEntityByID(ID) == NULL) { //  若打死人
			target.isLive = false;
		}
		break;

	case VillagerState::BuildingOnRoad:
		if (navigatorState == 1)
		{
			vs = VillagerState::Building;
		}
		break;

	case VillagerState::Building:
		if (!Building()) {
			vs = VillagerState::Base;
			entityState = Entity::State::Idle;
		}
		break;

	default:
		break;
	}
}


void Unit::Villager::onMove()
{
	Unit::Entity::onMove();
	if (hp <= 0)
		World::getInstance()->killByID(ID);
	HitBox = CRect(point.x, point.y, point.x + size.x, point.y + size.y);

	navigatorState = GetComponent<Navigator>()->onMove(&point);
	Entity* tempTarget = World::getInstance()->getEntityByID(target.ID);
	if (target.isLive && tempTarget != NULL)
		target.point = tempTarget->point;
	else
		target.isLive = false;
	this->FSM(navigatorState);
}

Unit::Villager::Villager(int pointX, int pointY) :Entity(pointX, pointY)
{
	AddComponent<Navigator>();
	AddComponent<Attack>(10,70);
	carryLimit = 10;
	maxHP = 100;
	resourceCounter = 0;
	entityType = EntityTypes::Villager;
	SetBitmap();
}

Unit::Villager::Villager(CPoint point) :Entity(point)
{
	AddComponent<Navigator>();
	AddComponent<Attack>(10, 70);
	carryLimit = 10;
	maxHP = 100;
	resourceCounter = 0;
	entityType = EntityTypes::Villager;
	SetBitmap();
}
Unit::Villager::Villager() :Entity(0, 0)
{
	AddComponent<Navigator>();
	AddComponent<Attack>(10, 70);
	carryLimit = 10;
	maxHP = 100;
	resourceCounter = 0;
	entityType = EntityTypes::Villager;
	SetBitmap();
}
Unit::Villager::~Villager()
{
	//TRACE("~Villager\n");
}
