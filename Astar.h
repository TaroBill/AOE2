#pragma once
namespace Utility
{
	namespace PathFinding
	{
		class Astar
		{
			//���
		private:
			static Astar _instance;
			Astar()
			{

			}
		public:
			Astar getInstance()
			{
				if ((&_instance) == nullptr)_instance = Astar();
				return _instance;
			}
		};
	}
}