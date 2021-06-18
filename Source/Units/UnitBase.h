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

		//取得組件
		//GetComponent<組件型別>()
		template<typename T>
		T* GetComponent()
		{

			for (unsigned int i = 0; i < _components.size(); i++)
				if (dynamic_cast<T*>(_components.at(i)))
					return dynamic_cast<T*>(_components.at(i));
			return nullptr;
			
		}
		template<typename T>
		bool ContainComponent()
		{
			for (unsigned int i = 0; i < _components.size(); i++)
				return (dynamic_cast<T*>(_components.at(i)) != nullptr);
			return false;

		}
		template<typename T>
		bool IsComponent()
		{
			return (dynamic_cast<T*>(this) != nullptr);
		}
		//新增組件時，請使用new
		//AddComponent(new 組件型別())
		virtual void AddComponent(UnitBase* component)
		{
			_components.push_back(component);
			component->SetParent(this);
		}

		template<typename T>
		void AddComponent()
		{
			T* n = new T();
			_components.push_back(n);
			n->SetParent(this);
		}
		
		template<typename T,typename ... A>
		void AddComponent(A ... rest)
		{
			T* n = new T(rest ...);
			_components.push_back(n);
			n->SetParent(this);
		}
		//刪除指定的同型別組件
		//RemoveComponent<組件型別>()
		template<typename T>
		bool RemoveComponent()
		{
			for (unsigned int i = 0; i < _components.size(); i++)
				if (dynamic_cast<T*>(_components.at(i)))
				{
					//做錯了，應該用erase直接刪除
					_components.pop_back();
					return true;
				}
			return false;
		}

		void RemoveComponents(vector<UnitBase*> components)
		{
			for (unsigned int i = 0; i < components.size(); i++)
			{
				if (components.at(i)->_components.size() > 0)
				{
					RemoveComponents(components.at(i)->_components);
				}
				delete components.at(i);
			}
			components.clear();
		}
		void RemoveComponents()
		{

		}
		template<typename T>
		T* GetParent()
		{
			return dynamic_cast<T*>(_parent);
		}

		UnitBase()
		{
		}
		
		virtual ~UnitBase()
		{
			RemoveComponents(_components);
			//TRACE("~UnitBase\n");
		}

		
	};
}