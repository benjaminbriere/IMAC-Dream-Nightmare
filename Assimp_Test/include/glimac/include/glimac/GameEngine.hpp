#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <GL/glew.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include "Shader.hpp"
#include "GameScene.hpp"
#include "FreeFlyCamera.hpp"

using namespace std;
using namespace glimac;

class GameEngine
{
    public:

      bool loading;
      vector<GameScene> scenes; // on admet qu'on aura plusieurs niveaux chaque niveaux seront stockées dans des scenes
      FreeFlyCamera Camera;

      GameEngine();
      void run(SDLWindowManager* windowManager, GLuint width, GLuint height, bool* end);

    private:

};
