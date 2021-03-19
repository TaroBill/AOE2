#pragma once

#include "Component.h"

namespace composite
{
	class Collectable :Component
	{
	private:
		int resource;
		int gatherRate;
		void reduceResource();
	public:
		Collectable();
		int getResource();
	};
}