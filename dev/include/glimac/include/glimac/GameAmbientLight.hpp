# pragma once

#include <glimac/glm.hpp>

#include "GameLight.hpp"

namespace glimac {

  class AmbientLight : public Light
  {
    /* ATTRIBUTES */
  private:
    /* Same as Light */
    lightType _type;

  public:
    /* CONSTRUCTORS */
    AmbientLight(glm::vec3 intensity);

    /* GETTERS */
    /* same as Light */
    glm::vec3 getIntensity();
    lightType getType();
  };

}
