#pragma once

#include <Vector>

namespace composite
{
	class Component
	{
	private:
		std::vector<Component> _components;
	public:
		template<typename T> void add(T component);
		void remove();
		template<typename T> T getComponent();
	};
}