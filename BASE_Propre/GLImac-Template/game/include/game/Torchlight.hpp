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
			void setNbBatteries(int v, char c);

            int getLifeTime();
            void setLifeTime(int v);
			void setLifeTime(int v,char c);

            int getFrames();
            void setFrames(int v);
			void setFrames(int v, char c);
						
	};
}
