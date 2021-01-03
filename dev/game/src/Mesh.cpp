#include "game/Mesh.hpp"

namespace game
{
  Mesh::MeshEntry::MeshEntry()
  {
    numIndices    = 0;
    materialIndex = INVALID_MATERIAL;
  }

  Mesh::MeshEntry::~MeshEntry()
  {

  }

  void Mesh::MeshEntry::init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
  {
    numIndices = indices.size();

    // Initialize vbo and ibo in the struct
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
  }

  Mesh::Mesh()
  {

  }

  Mesh::~Mesh()
  {

  }

  bool Mesh::loadMesh(const char* filename)
  {
    std::cout << "-- Mesh " << filename << " - initialisation..." << std::endl;

    bool ret = false;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(getModelFilePath(filename), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    // If the file is loaded, the Mesh object can be initalized
    if (scene) {
      std::cout << "-- " << filename << " chargé..." << std::endl;
      ret = init(scene, filename);
    }
    else {
      std::cerr << "ERREUR: Chargement du fichier 3D " << filename << std::endl;
    }

    return ret;
  }

  bool Mesh::init(const aiScene* scene, const char* filename)
  {
    // Meshes and textures vectors are resized
    _entries.resize(scene->mNumMeshes);
    _textures.resize(scene->mNumMaterials);

    // _entries is filled with all the meshes in the loaded file
    for (unsigned int i = 0; i < _entries.size(); i++) {
      const aiMesh* tmpMesh = scene->mMeshes[i];
      initMeshEntry(i, tmpMesh);
    }

    // Initialize the textures
    return initMaterials(scene);
  }

  void Mesh::initMeshEntry(unsigned int id, const aiMesh* meshEntry)
  {
    // The index of the material used by the mesh is stored
    _entries[id].materialIndex = meshEntry->mMaterialIndex;

    // Temp vectors filled with vertices and indices for the mesh faces
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Default value for the normal and tex corrds
    const aiVector3D defaultVector(0.0f, 0.0f, 0.0f);

    // vertices filled with all vertices
    for (unsigned int i = 0; i < meshEntry->mNumVertices; i++) {
      // Vertice position
      const aiVector3D* pos = &(meshEntry->mVertices[i]);
      // Normal
      const aiVector3D* norm = &(meshEntry->mNormals[i]) ? &(meshEntry->mNormals[i]) : &defaultVector;
      // Texture coords
      const aiVector3D* texCoords = meshEntry->HasTextureCoords(0) ? &(meshEntry->mTextureCoords[0][i]) : &defaultVector;

      // Create a point and store it
      Vertex v(glm::vec3(pos->x, pos->y, pos->z),
              glm::vec2(texCoords->x, texCoords->y),
              glm::vec3(norm->x, norm->y, norm->z));

      vertices.push_back(v);
    }

    // indices filled with the informations of the mesh faces
    for (unsigned int i = 0; i < meshEntry->mNumFaces; i++) {
      const aiFace& face = meshEntry->mFaces[i];

      indices.push_back(face.mIndices[0]);
      indices.push_back(face.mIndices[1]);
      indices.push_back(face.mIndices[2]);
    }

    // MeshEntry struct initialized in _entries
    _entries[id].init(vertices, indices);
  }

  bool Mesh::initMaterials(const aiScene* scene)
  {
    bool ret = true;

    // Loading default texture
    glimac::FilePath defTexturePath;
    getTextureFilePath(&defTexturePath, "textures/white.png");
    std::unique_ptr<glimac::Image> defaultTex = loadImage(defTexturePath);

    if (defaultTex == NULL) {
      std::cerr << "-- ERREUR chargement texture par défaut " << defTexturePath << std::endl;
      return false;
    }

    // All the textures are processed
    for (unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
      const aiMaterial* material = scene->mMaterials[i];

      aiColor3D diffuseCol(1.f, 1.f, 1.f);
      material->Get(AI_MATKEY_COLOR_DIFFUSE,diffuseCol);

      _diffuseCoef = glm::vec3(
        diffuseCol.r,
        diffuseCol.g,
        diffuseCol.b
      );

      aiColor3D specularCol(1.f, 1.f, 1.f);
      material->Get(AI_MATKEY_COLOR_SPECULAR,specularCol);

      _specularCoef = glm::vec3(
        specularCol.r,
        specularCol.g,
        specularCol.b
      );

      material->Get(AI_MATKEY_SHININESS,_shininess);

      _textures[i] = 0;

      // Only diffuse textures are processed
      if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        aiString path;

        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
          glimac::FilePath texturePath;
          getTextureFilePath(&texturePath, path.data);

          std::unique_ptr<glimac::Image> tex = loadImage(texturePath);

          GLuint texId;
          glGenTextures(1, &texId);
          glBindTexture(GL_TEXTURE_2D, texId);

          // Using default texture if the correct texture was not loaded
          if (tex == NULL) {
            std::cerr << "-- Erreur lors du chargement de la texture " << texturePath << std::endl;
            glTexImage2D(
              GL_TEXTURE_2D,
              0,
              GL_RGBA,
              defaultTex->getWidth(),
              defaultTex->getHeight(),
              0,
              GL_RGBA,
              GL_FLOAT,
              defaultTex->getPixels()
              );
            ret = false;
          }
          else {
            std::cout << "-- " << texturePath << " chargée..." << std::endl;
            glTexImage2D(
              GL_TEXTURE_2D,
              0,
              GL_RGBA,
              tex->getWidth(),
              tex->getHeight(),
              0,
              GL_RGBA,
              GL_FLOAT,
              tex->getPixels()
              );
          }

          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

          _textures[i] = texId;
        }
      }
    }

    return ret;
  }

  void Mesh::render()
  {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0; i < _entries.size(); i++) {
      glBindBuffer(GL_ARRAY_BUFFER, _entries[i].vb);
      glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        0
        );
      glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (const GLvoid*) (offsetof(Vertex, _texCoords))
        );
      glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (const GLvoid*) (offsetof(Vertex, _normal))
        );

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _entries[i].ib);

      const unsigned int matIndex = _entries[i].materialIndex;

      if (matIndex < _textures.size() && _textures[matIndex]) {
        glBindTexture(GL_TEXTURE_2D, _textures[matIndex]);
      }

      glDrawElements(GL_TRIANGLES, _entries[i].numIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
  }

  float Mesh::getShininess()
  {
    return _shininess;
  }

  glm::vec3 Mesh::getDiffuse()
  {
    return _diffuseCoef;
  }

  glm::vec3 Mesh::getSpecular()
  {
    return _specularCoef;
  }

  float Mesh::getVisible(){
    return _visible;
  }

  void Mesh::setVisible(float v){
    _visible = v;
  }

  void Mesh::setPosition(glm::vec3 position)
  {
    _position = position;
  }

  void Mesh::setAngle(float angle)
  {
    _angle = angle;
  }

  void Mesh::setRotAxe(glm::vec3 axis)
  {
    _rotAxe = axis;
  }

  void Mesh::setScale(glm::vec3 scale)
  {
    _scale = scale;
  }

  glm::vec3 Mesh::getPosition()
  {
    return _position;
  }

  float Mesh::getAngle()
  {
    return _angle;
  }

  glm::vec3 Mesh::getRotAxe()
  {
    return _rotAxe;
  }

  glm::vec3 Mesh::getScale()
  {
    return _scale;
  }
}
