#pragma once
#include <Vector>
#include <typeinfo>
namespace GameObject
{
	
	class Component
	{
	public:
		std::vector<void*> _components;
		//�z�L��ҷs�W�ե�
		virtual void add(Component* c)
		{
			(_components).push_back(c);
		}


		
		
		//�z�L���O�s�W�ե�
		template<typename T>
		void add()
		{
			T* temp = new T();
			(_components).push_back(temp);
		}

		template<typename T>
		auto getComponent()
		{
			T t;
			for (auto& item : _components)
			{

				if (typeid(item).name() == typeid(t).name())
				{
					return item;
				}
			}
			//void* a;
			return _components.at(0);
		}

		Component getComponent(int i)
		{

			void* v = _components.at(i);
			static Component* c = (Component*)v;
			return *c;
		}
		

		//�z�L���O���o�ե�
		
		template<typename T>
		T getComponent()
		{
			
			T temp;

			static T* t;

			const char* a = typeid(temp).name();
			for (int i = 0; i < _components.size(); i++)
			{
				const char* b = typeid(_components.at(i)).name();
				if (a == b)
				{
					t = (T*)_components.at(i);
					return *t;
				}
			}

			return *t;
		}
		
		

		Component()
		{
		}
		virtual ~Component()
		{
		}

	};
}
