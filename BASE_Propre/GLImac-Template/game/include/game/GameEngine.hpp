#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <json/json.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>

#include "utils.hpp"
#include "Shader.hpp"
#include "Scene.hpp"
#include "Torchlight.hpp"


namespace game
{

	class GameEngine
	{
	public:
		GameEngine(const char* appPath);
		~GameEngine();

		bool init(const char* vsFilename, const char* fsFilename);	
		void run();									

	private:
		bool initSdlOpenGl();					
		bool initScenes(const char* filename);

		// test récupération des piles
		void getBattery();	

		void renderScene();						
		bool userEvents();
		void checkVictory();														
		void mouseEvents(SDL_Event e);
		void setLampON(int v);
		void updateTorchlight();

		int getLampON();										

		glimac::SDLWindowManager* _WindowManager;
		ShaderProgram* _Program;
		ShaderProgram* _HUD;
		std::vector<Scene*> _Scenes;
		Torchlight* _Torchlight;

		int _SceneId;
		int _lampON;
		int _NbStatue;
		int _TorchLightWorks;
		//Mix_Chunk * _interrupteur;

		
	};
}
