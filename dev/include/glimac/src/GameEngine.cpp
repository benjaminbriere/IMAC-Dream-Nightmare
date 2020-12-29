#include "glimac/GameEngine.hpp"

using namespace std;
using namespace glimac;


GameEngine::GameEngine(const char* appPath)
{
  this->loading = false;
  FilePath tmp(appPath);
  this->applicationPath = tmp;
}

GameEngine::~GameEngine(){

}

bool GameEngine::initialisation(const char* vsFilename, const char* fsFilename){
  std::cout<<"*** Initialisation du moteur de jeu ***"<<endl;

  _Program = new gameShader();
  glimac::FilePath vsPath = applicationPath.dirPath()+"/shaders/"+vsFilename;
  glimac::FilePath fsPath = applicationPath.dirPath()+"/shaders/"+fsFilename;


  
	if (!_Program->init(&vsPath, &fsPath)) {
		std::cerr << "ERREUR : Initialisation gameShader" << std::endl;
		return false;
	}
  string configLevel = "listeLevel";
  if (!initialisationScenes(&configLevel)) {
		std::cerr << "ERREUR : Initialisation Scenes" << std::endl;
		return false;
	}

  std::cout<<"*** Fin initialisation du moteur de jeu ***"<<endl; 
  return false;
}


bool GameEngine::initialisationScenes(const string* filename)
{
	std::cout << std::endl <<"**********************************************************"<< std::endl 
	<< "Initialisation scenes" << std::endl;

  bool firstline = true;
  bool level_initialization = true; 
  int nbLevel;
  string line, firstword, word;

  string name_level, path_level;

  string path_conf = "assets/configurations/" + *filename + ".conf";
  ifstream file(path_conf);
  std::cout << "path : "<<path_conf << '\n';


  if(file) // si il trouve un fichier
  {
    std::cout << "                           " << endl
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
        while(iss >> word >> nbLevel)
        {
          std::cout << " Nombre de Levels       : "<<nbLevel<<endl << endl;
        }
        firstline = false;
        continue;
      }

      

      //LEVELS
      if(level_initialization) // normalement est tout le temps vrai tout comme models_initialization
      {
        for(int i = 0; i < nbLevel; i++)
        {

          bool firstlineLevel = true;
          bool models_initialization = true; 
          string lineLevel, firstwordLevel, wordLevel;
          int nbModel,nbLightAmbient,nbLightDirectional,nbLightPoint;
          string model_name,model_path;
          istringstream iss(line);
          while(iss >> name_level >> path_level)
          {
            std::cout << name_level << " " << path_level << endl ;
            ifstream fileLevel(path_level);
            if(fileLevel)
            {
              cout << "--- Fichier Level"<<i+1<<".conf trouvé "<<endl;
              while (getline( fileLevel, lineLevel ))
              {
                istringstream iss(lineLevel);
                iss >> firstwordLevel;

                //Si le premier mot est un # ceci est une ligne commentaire
                if(firstwordLevel.find("#") == string::npos)
                {
                  // si une ligne existe répondant à la consigne de ne pas être un commentaire existe
                  if(firstlineLevel)
                  {
                    istringstream iss(lineLevel);
                    //on sait que la première ligne qu'il va trouver dans le fichier config est le nombre de shader et model, on aurait juste pu écrire les nombres dans le fichier
                    //mais pour la compréhension on écrit à quoi cela correspond donc pour affecter les valeurs au variable on doit sauter un mot à chaque fois.
                    while(iss >> wordLevel >> nbModel >> wordLevel >> nbLightAmbient >> wordLevel >> nbLightDirectional >> wordLevel >> nbLightPoint)
                    {
                      std::cout << " Nombre de Models       : "<<nbModel<<endl
                      << " Nombre d'Ambient       : "<<nbLightAmbient<<endl
                      << " Nombre de Directional  : "<<nbLightDirectional<<endl
                      << " Nombre de Point        : "<<nbLightPoint<<endl
                      << endl;
                    }
                    firstlineLevel = false;
                    continue;
                  }
                  if(models_initialization)
                    {
                      for(int j = 0; j < nbModel; j++)
                      {
                        istringstream iss(lineLevel);
                        while(iss >> model_name >> model_path >> wordLevel >> wordLevel >> wordLevel >> wordLevel >> wordLevel >> wordLevel >> wordLevel >> wordLevel >> wordLevel >> wordLevel )
                        {
                          cout << "--- MODEL"<<j+1<<" : "<<model_path << endl;
                          Scene* tmp = new Scene(_Program);

                          if ( tmp->init(scenes[i].get("source", 0).asString().c_str()) ) {
                          _Scenes.push_back(tmp);
                          }
                          else {
                            std::cerr << "ERREUR: initialisation model " << scenes[i].get("source", 0) << " n'a pas pu être initialisée." << std::endl;
                            return false;
                          }
                        
                        }

                        getline(fileLevel, lineLevel);
                      }
                      cout << "" << endl;
                      models_initialization = false;
                      continue;
                    }
                }
              }  
              //this->shaders[name_shader] = Shader( (char*)pathShader_vs.c_str() , (char*)pathShader_fs.c_str() );
            }
            getline(file, line);
          }
          std::cout << "" << endl;
          level_initialization = false;
          continue;
        }
      } //Fin de la détection de lignes commentaires
    } //Fin de la lecture du fichier config
  }
  }


