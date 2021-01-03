#include "game/Vertex.hpp"

namespace game
{
  Vertex::Vertex() :
    _position(glm::vec3(0)),
    _texCoords(glm::vec2(0)),
    _normal(glm::vec3(0)){

  }

  Vertex::Vertex(glm::vec3 position, glm::vec2 textcoord, glm::vec3 normal) :
    _position(position),
    _texCoords(textcoord),
    _normal(normal){

  }

  Vertex::Vertex(float posX, float posY, float posZ, float tcX, float tcY, float normX, float normY, float normZ) :
    _position(glm::vec3(posX, posY, posZ)),
    _texCoords(glm::vec2(tcX, tcY)),
    _normal(glm::vec3(normX, normY, normZ)){

  }

  Vertex::Vertex(const Vertex& vertexToCopy) :
    _position(vertexToCopy._position),
    _texCoords(vertexToCopy._texCoords),
    _normal(vertexToCopy._normal){

  }

  Vertex::~Vertex()
  {
    
  }

  /* OVERLOADING */
  /* Operators */
  /* |_Comparison operators */
  bool Vertex::operator==(const Vertex& rhs) const {
    return(_position == rhs._position && _texCoords == rhs._texCoords && _normal == rhs._normal);
  }
}