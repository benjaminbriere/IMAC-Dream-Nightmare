#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <glimac/Geometry.hpp>
#include <cstddef>
#include <vector>

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    glewExperimental = GL_TRUE;

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /**********************************/
    /********* INITIALISATION *********/
    /**********************************/

    Sphere MySphere(1, 32, 16);

    //Chargement des shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/3D.vs.glsl",
        applicationPath.dirPath() + "shaders/torchlight.fs.glsl"
    );
    program.use();

    //Obtention de l'id de la variable uniforme
    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    //Obtiention des variables uniformes pour la lumière
    GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
    GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
    GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
    GLint uLightPos_vs = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
    GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

    glEnable(GL_DEPTH_TEST); //permet d'activer le test de profondeur du GPU. Sans cet appel de fonction, certains triangles non visible viendraient recouvrir des triangles situés devant.

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.0f), 800.0f/600.0f, 0.1f, 100.0f); //param perspective(float fovy, float aspect, float znear, float far)
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    //Création d'un VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    //Bindind du vbo sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Puis on envois les données à la CG
    glBufferData(GL_ARRAY_BUFFER, MySphere.getVertexCount()*sizeof(ShapeVertex), MySphere.getDataPointer(), GL_STATIC_DRAW);

    //Débindind du vbo de la cible pour éviter de le remodifier
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Création du VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);

    //Binding du vao (un seul à la fois)
    glBindVertexArray(vao);

    //Dire à OpenGL qu'on utilise le VAO
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCOORDS = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

    //Indiquer à OpenGL où trouver les sommets
    //Bindind du vbo sur la cible
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Spécification du format de l'attribut de sommet position
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)offsetof(ShapeVertex, texCoords));
    //Débindind du vbo de la cible pour éviter de le remodifier
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Débindind du vao de la cible pour éviter de le remodifier
    glBindVertexArray(0);

    std::unique_ptr<Image> ptr_lune = loadImage("/home/benjamin/Documents/openGL/S3/projet/include/assets/MoonMap.jpg");
    if (ptr_lune == NULL)
    std::cout << "Lune non chargé" << '\n';
    else
    std::cout << "Lune chargé" << '\n';

    GLuint textureLune;
    glGenTextures(1, &textureLune);
    glBindTexture(GL_TEXTURE_2D, textureLune);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ptr_lune->getWidth(), ptr_lune->getHeight(), 0, GL_RGBA, GL_FLOAT, ptr_lune->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // appliquer un filtre linéaire
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);


    uint nbLune = 32;
    FreeFlyCamera Camera;

    std::vector<glm::vec3> AxesRotation;
    std::vector<glm::vec3> AxesTranslation;


    for (int i = 0; i < nbLune; ++i)
    {
        AxesRotation.push_back(glm::sphericalRand(1.0f)); //Rempli Axes rotation comme une pile ou comme un tableau, on pourra l'utiliser AxesRotation[i]
        AxesTranslation.push_back(glm::sphericalRand(2.0f));
    }


    /**********************************/
    /******* BOUCLE D'AFFICHAGE *******/
    /**********************************/




    // Application loop:
    bool done = false;
    while(!done) {

        glm::mat4 ViewMatrix = Camera.getViewMatrix();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        //Ici on récupère les positions de la souris
        glm::ivec2 mousePos = windowManager.getMousePosition();
        if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) Camera.moveFront(0.01);
        else if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) Camera.moveFront(-0.01);

        if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)){
        mousePos = windowManager.getMousePosition();
        float mousePosX = mousePos.x/800.0f - 0.5;
        float mousePosY = mousePos.y/600.0f - 0.5;

        float sensibility = 2;

        Camera.rotateLeft(-sensibility*mousePosX);
        Camera.rotateUp(-sensibility*mousePosY);

        }

        if(windowManager.isKeyPressed(SDLK_s)) Camera.moveFront(-0.1);
        if(windowManager.isKeyPressed(SDLK_z)) Camera.moveFront(0.1);
        if(windowManager.isKeyPressed(SDLK_q)) Camera.moveLeft(0.1);
        if(windowManager.isKeyPressed(SDLK_d)) Camera.moveLeft(-0.1);

        //Camera.rotateLeft( mousePos.y );
        //Camera.rotateUp( mousePos.x );

        // Nettoyage de la fenêtre
        glClearColor(0.0,0.0,0.0,0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);


        glm::mat4 Mrotate = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        glm::mat4 MVMatrix = ViewMatrix * glm::translate(glm::mat4(), glm::vec3(0, 0, -5));
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix)); //Model View Projection
        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        NormalMatrix = glm::transpose(glm::inverse(ViewMatrix));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureLune);



        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        glDrawArrays(GL_TRIANGLES, 0, MySphere.getVertexCount());

        for (int i = 0; i < AxesRotation.size(); ++i)
        {
            glm::mat4 newMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
            newMVMatrix = glm::rotate(newMVMatrix, windowManager.getTime(), AxesRotation[i]); // Translation * Rotation
            newMVMatrix = glm::translate(newMVMatrix, AxesTranslation[i]); // Translation * Rotation * Translation
            newMVMatrix = ViewMatrix * glm::scale(newMVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale

            glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * newMVMatrix));
            glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr( newMVMatrix));
            NormalMatrix = glm::transpose(glm::inverse(newMVMatrix));
            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

            glDrawArrays(GL_TRIANGLES, 0, MySphere.getVertexCount());
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0



        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
