#pragma once

#include <Vector>

namespace composite
{
	class Component
	{
	private:
		std::vector<Component> _components;
		//預計用來遞迴刪除底下組件
		void Component::recursiveRemove(Component* c);
	public:
		Component();
		~Component();
		template<typename T> void add(T component);
		//指定刪除某個組件
		template<typename T> void remove(T component);
		//不指定就是刪除自己
		void remove();
		template<typename T> T getComponent();
	};
}