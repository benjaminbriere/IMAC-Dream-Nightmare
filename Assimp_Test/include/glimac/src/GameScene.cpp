#include "glimac/GameScene.hpp"

using namespace std;
using namespace glimac;

GameScene::GameScene(string path_scene)
{
  this->loadScene(path_scene);
}


void GameScene::loadScene(string path_scene)
{
  std::cout << "et c'est le loadScene : "<<path_scene << '\n';
  bool  firstline = true,
  shaders_initialization = true,
  models_initialization = true;

  int nbShader, nbModel;
  string line, firstword, word;

  string name_shader, pathShader_vs, pathShader_fs;

  //Valeurs du txt pour les models
  string name_model, path_model, model_shader_name;
  float rotate_angle, rotate_x, rotate_y, rotate_z,
  translate_x, translate_y, translate_z,
  scale;

  string path_conf = "assets/configurations/" + path_scene + ".conf";
  ifstream file(path_conf);
  std::cout << "path : "<<path_conf << '\n';

  if(file)
    {
      cout << "                           " << endl
      << "Config file informations : " << endl
      << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ " << endl;
    }

}

void GameScene::render(SDLWindowManager* windowManager, float width, float height){
  std::cout << "render" << '\n';
  loadScene("level1");
}
