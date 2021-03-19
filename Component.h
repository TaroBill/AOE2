#pragma once

#include <Vector>

namespace composite
{
	class Component
	{
	private:
		std::vector<Component> _components;
		//�w�p�Ψӻ��j�R�����U�ե�
		void Component::recursiveRemove(Component* c);
	public:
		Component();
		~Component();
		template<typename T> void add(T component);
		//���w�R���Y�Ӳե�
		template<typename T> void remove(T component);
		//�����w�N�O�R���ۤv
		void remove();
		template<typename T> T getComponent();
	};
}