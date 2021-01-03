# pragma once

#include <glimac/glm.hpp>

#include "Light.hpp"

namespace game {

  //enfant de Light
  class AmbientLight : public Light
  {
    private:

      lightType _type;

    public:

      AmbientLight(glm::vec3 intensity);

      glm::vec3 getIntensity();
      lightType getType();
  };

}
