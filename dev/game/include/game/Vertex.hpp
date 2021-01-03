#include <glimac/glm.hpp>

namespace game
{
  class Vertex {
  public:
    glm::vec3 _position;
    glm::vec2 _texCoords;
    glm::vec3 _normal;
    
    Vertex();
    Vertex(glm::vec3 position, glm::vec2 textcoord, glm::vec3 normal);
    Vertex(float posX, float posY, float posZ, float tcX, float tcY, float normX, float normY, float normZ);
    Vertex(const Vertex& vertexToCopy);
    ~Vertex();
    
    bool operator==(const Vertex& rhs) const;
  };
}