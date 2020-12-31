#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace game
{
	class Torchlight
	{
		private:
			int _lifeTime;
            int _nbBatteries; 
			int _frames;

		public:
			Torchlight();
			~Torchlight();

			int getNbBatteries();		
			void setNbBatteries(int v);

            int getLifeTime();
            void setLifeTime(int v);

            int getFrames();
            void setFrames(int v);
						
	};
}
