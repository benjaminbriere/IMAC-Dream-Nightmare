#pragma once
#include <glimac/SDLWindowManager.hpp>
#include "glimac/glm.hpp"
//#include "Model.hpp"
#include "glimac/Shader.hpp"
#include "glimac/FreeFlyCamera.hpp"
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <GL/glew.h>

using namespace std;
using namespace glimac;
//using namespace game;

class GameScene
{
    public:
      GameScene(string path_season);
      void loadScene(string path_season);
      void render(SDLWindowManager* windowManager, float width, float height);
    private:

      map<string, Shader> shaders;
      //map<string, Model> models;
};
