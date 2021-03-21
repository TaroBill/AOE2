#pragma once
namespace Utility
{
	namespace PathFinding
	{
		class Astar
		{
			//³æ¨Ò
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