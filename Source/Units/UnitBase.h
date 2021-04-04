#pragma once

#include "../stdafx.h"
#include "../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../audio.h"
#include "../gamelib.h"
#include <vector>

/*
*/
using namespace game_framework;
namespace Unit9
{
	class UnitBase
	{
		vector<UnitBase*> _components;
	public:

		template<typename T>
		T* GetComponent()
		{
			for (unsigned int i = 0; i < _components.size(); i++)
				if (dynamic_cast<T*>(_components.at(i)))
					return dynamic_cast<T*>(_components.at(i));
			return nullptr;
		}

		void AddComponent(UnitBase* component)
		{
			_components.push_back(component);
		}

		template<typename T>
		bool RemoveComponent()
		{
			for (unsigned int i = 0; i < _components.size(); i++)
				if (dynamic_cast<T*>(_components.at(i)))
				{
					_components.pop_back();
					return true;
				}
			return false;
		}

		UnitBase()
		{

		}

		~UnitBase()
		{

		}
	};
}