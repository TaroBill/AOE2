#pragma once

#include "Component.h"

namespace composite
{
	class Collectable :Component
	{
	private:
		int resource;
		int gatherRate;
	public:
		Collectable();
		int getResource();
		void reduceResource();
	};
}