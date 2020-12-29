# pragma once

#include <glimac/glm.hpp>

namespace glimac {
  
  enum lightType
  {
    LIGHT_AMBIENT= 0,
    LIGHT_DIRECTIONAL = 1,
    LIGHT_POINT = 2
  };

  /* Class general light */
  class Light
  {
    /* ATTRIBUTES */
  protected:
    glm::vec3 _intensity;
    lightType _type;

  public:
    /* CONSTRUCTORS */
    Light (glm::vec3 intensity);

    /* GETTERS */
    virtual glm::vec3 getIntensity();
    virtual lightType getType();

    /* SETTERS */
  };

}
