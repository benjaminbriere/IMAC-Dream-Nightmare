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

  if(file) // si il trouve un fichier
    {
      cout << "                           " << endl
      << "Config file informations : " << endl
      << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ " << endl;

      //Lecture de toutes les lignes du fichier file
      while (getline( file, line ))
      {

        istringstream iss(line);
        iss >> firstword;

        //Si le premier mot est un # ceci est une ligne commentaire
        if(firstword.find("#") == string::npos){

          // si une ligne existe répondant à la consigne de ne pas être un commentaire existe
          if(firstline)
          {
            istringstream iss(line);
            //on sait que la première ligne qu'il va trouver dans le fichier config est le nombre de shader et model, on aurait juste pu écrire les nombres dans le fichier
            //mais pour la compréhension on écrit à quoi cela correspond donc pour affecter les valeurs au variable on doit sauter un mot à chaque fois.
            while(iss >> word >> nbShader >> word >> nbModel)
            {
              cout << " Nombre de Shaders       : "<<nbShader<<endl<< " Nombre de Modeles        : "<<nbModel<<endl<< endl;
            }
            firstline = false;
            continue;
          }

          //SHADERS
          if(shaders_initialization) // normalement est tout le temps vrai tout comme models_initialization
          {
            for(int i = 0; i < nbShader; i++)
            {
              istringstream iss(line);
              while(iss >> name_shader >> pathShader_vs >> pathShader_fs)
              {
                cout << name_shader << " " << pathShader_vs << " " << pathShader_fs << endl ;
                //this->shaders[name_shader] = Shader( (char*)pathShader_vs.c_str() , (char*)pathShader_fs.c_str() );
              }
              getline(file, line);
            }
            cout << "" << endl;
            shaders_initialization = false;
            continue;
          }

          //MODELS
          if(models_initialization)
          {
            for(int i = 0; i < nbModel; i++)
            {
              istringstream iss(line);
              while(iss >> name_model >> path_model >> model_shader_name >> rotate_angle >> rotate_x >> rotate_y >> rotate_z >> translate_x >> translate_y >> translate_z >> scale)
              {
                cout << name_model << " " << path_model << " " << model_shader_name << endl;
                //this->models[name_model] = Model( (char*)path_model.c_str(), (char*)model_shader_name.c_str(), rotate_angle, rotate_x, rotate_y, rotate_z, translate_x, translate_y, translate_z, scale);
              }

              getline(file, line);
            }
            cout << "" << endl;
            models_initialization = false;
            continue;
          }

        } //Fin de la détection de lignes commentaires
      } //Fin de la lecture du fichier config

    }



}

void GameScene::render(SDLWindowManager* windowManager, float width, float height){
  std::cout << "render" << '\n';
  loadScene("level1");
}
