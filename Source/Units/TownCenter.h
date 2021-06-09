#pragma once
#include "Entity.h"
#include "UnitBase.h"

namespace Unit
{
	class TownCenter :public Entity
	{
	public:
		void Serialize(stringstream& in)
		{
			in << "Type " << this->entityType << " ";
			in << "HP " << this->hp << " ";
			in << "ID " << this->ID << " ";
			in << "playerID " << (1 - this->playerId) << " ";
			in << "End ";

		}

		void deSerialize(stringstream& in)
		{
			string erase;
			in >> erase >> this->hp;
			in >> erase >> this->ID;
			in >> erase >> this->playerId;
			in >> erase;
		}
		void SetBitmap();
		void onMove();
		TownCenter(int pointX, int pointY);
		TownCenter(CPoint point);
		TownCenter();
		~TownCenter();
	};
}