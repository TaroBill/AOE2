#include "Attack.h"
#include "Entity.h"
#include "Navigator.h"
#include "../World.h"

Unit::Attack::Attack() {
	Range = 20;
	Damage = 10;
}

Unit::Attack::~Attack() {

}

Unit::Attack::Attack(int damage, int range) {
	Range = range;
	Damage = damage;
}

bool Unit::Attack::doAttack() {
	Entity* target = World::getInstance()->getEntityByID(this->GetParent<Unit::Entity>()->target.ID);
	if (target == NULL)
		return false;
	if (calculateLength(this->GetParent<Unit::Entity>()->point, target->point) < Range) {
		target->hp -= Damage;
		if (target->hp <= 0) {
			this->GetParent<Unit::Entity>()->target.isLive = false;
			World::getInstance()->killByID(target->ID);
			return false;
		}
		return true;
	}
	return false;
}


double Unit::Attack::calculateLength(CPoint p1, CPoint p2) {
	CPoint vector = p1 - p2;
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}