# pragma once

#include <glimac/glm.hpp>

#include "Light.hpp"

namespace game {

  //Enfant de Light
  class PointLight : public Light
  {
    private:
      glm::vec3 _position;
      lightType _type;

    public:
      PointLight(glm::vec3 intensity, glm::vec3 position);

      glm::vec3 getIntensity();
      lightType getType();
      const glm::vec3 getPosition() const;
  };

}
