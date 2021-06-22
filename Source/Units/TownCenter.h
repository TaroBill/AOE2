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
			in << "spawnCount " << this->spawnCount << " ";
			in << "playerID " << (1 - this->playerId) << " ";
			in << "End ";

		}

		void deSerialize(stringstream& in)
		{
			string erase;
			in >> erase >> this->hp;
			in >> erase >> this->ID;
			in >> erase >> this->spawnCount;
			in >> erase >> this->playerId;
			in >> erase;
		}
		void SetBitmap();
		void onMove();
		void doneBuilding();
		bool isDoneBuilding;
		int spawnCount = 0;
		TownCenter(int pointX, int pointY, int Hp = 1);
		TownCenter(CPoint point, int Hp = 1);
		TownCenter();
		~TownCenter();
	};
}