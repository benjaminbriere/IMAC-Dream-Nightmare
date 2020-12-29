#include "glimac/GameAmbientLight.hpp"

namespace glimac {

  AmbientLight::AmbientLight(glm::vec3 intensity):
    Light(intensity),
    _type(LIGHT_AMBIENT)
  {};

  glm::vec3 AmbientLight::getIntensity()
  {
    return _intensity;
  }

  lightType AmbientLight::getType()
  {
    return _type;
  }

}
