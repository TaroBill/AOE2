#pragma once
#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include "../Units/Entity.h"
#include "./Gatherable.h"
namespace Unit
{
	class Stone :public Entity
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

		Stone(CPoint, ResourceType);

		Stone(int, int, ResourceType );

		void SetBitmap()override;

		void SetTarget(CPoint, vector<Entity*>) override;

		void onMove()override;

		 ~Stone() ;
	};
}