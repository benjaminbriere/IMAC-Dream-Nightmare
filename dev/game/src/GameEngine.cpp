#include "game/GameEngine.hpp"

namespace game
{
	GameEngine::GameEngine(const char* appPath)
	{
		_SceneId = -1; //le niveau à afficher, le -1 correspond à l'écran noir du temps de chargement 
		_NbStatue = 0;

		_Torchlight = new Torchlight();
		setLampON(_Torchlight->getLifeTime()); // allumage de la lampe torche qui doit interrargir avec le shader

		initApplicationPath(appPath); //Récupération du chemin relatif utile pour le chargement des shaders, scenes, models, textures
		std::cout << "App run on " << gApplicationPath->dirPath() << std::endl;
	}

	GameEngine::~GameEngine()
	{

	}

	bool GameEngine::init(const char* vsFilename, const char* fsFilename)
	{
		try
		{
			//Initialisation d'OpenGL et SDL
			if (!initSdlOpenGl()) {
				throw std::string("Initialisation SDL & OpenGL");
			}
			else{
				//Initialisation des Shaders
				_Program = new ShaderProgram();
				if (!_Program->init(vsFilename, fsFilename)) {
					throw std::string("Initialisation SHADERS");
				}
				else{
					//Initialisation des Scènes
					if (!initScenes("scenes/levelList.json")) {
						throw std::string("Initialisation SCENES");
					}
					else{
						_SceneId = 0; //si les scènes ont correctement été initialisées on passe au niveau 1
						return true;
					}
				}		
			}
		}
		catch(const std::string &err){
			std::cerr << "ERREUR : "<<err<<std::endl;
			return false;
		}
	}

	bool GameEngine::initSdlOpenGl()
	{
		SDL_Init(SDL_INIT_VIDEO);

		glimac::SDLWindowManager* windowManager = new glimac::SDLWindowManager(800, 600, "Imac-Nightmare-Dream");

		if (!windowManager) {
			return false;
		}

		_WindowManager = windowManager;

		GLenum glewInitError = glewInit();

		if (GLEW_OK != glewInitError) {
			std::cerr << glewGetErrorString(glewInitError) << std::endl;
			return false;
		}

		std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl << std::endl;

		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
  		{
    	  printf("%s", Mix_GetError());
   		}	
		Mix_AllocateChannels(32);
 	    Mix_Music *musique; //Création du pointeur de type Mix_Music
		musique = Mix_LoadMUS("src/../assets/Musique_jeu.mp3"); //Chargement de la musique
 		Mix_PlayMusic(musique, -1); //Jouer infiniment la musique

		SDL_ShowCursor(SDL_DISABLE);


		return true;
	}

	bool GameEngine::initScenes(const char* filename)
	{

		// Récupération du json contenant les scènes 
		std::ifstream sceneList(getScenesFilePath(filename), std::ios::in);

		if (!sceneList) {
			std::cerr << "ERREUR = ouverture du fichier json scènes" << getScenesFilePath(filename) << std::endl;
			return false;
		}

		Json::Value root;
		Json::Reader reader;

		if (!reader.parse(sceneList, root, false)) {
      		std::cerr  << "ERREUR = Lecture Json " << std::endl;
			return false;
		}

		// Se positionne sur le noeud scenes
		const Json::Value scenes = root["scenes"];
		if (scenes == 0) {
			std::cerr << "ERREUR = Noeud 'scenes' introuvable" << std::endl;
			return false;
		}

		// Pour chacune des scènes on va récupérer son nom et son path et les initialiser
		for (int i = 0; i < scenes.size(); i++) {
			
			std::cout<<"LECTURE SCENE : "<<i+1<<std::endl;

			Scene* tmpScene = new Scene(_Program);

			//initialisation de la scène et ajout de cette denriere dans le vecteur de scènes du moteur
			if ( tmpScene->init(scenes[i].get("source", 0).asString().c_str()) ) {
				_Scenes.push_back(tmpScene);
			}
			else {
				std::cerr << "ERREUR: Scene n°" << scenes[i].get("source", 0) << " non initialisée" << std::endl;
				return false;
			}
		}

		return true;
	}

	void GameEngine::run()
	{
		//tant que done == false, boucle de rendu
		bool done = false;
		Uint32 currentTime = SDL_GetTicks();

		Mix_Chunk *interrupteur;
		interrupteur = Mix_LoadWAV("src/../assets/switch.wav");
		SDL_Event event;

		while(!done) {
			Uint32 deltaTime = SDL_GetTicks() - currentTime;
			//std::cout << "delta time " << deltaTime <<std::endl;
			Uint32 currentTime = SDL_GetTicks();
			if(deltaTime < 1000/60){
				SDL_Delay(1000/60 - deltaTime);
			}
			
			if(getLampON()!=0){
				updateTorchlight();
			}          

			//sleep( (10000/60 - deltaTime );

			renderScene();
			checkVictory();

			if (userEvents()) {
				done = true;
			}
		}		
		Mix_FreeChunk(interrupteur);
		Mix_CloseAudio();
	}

	void GameEngine::checkVictory(){

		if(_NbStatue == 4) // le joueur a récupéré toute les statues
		{
			std::cout << "c'est GAGNE " << std::endl;
			_SceneId = 1;
		}
		else if( (_Torchlight->getNbBatteries()==0) && (_Torchlight->getLifeTime()==0) ){
			std::cout << "c'est PERDU " << std::endl;
			std::cout<<"--> Etat de la pile : "<<_Torchlight->getLifeTime()<<std::endl;
			std::cout << "|||||||||||||||||||+  : " << _Torchlight->getNbBatteries() <<std::endl;
			_SceneId = 2;
		}

	}


