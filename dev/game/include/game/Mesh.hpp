#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>

#include <glimac/glm.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "utils.hpp"
#include "Vertex.hpp"

namespace game
{
  /**
   * Class Mesh
   **/
  class Mesh
  {
  public:
    Mesh();
    ~Mesh();
    
    bool loadMesh(const char* filename);  // Load 3D objet
    void render();                        // Render all the meshs

    float getShininess();
    glm::vec3 getDiffuse();
    glm::vec3 getSpecular();

    void setPosition(glm::vec3 position);
    void setAngle(float angle);
    void setRotAxe(glm::vec3 axis);
    void setScale(glm::vec3 scale);
    void setVisible(float v);

    glm::vec3 getPosition();
    float getAngle();
    glm::vec3 getRotAxe();
    glm::vec3 getScale();
    float getVisible();

  private:
    bool init(const aiScene* scene, const char* filename);          // Initialize Mesh object
    void initMeshEntry(unsigned int id, const aiMesh* meshEntry);   // Initialize all meshes
    bool initMaterials(const aiScene* scene);                       // Initialize all textures

    #define INVALID_MATERIAL 0xFFFFFFFF

    // Each mesh in the loaded file is a struct
    struct MeshEntry {
      MeshEntry();
      ~MeshEntry();

      // Initialize the mesh struct
      void init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

      GLuint vb;                    // vbo
      GLuint ib;                    // ibo
      unsigned int numIndices;      // Number of indices in the mesh
      unsigned int materialIndex;   // Id of the texture linked to the mesh
    };

    std::vector<MeshEntry> _entries;  // All the meshes
    std::vector<GLuint> _textures;    // All the textures

    glm::vec3 _position;              // Position in scene
    float _angle;                      // Rotation in scene
    glm::vec3 _rotAxe;
    glm::vec3 _scale;                 // Scale in scene

    float _shininess;
    glm::vec3 _diffuseCoef;
    glm::vec3 _specularCoef;

    float _visible;

  };
}