/*
		// A json file with the scenes is loaded
		std::ifstream sceneList(getScenesFilePath(filename), std::ios::in);

		if (!sceneList) {
			std::cerr << "ERROR: Impossible d'ouvrir le fichier contenant la liste des scènes " << getScenesFilePath(filename) << std::endl;
			return false;
		}
		std::cout << "Liste des scenes ouvert..." << std::endl;

		// Retrieve the root node
		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(sceneList, root, false)) {
      std::cerr  << "ERROR: Erreur lors de la récupération du json !" << std::endl;
			return false;
		}

		// retrieve the "scenes" node
		const Json::Value scenes = root["scenes"];
		if (scenes == 0) {
			std::cerr << "ERROR: Impossible de récupérer le noeud scenes !" << std::endl;
			return false;
		}

		// Initalize each scene
		for (int i = 0; i < scenes.size(); i++) {
			std::cout << std::endl << scenes[i].get("name", 0).asString() << " - initialisation..." << std::endl;

			Scene* tmp = new Scene(_Program);

			if ( tmp->init(scenes[i].get("source", 0).asString().c_str()) ) {
				_Scenes.push_back(tmp);
			}
			else {
				std::cerr << "ERROR: Scene " << scenes[i].get("source", 0) << " n'a pas pu être initialisée." << std::endl;
				return false;
			}
		}

		std::cout << "Fin initialisation scenes" << std::endl;
		std::cout << "**********************************************************"<< std::endl << std::endl;
		return true;
    */

   std::cout << "Fin Initialisation scenes" << std::endl;
   std::cout <<"**********************************************************"<< std::endl <<std::endl;
   return true; 

}



void GameEngine::run(SDLWindowManager* windowManager, GLuint width, GLuint height, bool* end)
{

    SDL_Event e;
    while(windowManager->pollEvent(e)) {
      if(e.type == SDL_QUIT) {
        (*end) = true;  //EXIT THE GAME AFTER THE LOOP
      }
      switch( e.type )
      {
        case SDL_KEYDOWN:
          if(windowManager->isKeyPressed(SDLK_ESCAPE))
          {
            (*end) = true;
          }
          /*
          if(windowManager->isKeyPressed(SDLK_s)) this->Camera.moveFront(-0.1);
          if(windowManager->isKeyPressed(SDLK_z)) this->Camera.moveFront(0.1);
          if(windowManager->isKeyPressed(SDLK_q)) this->Camera.moveLeft(0.1);
          if(windowManager->isKeyPressed(SDLK_d)) this->Camera.moveLeft(-0.1);
          */
        break;
      }
    }

    cout << "GAME ENGINE PATH : " << this->applicationPath << endl; 

    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->scenes[0].render(windowManager, width, height);

    // Update the display
    windowManager->swapBuffers();
}
