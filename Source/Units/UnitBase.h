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

		//���o�ե�
		//GetComponent<�ե󫬧O>()
		template<typename T>
		T* GetComponent()
		{

			for (unsigned int i = 0; i < _components.size(); i++)
				if (dynamic_cast<T*>(_components.at(i)))
					return dynamic_cast<T*>(_components.at(i));
			return nullptr;
			
		}
		

		//�s�W�ե�ɡA�Шϥ�new
		//AddComponent(new �ե󫬧O())
		virtual void AddComponent(UnitBase* component)
		{
			_components.push_back(component);
			component->SetParent(this);
		}

		//�R�����w���P���O�ե�
		//RemoveComponent<�ե󫬧O>()
		template<typename T>
		bool RemoveComponent()
		{
			for (unsigned int i = 0; i < _components.size(); i++)
				if (dynamic_cast<T*>(_components.at(i)))
				{
					//�����F�A���ӥ�erase�����R��
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
			RemoveComponents(_components);
			
		}
		
	};
}