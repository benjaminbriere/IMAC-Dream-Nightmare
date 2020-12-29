#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include "glimac/Shader.hpp"
#include "glimac/FilePath.hpp"
//#include "glimac/FreeFlyCamera.hpp"
#include "glimac/Program.hpp"

#include "glimac/GameScene.hpp"
#include "glimac/GameShader.hpp"


using namespace std;
using namespace glimac;
//using namespace game;

class GameEngine
{
    public:

      bool loading;
      vector<GameScene> scenes; // on admet qu'on aura plusieurs niveaux chaque niveaux seront stockées dans des scenes
      //FreeFlyCamera Camera;
      FilePath applicationPath;

      GameEngine(const char* appPath);
      ~GameEngine();
      bool initialisation(const char* vsFilename, const char* fsFilename);
      bool initialisationScenes(const string* filename);
      void run(SDLWindowManager* windowManager, GLuint width, GLuint height, bool* end);

    private:
      glimac::gameShader* _Program;

};