	void GameEngine::updateTorchlight(){
		if(_Torchlight->getFrames()<=60){
			_Torchlight->setFrames(1);
		}
		else{
			_Torchlight->setFrames(0,'a');
			if(_Torchlight->getLifeTime()>0){
				std::cout << "|||||||||||||||||||+  : " << _Torchlight->getNbBatteries() <<std::endl;
				std::cout<<"--> Etat de la pile : "<<_Torchlight->getLifeTime()<<std::endl;
				_Torchlight->setLifeTime(-4);
			}
			else{
				std::cout<<"--> Une pile consommée "<<std::endl;
				_Torchlight->setNbBatteries(-1);
				if(_Torchlight->getNbBatteries()!=0){
					_Torchlight->setLifeTime(100,'a');
				}
				
			}
		}

			
		/*
		std::cout<<"Gestion lampe torche : "<<std::endl
			<<"--> Nombre de piles : "<<_Torchlight->getNbBatteries()<<std::endl
			<<"--> Etat de la pile : "<<_Torchlight->getLifeTime()<<std::endl
			<<"--> Nombre de frame : "<<_Torchlight->getFrames()<<std::endl;
			*/

	}

	void GameEngine::renderScene()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		getBattery();

		_Scenes[_SceneId]->render(getLampON(),_SceneId); //passage de valeur de getLampON en parametre pour modifier le shader [ne fonctionne pas encore]
		_WindowManager->swapBuffers();
	}

	void GameEngine::getBattery(){
		glm::vec3 CameraPosition = _Scenes[_SceneId]->_Camera.getPosition();
		//std::cout << "Position de la camera : " << CameraPosition << std::endl;
		
		for (auto mesh = _Scenes[_SceneId]->_Meshes.begin(); mesh != _Scenes[_SceneId]->_Meshes.end(); ++mesh) {
			glm::vec3 meshPosition = (*mesh)->getPosition();
			//std::cout << "Position des models  : " << (*mesh)->getPosition() << std::endl; 
			if((*mesh)->getVisible() == 1){
				if( std::abs(CameraPosition.x-meshPosition.x)<0.3 && std::abs(CameraPosition.z-meshPosition.z)<0.3){
					//std::cout << "----- Proche " <<std::endl;
					(*mesh)->setVisible(0.0);
					_Torchlight->setNbBatteries(1);
				}
			}
			if((*mesh)->getVisible() == 2.0){
				if( std::abs(CameraPosition.x-meshPosition.x)<0.1 && std::abs(CameraPosition.z-meshPosition.z)<0.1){
					//std::cout << "----- Proche " <<std::endl;
					(*mesh)->setVisible(0.0);
					_NbStatue++;
				}
			}
		}
	}

	bool GameEngine::userEvents() {
		SDL_Event e;
		bool quit = false;
		Mix_Chunk *interrupteur;
		interrupteur = Mix_LoadWAV("src/../assets/switch.wav");
		while(_WindowManager->pollEvent(e)) {
			if (e.type == SDL_MOUSEMOTION)
			{
			  mouseEvents(e);
			}

			if(e.type == SDL_MOUSEBUTTONUP){
				if(e.button.button == SDL_BUTTON_RIGHT){
					//std::cout<<"valeur de LampON : "<< getLampON() <<std::endl;
					if(getLampON() != 0){
						//std::cout<<" valeur de la lampe = 1"<<std::endl;
						setLampON(0);
						//std::cout<<" valeur de la lampe = "<< getLampON()<<std::endl;
					}else{
						setLampON(_Torchlight->getLifeTime());
						//std::cout<<" valeur de la lampe = "<<getLampON()<<std::endl;
					}
					Mix_PlayChannel(1, interrupteur, 0);
				}
			}

			if (e.type == SDL_KEYUP) {
				switch (e.key.keysym.sym) {
					case SDLK_LEFT:
						std::cout<<"Numéro de la scène : "<<_SceneId<<std::endl;
						if(_SceneId>0){
							_SceneId--;
						}
						break;
					case SDLK_RIGHT:
						std::cout<<"Numéro de la scène : "<<_SceneId<<std::endl;
						if(_SceneId<2){
							_SceneId++;
						}
						break;
					}
			}

			if(e.type == SDL_QUIT) {
				std::cout << std::endl << "Fermeture d'application reçue..." << std::endl;
				quit = true;
			}
		}

		if(_WindowManager->isKeyPressed(SDLK_s)){
			_Scenes[_SceneId]->_Camera.moveFront(-0.1);
			_Scenes[_SceneId]->_Camera.setPositionY(0.0);
		} 
        if(_WindowManager->isKeyPressed(SDLK_z)){
			_Scenes[_SceneId]->_Camera.moveFront(0.1);
			_Scenes[_SceneId]->_Camera.setPositionY(0.0);
		} 
        if(_WindowManager->isKeyPressed(SDLK_q)){
			_Scenes[_SceneId]->_Camera.moveLeft(0.1);
			_Scenes[_SceneId]->_Camera.setPositionY(0.0);
		} 
        if(_WindowManager->isKeyPressed(SDLK_d)){
			_Scenes[_SceneId]->_Camera.moveLeft(-0.1);
			_Scenes[_SceneId]->_Camera.setPositionY(0.0);
		}

		return quit;
	}


	void GameEngine::mouseEvents(SDL_Event e)
	{
		if (e.motion.state & SDL_BUTTON_LMASK)
		{
				_Scenes[_SceneId]->_Camera.rotateLeft((float)e.motion.xrel);
				_Scenes[_SceneId]->_Camera.rotateUp((float)e.motion.yrel);
		}
		else if (e.motion.state & SDL_BUTTON_RMASK)
		{
			
		}
	}

	void GameEngine::setLampON(int v){
		_lampON = v;
	}	

	int GameEngine::getLampON(){
		return _lampON;
	}
}


