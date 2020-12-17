#include "glimac/GameEngine.hpp"

using namespace std;
using namespace glimac;


GameEngine::GameEngine()
{
  this->loading = false;
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
          if(windowManager->isKeyPressed(SDLK_s)) this->Camera.moveFront(-0.1);
          if(windowManager->isKeyPressed(SDLK_z)) this->Camera.moveFront(0.1);
          if(windowManager->isKeyPressed(SDLK_q)) this->Camera.moveLeft(0.1);
          if(windowManager->isKeyPressed(SDLK_d)) this->Camera.moveLeft(-0.1);
        break;
      }
    }

    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->scenes[0].render(windowManager, width, height);

    // Update the display
    windowManager->swapBuffers();
}
