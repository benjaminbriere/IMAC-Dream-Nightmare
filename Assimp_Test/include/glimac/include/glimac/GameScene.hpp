#pragma once
#include <glimac/SDLWindowManager.hpp>
#include "glimac/glm.hpp"
//#include "Model.hpp"
#include "Shader.hpp"
#include "FreeFlyCamera.hpp"
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <GL/glew.h>

using namespace std;
using namespace glimac;


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
