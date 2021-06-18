#pragma once
#include "./Entity.h"
#include <sstream>
#include "Gatherable.h"

#include "../Player/GameResource.h"
namespace Unit
{
	class Tree : public Entity
	{
	public:
		void Serialize(stringstream& in)
		{
			in << "Type " << this->entityType << " ";
			in << "ID " << this->ID << " ";
			in << "playerID " << this->playerId << " ";
			in << "remainAmount " << remainAmount << " ";
			in << "End ";
		}

		void deSerialize(stringstream& in)
		{
			string erase;	//erase¥Î¨Ó¦Y±¼" "
			in >> erase >> this->ID;
			in >> erase >> this->playerId;
			in >> erase >> this->GetComponent<Gatherable>()->resource.amount;
			in >> erase;
		}

		int remainAmount;

		Tree(CPoint, ResourceType);

		Tree(int, int, ResourceType);

		void SetBitmap()override;

		void SetTarget(CPoint, vector<Entity*>) override;

		void onShow(int screenX,int screenY) override;

		void onMove()override;

		~Tree();
	};
}