# pragma once

#include <glimac/glm.hpp>

namespace game {
  enum lightType
  {
    LIGHT_AMBIENT= 0,
    LIGHT_DIRECTIONAL = 1,
    LIGHT_POINT = 2
  };

  class Light
  {

  protected:
    glm::vec3 _intensity;
    lightType _type;

  public:

    Light (glm::vec3 intensity);

    virtual glm::vec3 getIntensity();
    virtual lightType getType();

  };

}
