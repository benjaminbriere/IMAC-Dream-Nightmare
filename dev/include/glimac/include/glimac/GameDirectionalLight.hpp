# pragma once

#include <glimac/glm.hpp>

#include "glimac/GameLight.hpp"

namespace glimac {

  class DirectionalLight : public Light
  {
    /* ATTRIBUTES */
  private:
    /* Same as Light */
    glm::vec3 _direction;
    lightType _type;

  public:
    /* CONSTRUCTORS */
    DirectionalLight(glm::vec3 intensity, glm::vec3 direction);

    /* GETTERS */
    /* same as Light */
    glm::vec3 getIntensity();
    lightType getType();
    const glm::vec3 getDirection() const;
  };

}
