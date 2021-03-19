#include "stdafx.h"
#include "Collectable.h"

namespace composite
{
	Collectable::Collectable()
	{
		int resource = 100;
		int gatherRate = 25;
	};
	int Collectable::getResource()
	{
		
		return gatherRate;
	}
	int Collectable::reduceResource()
	{

	}
}