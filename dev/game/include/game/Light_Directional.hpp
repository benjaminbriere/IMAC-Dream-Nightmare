# pragma once

#include <glimac/glm.hpp>

#include "Light.hpp"

namespace game {

  //Enfant de Light
  class DirectionalLight : public Light
  {
    private:
      glm::vec3 _direction;
      lightType _type;

    public:
      DirectionalLight(glm::vec3 intensity, glm::vec3 direction);
      
      glm::vec3 getIntensity();
      lightType getType();
      const glm::vec3 getDirection() const;
  };

}
