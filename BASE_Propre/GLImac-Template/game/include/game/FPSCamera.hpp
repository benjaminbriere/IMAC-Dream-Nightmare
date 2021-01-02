#include <glimac/glm.hpp>
#include <cmath>

namespace game
{
  class FPSCamera
  {
    private:
      glm::vec3 m_Position;
      float m_fPhi;
      float m_fTheta;
      float m_mouse_sensibility;
      float m_walk_sensibility;
      glm::vec3 m_FrontVector;
      glm::vec3 m_LeftVector;
      glm::vec3 m_UpVector;

      void computeDirectionVectors();
    
    public:
      FPSCamera();
      ~FPSCamera();

      void setPosition(glm::vec3 position);
      void setPositionY(float v);

      void moveLeft(float distance);
      void moveFront(float distance);
      void rotateLeft(float degrees);
      void rotateUp(float degrees);

      glm::vec3 getPosition() const;
      glm::mat4 getViewMatrix() const;
      
      
  };
}
