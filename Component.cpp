#include "stdafx.h"
#include <Vector>
#include <typeinfo>
#include "Component.h"

namespace composite
{


	std::vector<Component> _components;

	//預計遞迴刪除
	

	Component::Component()
	{

	}
	Component::~Component()
	{

	}

	template<typename T> void Component::add(T component)
	{
		component = new component;
		_components.push_back(component);
	}
	template<typename T>void Component::remove(T component)
	{

	}
	template<typename T> T Component::getComponent()
	{
		for (int i = 0; i < _components.size(); i++)
			if (typeid(_components.at(i)).name() == T)//不確定
				return _components.at(i);
		return NULL;
	}

}