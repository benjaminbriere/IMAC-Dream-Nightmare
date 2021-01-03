#include "game/Light_Point.hpp"

namespace game {

  /* CONSTRUCTORS */
  PointLight::PointLight(glm::vec3 intensity, glm::vec3 position):
    Light(intensity),
    _position(position),
    _type(LIGHT_POINT)
  {};

  glm::vec3 PointLight::getIntensity()
  {
    return _intensity;
  }

  lightType PointLight::getType()
  {
    return _type;
  }

  const glm::vec3 PointLight::getPosition () const
  {
    return _position;
  }
}
