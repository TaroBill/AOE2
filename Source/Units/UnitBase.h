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
namespace Unit
{
	class UnitBase
	{
		vector<UnitBase*> _components;
		UnitBase* _parent;
	protected:
		void SetParent(UnitBase* parent)
		{
			this->_parent = parent;
		}
	public:

		template<typename T>
		T* GetComponent()
		{
			for (unsigned int i = 0; i < _components.size(); i++)
				if (dynamic_cast<T*>(_components.at(i)))
					return dynamic_cast<T*>(_components.at(i));
			return nullptr;
		}



		virtual void AddComponent(UnitBase* component)
		{
			_components.push_back(component);
			component->SetParent(this);
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

		template<typename T>
		T* GetParent()
		{
			return dynamic_cast<T*>(_parent);
		}
		UnitBase()
		{
		}

		~UnitBase()
		{

		}
	};
}