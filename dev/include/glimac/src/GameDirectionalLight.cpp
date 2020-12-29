#include "glimac/GameDirectionalLight.hpp"

namespace glimac {

  DirectionalLight::DirectionalLight(glm::vec3 intensity, glm::vec3 direction):
    Light(intensity),
    _direction(direction),
    _type(LIGHT_DIRECTIONAL)
  {};

  glm::vec3 DirectionalLight::getIntensity()
  {
    return _intensity;
  }

  lightType DirectionalLight::getType()
  {
    return _type;
  }

  const glm::vec3 DirectionalLight::getDirection() const
  {
    return _direction;
  }
}
