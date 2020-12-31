#include <iostream>
#include <cstdlib>

#include <game/GameEngine.hpp>

int main(int argc, char** argv) {

    //Création du moteur du jeu en passant le path de l'exécutable en paramètre
    game::GameEngine* engine = new game::GameEngine(argv[0]);
    
    //initialisation du moteur et initialisation dans l'ordre de sdl, les shaders et les scènes
    if (!engine->init("shader.vs.glsl", "shader.fs.glsl")) {
        return EXIT_FAILURE;
    }

    //execution du moteur
    engine->run();

    delete(engine);

    return EXIT_SUCCESS;
}
